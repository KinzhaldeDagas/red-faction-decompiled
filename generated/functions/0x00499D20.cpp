// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499D20 rf_client_ctf_red_capture_byte_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(raw byte value). Only runtime mode exactly1, authority exactly0 and game mode exactly1 copies low argument BYTE into red capture count77D6E0. No initialized check,
// normalization, increment, assist award, carrier/timer mutation or network send. Out-of-mode leaves count unchanged; EAX is guard/game-mode artifact rather than a defined
// success/count return.
int __cdecl rf_client_ctf_red_capture_byte_set(char a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = rf_multiplayer_game_mode_get();
    if ( result == 1 )
      byte_77D6E0 = a1;
  }
  return result;
}

