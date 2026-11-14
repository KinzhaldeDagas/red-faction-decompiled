// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBC00 rf_player_reset_alt_zoom_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Assumes player nonNULL. Clear bytes3988/3989 then F32+0 to factor3992. Return player+3968 pointer bits EAX, not player or boolean. No global-local guard, sound stop, factor1 clamp or other target-lock/scanner reset. Neutral0 remains distinct from valid update clamp minimum1.
int __cdecl rf_player_reset_alt_zoom_state(int a1)
{
  *(_BYTE *)(a1 + 3988) = 0;
  *(_BYTE *)(a1 + 3989) = 0;
  *(float *)(a1 + 3992) = 0.0;
  return a1 + 3968;
}

