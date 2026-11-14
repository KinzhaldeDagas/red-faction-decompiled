// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004414D0 rf_player_build_controls_unpaused_unblocked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(player pointer,output pointer), no uniform success result. First448C10 pause query: ANY nonzero AL
// exits with EAX=zero-extended returned byte, before reading either argument. Pause0 delegates441520(player,output) unless runtime BYTE704E81==EXACT1 AND authority BYTE704E82==0.
// Only that exact multiplayer-client branch dereferences GLOBAL local-player pointer87C318, then DWORD[globalPlayer+4608], then DWORD[nested+8]. Mask0x20 set suppresses construction
// and leaves EAX equal to the global player POINTER; mask clear delegates and forwards full EAX. This gate uses global local player, not caller player, with no global/nested NULL
// guard; runtime bytes other than1 delegate. Does not initialize output or normalize any return.
int __cdecl rf_player_build_controls_unpaused_unblocked(int a1, int a2)
{
  int result; // eax

  result = (unsigned __int8)rf_game_pause_gate_query();
  if ( !(_BYTE)result )
  {
    if ( rf_multiplayer_runtime_mode != 1 )
      return rf_player_build_controls_from_embedded_input(a1, a2);
    if ( rf_multiplayer_server_authority )
      return rf_player_build_controls_from_embedded_input(a1, a2);
    result = rf_local_fpgun_player;
    if ( (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x20) == 0 )
      return rf_player_build_controls_from_embedded_input(a1, a2);
  }
  return result;
}

