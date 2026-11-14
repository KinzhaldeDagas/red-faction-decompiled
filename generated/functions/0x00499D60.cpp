// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499D60 rf_client_ctf_blue_capture_byte_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(raw byte value). Only runtime mode exactly1, authority exactly0 and game mode exactly1 writes low argument BYTE to blue capture count77D6E1. No initialized check,
// normalization, increment, assist, carrier/timer mutation or broadcast. Guard rejection leaves count unchanged. Return EAX is incidental guard/game-mode result.
int __cdecl rf_client_ctf_blue_capture_byte_set(char a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = rf_multiplayer_game_mode_get();
    if ( result == 1 )
      byte_77D6E1 = a1;
  }
  return result;
}

