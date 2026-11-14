// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E25F0 rf_player_begin_blackout_transition
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] Store exact float literal1e-7f into player+0x11D4 and supplied duration into+0x11D8. Supplied nonzero callback stored at+0x11DC, otherwise default0x4E25D0. No duration validation, player flag mutation, callback invocation, or immediate transition completion in body.
int __cdecl rf_player_begin_blackout_transition(int a1, float a2, int a3)
{
  int result; // eax

  result = a1;
  *(float *)(a1 + 4564) = 0.0000001;
  *(float *)(a1 + 4568) = a2;
  if ( a3 )
  {
    *(_DWORD *)(a1 + 4572) = a3;
    return a3;
  }
  else
  {
    *(_DWORD *)(a1 + 4572) = rf_player_request_panel13_and_stop_voices;
  }
  return result;
}

