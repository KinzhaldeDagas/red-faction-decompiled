// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC6A0 rf_player_prepare_and_render_carried_corpse
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Resolves entity20 then carried-body handle entity1884 using type7 resolver; either missing returns0. ORs corpse flags124 mask0x4000 and never restores it here. If corpse animation704!=-1, resets cyclic/actions, starts selected animation atweight1,mode1, spills double animation-duration ST0 to FLOAT, advances by that float then by float0.30000001, both with flags0,NULL position/matrix,extra1. This happens even if later rendering is suppressed. Reads camera196 state8; only state0 AND global byte6807E0==0 skips render. Else composes owner entity model128 node at class660 DWORD5076 using entity orientation72/position60, constructs default render options and renders corpse model128
// at composed pose. No own NULL camera/model/class checks or node validation; returns EAX residue/render delegate result.
float *__cdecl rf_player_prepare_and_render_carried_corpse(int a1)
{
  float *result; // eax
  float v2; // [esp+14h] [ebp-8Ch]
  float v3[3]; // [esp+18h] [ebp-88h] BYREF
  char v4[36]; // [esp+24h] [ebp-7Ch] BYREF
  char v5[80]; // [esp+48h] [ebp-58h] BYREF
  float *v6; // [esp+98h] [ebp-8h]
  float *v7; // [esp+9Ch] [ebp-4h]

  result = (float *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v7 = result;
  if ( result )
  {
    result = (float *)rf_corpse_resolve_handle_type7(*((_DWORD *)v7 + 471));
    v6 = result;
    if ( result )
    {
      *((_DWORD *)v6 + 31) |= 0x4000u;
      if ( *((_DWORD *)v6 + 176) != -1 )
      {
        rf_model_handle_reset_cyclic_adapter(*((_DWORD *)v6 + 32));
        rf_model_handle_reset_actions_adapter(*((_DWORD *)v6 + 32));
        rf_vfx_start_instance(*((int **)v6 + 32), *((_DWORD *)v6 + 176), 1.0, 1);
        v2 = rf_model_animation_duration_seconds((unsigned int *)*((_DWORD *)v6 + 32), *((_DWORD *)v6 + 176));
        rf_vfx_update_instance(*((int **)v6 + 32), v2, 0, 0, 0, 1);
        rf_vfx_update_instance(*((int **)v6 + 32), 0.30000001, 0, 0, 0, 1);
      }
      result = (float *)rf_view_wrapper_get_dword8(*(_DWORD *)(a1 + 196));
      if ( result || unk_6807E0 )
      {
        rf_vector3_default_construct_noop(v3);
        rf_matrix3_construct(v4);
        rf_vmesh_compose_prop_world_transform(
          *((_DWORD *)v7 + 32),
          *(_DWORD *)(*((_DWORD *)v7 + 165) + 5076),
          v7 + 18,
          (int)(v7 + 15),
          (int)v4,
          v3);
        rf_model_render_options_construct(v5);
        return (float *)rf_model_handle_render_all_adapter(*((_DWORD *)v6 + 32), (int)v3, (int)v4, (int)v5);
      }
    }
  }
  return result;
}

