// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9720 rf_ui_play_feedback_sound
// UNREALRED VERIFIED [ui-properties-20261029]: Signed sound-event index. Reads ID table0x1CF75A0[index] WITHOUT index bound;nonnegative ID plays rf_gamesound_play_event(id,0,0.0,1.0). Missing ID and index>1 falls back table slot1 at0x1CF75A4 when nonnegative. Otherwise returns original index. Play path returns sound handle/helper result;not a normalized status. No table setup or resource loading in body.
int __cdecl rf_ui_play_feedback_sound(int a1)
{
  int result; // eax

  result = a1;
  if ( dword_1CF75A0[a1] >= 0 )
    return rf_gamesound_play_event(dword_1CF75A0[a1], 0, 0.0, 1.0);
  if ( a1 > 1 && unk_1CF75A4 >= 0 )
    return rf_gamesound_play_event(unk_1CF75A4, 0, 0.0, 1.0);
  return result;
}

