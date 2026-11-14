// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CE30 rf_multiplayer_setup_game_mode_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Hit-test enabled buttons in6F3088/count6F3108;nonnegative index and nonNULL hit DWORD32 callback
// ->invoke with original(x,y),return callback EAX. Otherwise raw hit index. No extra bounds,controlNULL,state9 guard,sound or mode mutation in wrapper;child callback owns
// cycling/filter rebuild.
int __cdecl rf_multiplayer_setup_game_mode_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F3088, dword_6F3108);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F3088[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F3088[result] + 32))(physical_x, physical_y);
  }
  return result;
}

