// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460680 rf_multiplayer_profile_next_character
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Increment index6F4AD8;if signed newIndex>=characterCount store0;then unguarded localPlayerDWORD3932=index,return index. No
// count-positive/negative-index/pointer/runtime guard,sound or explicit broadcast/name-dirty mutation. Empty count still stores0;arithmetic native32-bit.
int rf_multiplayer_profile_next_character()
{
  int result; // eax

  if ( ++dword_6F4AD8 >= rf_multiplayer_character_count )
    dword_6F4AD8 = 0;
  result = dword_6F4AD8;
  *(_DWORD *)(rf_local_fpgun_player + 3932) = dword_6F4AD8;
  return result;
}

