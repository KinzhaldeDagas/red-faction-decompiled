// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEC10 rf_splitscreen_play_announcer_row
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl(signed rowIndex,stopAll BYTE,onlyIfIdle BYTE), bool AL. Global11 rows at662C80 stride12: eventDWORD0,voiceHandleDWORD4,playedBYTE8. stopAll nonzero
// calls4AECD0 then goes straight to play, ignoring onlyIfIdle. Else onlyIfIdle nonzero scans rows0..10: skip handle-1; query live voice using FULL EAX nonzero, on first playing
// return AL0 immediately; earlier dead handles already reset-1, later handles untouched. Dead queried handle reset-1. With neither gate, play regardless existing voices. Call
// gamesound(eventID at unchecked row,0,0.0,1.0), store returned handle even-1, set playedBYTE1, return AL1 unconditionally after delegate. No row bounds/runtime/authority guard;
// return1 means attempted row dispatch, not audible success. Original PE rows start event=-1,handle=-1,played0; event mapping/later initialization must not be inferred from row
// numbers.
char __cdecl rf_splitscreen_play_announcer_row(int a1, char a2, char a3)
{
  int i; // [esp+8h] [ebp-4h]

  if ( a2 )
  {
    rf_splitscreen_stop_all_announcer_voices();
  }
  else if ( a3 )
  {
    for ( i = 0; i < 11; ++i )
    {
      if ( dword_662C84[3 * i] != -1 )
      {
        if ( rf_gamesound_voice_is_playing(dword_662C84[3 * i]) )
          return 0;
        dword_662C84[3 * i] = -1;
      }
    }
  }
  dword_662C84[3 * a1] = rf_gamesound_play_event(dword_662C80[3 * a1], 0, 0.0, 1.0);
  byte_662C88[12 * a1] = 1;
  return 1;
}

