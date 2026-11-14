// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004564C0 rf_save_list_b_dispatch_edit_group_click
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(x,y). Calls458BE0(x,y,pointer table6F25E0,countDWORD6F2660). Negative hit returns hit. Nonnegative hit fetches child, tests callbackDWORD+32, then
// re-fetches child/callback and invokes with TWO cdecl(x,y) stack arguments, ADD8, forwarding EAX. Null callback returns incidental pointer/residue. No own upper-hit bound, child
// NULL guard, enabled/selection/sound action or normalized Boolean.
int __cdecl rf_save_list_b_dispatch_edit_group_click(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)&unk_6F25E0, dword_6F2660);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(*((_DWORD *)&unk_6F25E0 + result) + 32) )
      return (*(int (__cdecl **)(int, int))(*((_DWORD *)&unk_6F25E0 + result) + 32))(physical_x, physical_y);
  }
  return result;
}

