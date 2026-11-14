// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461EE0 rf_browser_filter_group_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(x,y). Hit-test child pointer array6F54D0 with count6F5550. Nonnegative hit and nonNULL callbackDWORD32 ->call with TWO ORIGINAL(x,y),caller cleanup8. No own count
// upper-bound/controlNULL/state9 recheck,sound or filter mutation;delegates own actual actions. EAX hit/callback residue.
int __cdecl rf_browser_filter_group_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F54D0, dword_6F5550);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F54D0[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F54D0[result] + 32))(physical_x, physical_y);
  }
  return result;
}

