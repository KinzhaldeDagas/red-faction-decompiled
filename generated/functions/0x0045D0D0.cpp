// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D0D0 rf_multiplayer_setup_level_list_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Hit-test6F3A60/count6F3AE0;nonnegative index and nonNULL hit DWORD32 callback ->call original(x,y). No
// independent control-state/upper-index/null checks or sound. Same table as prior45B530 but press callback offset32 instead of drag36. Return hit index or callback EAX;list
// selection/scroll/add-remove effects delegated.
int __cdecl rf_multiplayer_setup_level_list_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F3A60, dword_6F3AE0);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F3A60[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F3A60[result] + 32))(physical_x, physical_y);
  }
  return result;
}

