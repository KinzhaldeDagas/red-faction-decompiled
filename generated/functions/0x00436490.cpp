// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436490 rf_entity_request_body_action
// VERIFIED: Starts the resolved animation record stored in one of 45 owner slots at +2644 with stride 16; invalid indices above 44 or a -1 record index do not start an animation.
// UNREALRED VERIFIED [body-action-decode]: Validates one of 45 action records and starts its VMesh action with mix, hold-last, and optional sound.
void __cdecl rf_entity_request_body_action(int a1, unsigned int a2, float a3, char a4, char a5)
{
  int v5; // [esp+Ch] [ebp-4h]

  if ( a2 <= 0x2C && *(int *)(a1 + 16 * a2 + 2644) >= 0 )
  {
    rf_vfx_start_instance(*(int **)(a1 + 128), *(_DWORD *)(a1 + 16 * a2 + 2644), a3, a4);
    if ( a5 == 1 )
    {
      v5 = rf_foley_choose_random_sound(*(_DWORD *)(a1 + 16 * a2 + 2652));
      if ( v5 != -1 )
        rf_gamesound_play_positional_event(v5, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    }
  }
}

