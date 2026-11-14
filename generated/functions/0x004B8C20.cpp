// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B8C20 rf_physics_work_batch_execute
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): Cdecl(batch vector,nonzero commit flag); vector signed count at+0 via486DE0, element address via existing inline-array helper. Starts retry index0;
// while count>0, re-reads count in each loop. Integrates each entry: type0 entity motion prediction then ordered speed length(velocity+324)>DOUBLE100 triggers
// damage(handle+44,FLOAT10000,0,0,9,0,-1,1), eight stack slots; discards returned ST0. Other types call body integrator. If count remains positive invokes pair-contact solver. World
// sweeps require physics mask+424 bit0x10; when runtime BYTE==EXACT1 also require BYTE7B8E19==EXACT1 OR object==global681E38 OR object type!=0. Other runtime values including2 bypass
// this extra restriction. Then per-entry optional commit: entities entity-commit/contact, others body-finalize. Residual FLOAT+432 ordered<=0 retires immediately; UNORDERED follows
// remaining-time path. Remaining entries survive if (retry<=3 OR residual is NOT ordered<DOUBLE0.25) AND retry<10; survivors increment index, erased entries do not, so shifted
// element is processed at same index. On retirement, commit flag nonzero publishes position from object+228 and clears physics bit0x40000000. Retry-exhaustion retirement
// additionally, only when commit and entity descriptor(+2136)->+4==3, computes float32(squaredDistance(object+60,object+240)/frameDelta); ordered result<DOUBLE0.05000000074505806
// zeros velocity+324. This is distance-squared divided by delta, not squared speed; no zero-delta guard. With commit flag0 the function still integrates, sweeps and erases entries
// but skips finalization, publication, velocity zeroing and bit clearing. After retirement scan increments retry and repeats full batch; at most initial pass plus ten retries.
// Returns current signed vector count (zero normally, or preexisting negative count); no success boolean.
int __cdecl rf_physics_work_batch_execute(_DWORD *a1, int a2)
{
  int result; // eax
  int first_dword; // eax
  int *v4; // eax
  int *v5; // eax
  int v6; // eax
  int v7; // eax
  int *v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // eax
  int *v12; // eax
  int v13; // eax
  float out_vector[3]; // [esp+1Ch] [ebp-1Ch] BYREF
  float v15; // [esp+28h] [ebp-10h]
  int v16; // [esp+2Ch] [ebp-Ch]
  int i; // [esp+30h] [ebp-8h]
  int v18; // [esp+34h] [ebp-4h]

  v18 = 0;
LABEL_2:
  result = rf_receiver_get_first_dword(a1);
  if ( result > 0 )
  {
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(a1);
      if ( i >= first_dword )
        break;
      v4 = (int *)rf_inline_dword_array4_element_address_unchecked(a1, i);
      if ( rf_object_is_entity(*v4) )
      {
        v5 = (int *)rf_inline_dword_array4_element_address_unchecked(a1, i);
        rf_entity_predict_motion_by_current_descriptor(*v5);
        v6 = rf_inline_dword_array4_element_address_unchecked(a1, i);
        if ( rf_vector3_length((float *)(*(_DWORD *)v6 + 324)) > 100.0 )
        {
          v7 = rf_inline_dword_array4_element_address_unchecked(a1, i);
          rf_damage_dispatch(*(_DWORD *)(*(_DWORD *)v7 + 44), 10000.0, 0, 0, 9, 0, -1, 1);
        }
      }
      else
      {
        v8 = (int *)rf_inline_dword_array4_element_address_unchecked(a1, i);
        rf_physics_body_integrate(*v8);
      }
    }
    if ( rf_receiver_get_first_dword(a1) > 0 )
      rf_physics_pair_contacts_solve();
    if ( rf_multiplayer_runtime_mode == 1 )
    {
      for ( i = 0; ; ++i )
      {
        v9 = rf_receiver_get_first_dword(a1);
        if ( i >= v9 )
          break;
        if ( (unk_7B8E19 == 1
           || *(_DWORD *)rf_inline_dword_array4_element_address_unchecked(a1, i) == dword_681E38
           || *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(a1, i) + 36))
          && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(a1, i) + 424) & 0x10) != 0 )
        {
          v10 = (int *)rf_inline_dword_array4_element_address_unchecked(a1, i);
          rf_physics_world_contacts_sweep(*v10);
        }
      }
    }
    else
    {
      for ( i = 0; ; ++i )
      {
        v11 = rf_receiver_get_first_dword(a1);
        if ( i >= v11 )
          break;
        if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(a1, i) + 424) & 0x10) != 0 )
        {
          v12 = (int *)rf_inline_dword_array4_element_address_unchecked(a1, i);
          rf_physics_world_contacts_sweep(*v12);
        }
      }
    }
    i = 0;
    while ( 1 )
    {
      v13 = rf_receiver_get_first_dword(a1);
      if ( i >= v13 )
      {
        ++v18;
        goto LABEL_2;
      }
      v16 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked(a1, i);
      if ( a2 )
      {
        if ( rf_object_is_entity(v16) )
          rf_entity_commit_motion_and_dispatch_contact(v16);
        else
          rf_physics_body_finalize_step(v16);
      }
      if ( *(float *)(v16 + 432) <= 0.0 )
        break;
      if ( (v18 <= 3 || *(float *)(v16 + 432) >= 0.25) && v18 < 10 )
      {
        ++i;
      }
      else
      {
        if ( a2 )
        {
          if ( rf_object_is_entity(v16) && *(_DWORD *)(*(_DWORD *)(v16 + 2136) + 4) == 3 )
          {
            rf_vector_subtract((const float *)(v16 + 60), out_vector, (const float *)(v16 + 240));
            v15 = rf_vector_length_squared(out_vector) / rf_frame_delta_seconds;
            if ( v15 < 0.05000000074505806 )
              rf_vector3_zero_return_destination((float *)(v16 + 324));
          }
          rf_object_publish_position_and_bounds(v16, (float *)(v16 + 228));
          *(_DWORD *)(v16 + 424) &= ~0x40000000u;
        }
LABEL_37:
        rf_inline_pointer_array_erase_unchecked(a1, i);
      }
    }
    if ( a2 )
    {
      rf_object_publish_position_and_bounds(v16, (float *)(v16 + 228));
      *(_DWORD *)(v16 + 424) &= ~0x40000000u;
    }
    goto LABEL_37;
  }
  return result;
}

