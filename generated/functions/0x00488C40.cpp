// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00488C40 rf_mover_start_sounds
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Departure audio selects sound slot3 for a door whose target index is0 or any backward rotating mover; otherwise slot0. Then plays slot1 when available and retains voice handles at +0x31C/+0x328 and +0x320. Repeated forward activation while active does not restart this sequence.
// UNREALRED VERIFIED [mission-mover-effects-20261013] Mover slot1 is a retained movement voice, but its looping comes from bluebeard.bty via0x568050. Slots0/3 and1 all use this same positional path. Source volume/minimum distance come from constructor registration; L14S2 uses minimum10 instead of5 RF units. Starting a slot replaces the retained handle without stopping an older voice in that slot.
int __cdecl rf_mover_start_sounds(int a1)
{
  int result; // eax
  bool v2; // [esp+Fh] [ebp-1h]

  v2 = 0;
  if ( rf_mover_flag2_is_set(a1) )
    v2 = *(_DWORD *)(a1 + 764) == 0;
  if ( rf_mover_is_rotating(a1) && (*(_DWORD *)(a1 + 792) & 0x2000) == 0 )
    v2 = 1;
  if ( v2 )
  {
    result = rf_gamesound_play_positional_event(*(_DWORD *)(a1 + 740), (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    *(_DWORD *)(a1 + 808) = result;
  }
  else
  {
    result = rf_gamesound_play_positional_event(*(_DWORD *)(a1 + 728), (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    *(_DWORD *)(a1 + 796) = result;
  }
  if ( *(_DWORD *)(a1 + 732) != -1 )
  {
    result = rf_gamesound_play_positional_event(*(_DWORD *)(a1 + 732), (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    *(_DWORD *)(a1 + 800) = result;
  }
  return result;
}

