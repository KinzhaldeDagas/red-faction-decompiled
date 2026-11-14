// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B470 rf_multiplayer_chat_begin_mode
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl raw modeDWORD,original unsigned prototype preserved but native uses signed comparisons: reject mode<0 or>=2. For mode1
// only require game-mode getter NONZERO,not exact CTF/team2;this check occurs before runtime gate. Mode0 bypasses game-mode query. Require runtimeBYTE EXACT1,then store
// activeBYTE6F2CC8=1 followed by modeDWORD6F2CC4=arg. No immediate input-string clear,init-byte reset,throttle reset,key reset,sound or authority gate. Reentry can switch stored mode
// while retaining buffer/init; prompt only clears if init byte is already zero.
void __cdecl rf_multiplayer_chat_begin_mode(unsigned int a1)
{
  if ( a1 < 2 && (a1 != 1 || rf_multiplayer_game_mode_get()) && rf_multiplayer_runtime_mode == 1 )
  {
    unk_6F2CC8 = 1;
    unk_6F2CC4 = a1;
  }
}

