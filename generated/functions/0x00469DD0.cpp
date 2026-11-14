// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469DD0 rf_performance_character_detail_group_press_apply
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Hit-test6F78F8/count6F7978;nonnegative hit/nonnull callback32 ->TWO original(x,y). Then selected character-detailDWORD6F7504 ->player3924
// AND global1C99890,then apply_preset(3) commits all current UI fields/Custom. Does not itself validate indices,player,capability or changed choice/save. Keyboard calls
// leaf469E50/E80 directly and bypasses apply. Native builder fallback Character Detail establishes semantic label.
int __cdecl rf_performance_character_detail_group_press_apply(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F78F8, dword_6F7978);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F78F8[result] + 32) )
    {
      (*(void (__cdecl **)(int, int))(unk_6F78F8[result] + 32))(physical_x, physical_y);
      *(_DWORD *)(rf_local_fpgun_player + 3924) = unk_6F7504;
      unk_1C99890 = unk_6F7504;
      return rf_performance_options_apply_preset(3);
    }
  }
  return result;
}

