// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00488BE0 rf_mover_stop_sounds
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Stops live sound-slot1 voice (+0x320) and sets its handle -1, then plays sound slot2 and retains voice+0x324. Called on waits/stops; rotating arrival separately stops slot1 first via0x4897F0.
// UNREALRED VERIFIED [mission-mover-effects-20261013] Stops only the currently retained movement handle at+0x320 and sets it -1, then starts slot2 independently. It does not stop previous departure/closing one-shots. Generation-tagged voice handles prevent an old retained slot from stopping a reused common voice.
int __cdecl rf_mover_stop_sounds(int a1)
{
  int result; // eax

  if ( *(_DWORD *)(a1 + 800) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 800));
    *(_DWORD *)(a1 + 800) = -1;
  }
  result = rf_gamesound_play_positional_event(*(_DWORD *)(a1 + 736), (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
  *(_DWORD *)(a1 + 804) = result;
  return result;
}

