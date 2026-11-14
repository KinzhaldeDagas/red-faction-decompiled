// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E46B0 rf_player_render_fighter_chaingun_and_muzzle_flash
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(player,linked fighter,lowBYTE flash). Resolve own entity,missing exits; get cockpit handle, require SIGNED>0. If either GLOBAL node cache662F34/38<0 resolve BOTH chaingun_1 and muzzle_1 against cockpit model; any stillnegative exits before spin/load/render. Firing-byte predicate422270(own linked UID512,fighter selected weapon676) nonzero: F32 speed4300 += dt/DOUBLE.25 *DOUBLE25.13274192810059; else subtract dt/DOUBLE1 *same. Clamp speed to[0,F3225.132742], NaN preserved by native clamp; F32 angle4296 +=dt*speed, no angle wrapping. Axis-angle from own matrix row+96; render orientation=own matrix72 *rotation. Compose chaingun node using own position2004 and matrix2016 for POSITION, discard composed node orientation for spin orientation.
// Lazy-load Fighter01_chaingun.v3d mode1,-1 when global662F30==-1; render if !=-1. Nonzero flash independently composes muzzle node using own matrix72/position2004, binds selected weapon texture DWORD+100,-1, then billboard with size from weapon F32+104,random angle0..F326.2831855,glow render state. No own weapon/NULLfighter/finite/node-model cache validation. Return AL is raw child/pointer residue, not canonical status.
char __cdecl rf_player_render_fighter_chaingun_and_muzzle_flash(int a1, int a2, char a3)
{
  int attached_cockpit_model_handle; // eax
  double v4; // st7
  float v6; // [esp+4h] [ebp-114h]
  float v7; // [esp+8h] [ebp-110h]
  int v8; // [esp+Ch] [ebp-10Ch]
  int v9[3]; // [esp+10h] [ebp-108h] BYREF
  int v10; // [esp+1Ch] [ebp-FCh]
  char v11[36]; // [esp+20h] [ebp-F8h] BYREF
  float v12[9]; // [esp+44h] [ebp-D4h] BYREF
  float v13[3]; // [esp+68h] [ebp-B0h] BYREF
  char v14[36]; // [esp+74h] [ebp-A4h] BYREF
  char v15[84]; // [esp+98h] [ebp-80h] BYREF
  char *v16; // [esp+ECh] [ebp-2Ch]
  float v17[9]; // [esp+F0h] [ebp-28h] BYREF
  int v18; // [esp+114h] [ebp-4h]

  attached_cockpit_model_handle = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v18 = attached_cockpit_model_handle;
  if ( attached_cockpit_model_handle )
  {
    attached_cockpit_model_handle = rf_player_get_attached_cockpit_model_handle(a1);
    v10 = attached_cockpit_model_handle;
    if ( attached_cockpit_model_handle > 0 )
    {
      if ( dword_662F34 < 0 || dword_662F38 < 0 )
      {
        dword_662F34 = rf_model_handle_find_node_adapter(v10, "chaingun_1");
        attached_cockpit_model_handle = rf_model_handle_find_node_adapter(v10, "muzzle_1");
        dword_662F38 = attached_cockpit_model_handle;
      }
      if ( dword_662F34 >= 0 && dword_662F38 >= 0 )
      {
        if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v18 + 512), *(_DWORD *)(a2 + 676)) )
          v4 = rf_frame_delta_seconds / 0.25 * 25.13274192810059 + *(float *)(a1 + 4300);
        else
          v4 = *(float *)(a1 + 4300) - rf_frame_delta_seconds / 1.0 * 25.13274192810059;
        *(float *)(a1 + 4300) = v4;
        rf_float_clamp_in_place((float *)(a1 + 4300), 0.0, 25.132742);
        *(float *)(a1 + 4296) = rf_frame_delta_seconds * *(float *)(a1 + 4300) + *(float *)(a1 + 4296);
        rf_matrix3_construct((char *)v12);
        rf_matrix3_set_axis_angle_unchecked_axis(v12, (float *)(v18 + 96), *(float *)(a1 + 4296));
        rf_matrix3_argument_times_receiver_to_output(v12, v17, (const float *)(v18 + 72));
        rf_matrix3_construct(v14);
        rf_vector3_default_construct_noop(v13);
        rf_vmesh_compose_prop_world_transform(v10, dword_662F34, (float *)(v18 + 2016), v18 + 2004, (int)v14, v13);
        LOBYTE(attached_cockpit_model_handle) = (unsigned __int8)rf_model_render_options_construct(v15);
        if ( dword_662F30 == -1 )
        {
          attached_cockpit_model_handle = rf_model_handle_load_v3m_mode1(aFighter01Chain, 1, (void *)0xFFFFFFFF);
          dword_662F30 = attached_cockpit_model_handle;
        }
        if ( dword_662F30 != -1 )
          LOBYTE(attached_cockpit_model_handle) = rf_model_handle_render_all_adapter(
                                                    dword_662F30,
                                                    (int)v13,
                                                    (int)v17,
                                                    (int)v15);
        if ( a3 )
        {
          v16 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)(a2 + 676);
          rf_vector3_default_construct_noop(v9);
          rf_matrix3_construct(v11);
          rf_vmesh_compose_prop_world_transform(
            v10,
            dword_662F38,
            (float *)(v18 + 72),
            v18 + 2004,
            (int)v11,
            (float *)v9);
          rf_renderer_set_pending_texture_handles(*((_DWORD *)v16 + 25), -1);
          v8 = LODWORD(rf_particle_glow_billboard_render_state);
          v7 = *((float *)v16 + 26);
          v6 = rf_random_float_range(0.0, 6.2831855);
          LOBYTE(attached_cockpit_model_handle) = rf_renderer_world_billboard_aspect_backend_dispatch(
                                                    (int)v9,
                                                    v6,
                                                    v7,
                                                    v8);
        }
      }
    }
  }
  return attached_cockpit_model_handle;
}

