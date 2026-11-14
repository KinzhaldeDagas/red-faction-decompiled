// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAEF0 rf_player_get_alt_zoom_in_flag_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Assumes player nonNULL; loads raw BYTE3988 into AL, returns without normalization or global-local check. No zoom factor, sound, camera or transition updates; upper EAX is incidental pointer residue.
char __cdecl rf_player_get_alt_zoom_in_flag_byte(int a1)
{
  return *(_BYTE *)(a1 + 3988);
}

