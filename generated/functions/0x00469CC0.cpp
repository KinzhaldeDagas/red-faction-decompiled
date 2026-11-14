// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469CC0 rf_performance_texture_group_press_apply
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Hit-test child pointers6F6C18/count6F6C98;nonnegative hit/nonnull callback32 ->TWO original(x,y),cleanup8. Then copy selected
// texture-resolutionDWORD6F6E54 to unchecked player3920;bitmap reduction setter1/2 for exact1/2,otherwise0. Finally apply_preset(3):marks Custom and commits ALL current UI
// tuple,including another bitmap reduction call. No changed-choice/bounds/player/state9 recheck,save or own sound. Missing hit/callback skips apply entirely. Keyboard arrow path
// calls child469D70/DA0 directly and bypasses this wrapper.
int __cdecl rf_performance_texture_group_press_apply(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F6C18, dword_6F6C98);
  if ( result >= 0 && *(_DWORD *)(unk_6F6C18[result] + 32) )
  {
    (*(void (__cdecl **)(int, int))(unk_6F6C18[result] + 32))(physical_x, physical_y);
    *(_DWORD *)(rf_local_fpgun_player + 3920) = unk_6F6E54;
    if ( unk_6F6E54 == 1 )
    {
      rf_bitmap_set_global_reduction_mode(1);
    }
    else if ( unk_6F6E54 == 2 )
    {
      rf_bitmap_set_global_reduction_mode(2);
    }
    else
    {
      rf_bitmap_set_global_reduction_mode(0);
    }
    return rf_performance_options_apply_preset(3);
  }
  return result;
}

