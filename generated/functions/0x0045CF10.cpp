// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CF10 rf_multiplayer_setup_player_count_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Hit-test6F3388/count6F3408;nonnegative index,nonnull hit DWORD32 callback ->invoke original(x,y),return
// its EAX. Otherwise return hit index. No own upper bound,pointer/state9 recheck,sound or player-count assignment;child previous/next helpers own choice update.
int __cdecl rf_multiplayer_setup_player_count_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F3388, dword_6F3408);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F3388[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F3388[result] + 32))(physical_x, physical_y);
  }
  return result;
}

