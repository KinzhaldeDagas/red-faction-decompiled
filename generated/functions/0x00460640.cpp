// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460640 rf_multiplayer_profile_previous_character
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Decrement raw selected index6F4AD8;only signed negative wraps to characterCount-1. Store result into unguarded localPlayerDWORD3932 (F5C),return same
// indexEAX. No positive-count/upper-index/pointer/runtime guard,sound,dirty-name flag or explicit network update. Zero character count can produce-1;does not independently repair
// corrupt high index.
int rf_multiplayer_profile_previous_character()
{
  int result; // eax

  if ( --dword_6F4AD8 < 0 )
    dword_6F4AD8 = rf_multiplayer_character_count - 1;
  result = dword_6F4AD8;
  *(_DWORD *)(rf_local_fpgun_player + 3932) = dword_6F4AD8;
  return result;
}

