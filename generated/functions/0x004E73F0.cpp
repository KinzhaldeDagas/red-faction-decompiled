// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E73F0 rf_fpgun_update_state_transition
// UNREALRED VERIFIED [fpgun-state-decode]: Advances and promotes the 0.2-second fpgun state crossfade and writes linear weights.
void __cdecl rf_fpgun_update_state_transition(int a1, unsigned int a2)
{
  float v2; // [esp+4h] [ebp-18h]
  float v3; // [esp+8h] [ebp-14h]
  int v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+10h] [ebp-Ch]

  if ( a1 == rf_local_fpgun_player )
  {
    if ( rf_entity_resolve_handle(*(_DWORD *)(a1 + 20)) )
    {
      *(_DWORD *)(a1 + 52) = rf_fpgun_selected_mesh_resolve((_DWORD *)a1, a2);
      if ( *(int *)(a1 + 52) > 0 )
      {
        rf_fpgun_select_state(a1);
        if ( *(float *)(a1 + 4312) > 0.0 )
        {
          *(float *)(a1 + 4316) = *(float *)(a1 + 4316) + rf_frame_delta_seconds;
          if ( *(float *)(a1 + 4312) <= (double)*(float *)(a1 + 4316) )
          {
            *(_DWORD *)(a1 + 4320) = *(_DWORD *)(a1 + 4324);
            *(float *)(a1 + 4312) = 0.0;
            *(_DWORD *)(a1 + 4324) = -1;
          }
        }
        if ( *(int *)(a1 + 4320) >= 0 )
        {
          v5 = *((_DWORD *)&rf_weapon_records + 340 * a2 + 7 * *(_DWORD *)(a1 + 4320) + 172);
          rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(a1 + 52));
          if ( *(float *)(a1 + 4312) == 0.0 )
          {
            if ( v5 != -1 )
              rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 52), v5, 1.0);
          }
          else
          {
            v4 = *((_DWORD *)&rf_weapon_records + 340 * a2 + 7 * *(_DWORD *)(a1 + 4324) + 172);
            if ( v4 != -1 && v5 != -1 )
            {
              v3 = *(float *)(a1 + 4316) / *(float *)(a1 + 4312);
              v2 = 1.0 - v3;
              rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 52), v5, v2);
              rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 52), v4, v3);
            }
          }
        }
      }
    }
  }
}

