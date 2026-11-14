// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00428970 rf_entity_update_body_state_transition
// UNREALRED VERIFIED [mission-play-animation-20261013] Entity+0x810 bit8 suppresses this entire normal cyclic-state scheduler. When enabled, the scheduler selects normal state indices then zeroes cyclic weights through0x565000 and writes the current/pending mixes. Thus an unheld Play_Animation state record is not an invented persistent AI state override: the next ordinary scheduler pass replaces its weight. A prior held-action bit8 survives a later state event until its separate owner resets it.
void __cdecl rf_entity_update_body_state_transition(int a1)
{
  float v1; // [esp+4h] [ebp-10h]
  float v2; // [esp+8h] [ebp-Ch]
  int v3; // [esp+Ch] [ebp-8h]
  int v4; // [esp+10h] [ebp-4h]

  if ( (*(_DWORD *)(a1 + 2064) & 8) == 0 && rf_entity_admits_speech_body_actions(a1) )
  {
    if ( sub_438AC0(a1) )
      rf_player_update_entity_body_animation_for_movement(*(_DWORD *)(a1 + 5168));
    else
      sub_428B90(a1);
    if ( *(float *)(a1 + 5012) > 0.0 )
    {
      *(float *)(a1 + 5016) = *(float *)(a1 + 5016) + rf_frame_delta_seconds;
      if ( *(float *)(a1 + 5012) <= (double)*(float *)(a1 + 5016) )
      {
        *(_DWORD *)(a1 + 5004) = *(_DWORD *)(a1 + 5008);
        *(float *)(a1 + 5012) = 0.0;
        *(_DWORD *)(a1 + 5008) = -1;
      }
    }
    v4 = *(_DWORD *)(a1 + 16 * *(_DWORD *)(a1 + 5004) + 2276);
    rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(a1 + 128));
    if ( (*(_DWORD *)(a1 + 2064) & 0x20) != 0 )
    {
      if ( *(int *)(a1 + 16 * *(_DWORD *)(a1 + 4996) + 2276) >= 0 )
        rf_model_handle_set_cyclic_mix_adapter(
          *(int **)(a1 + 128),
          *(_DWORD *)(a1 + 16 * *(_DWORD *)(a1 + 4996) + 2276),
          1.0);
    }
    else if ( *(float *)(a1 + 5012) == 0.0 )
    {
      if ( v4 != -1 )
        rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 128), v4, 1.0);
    }
    else
    {
      v3 = *(_DWORD *)(a1 + 16 * *(_DWORD *)(a1 + 5008) + 2276);
      if ( v3 != -1 && v4 != -1 )
      {
        v2 = *(float *)(a1 + 5016) / *(float *)(a1 + 5012);
        v1 = 1.0 - v2;
        rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 128), v4, v1);
        rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 128), v3, v2);
      }
    }
  }
}

