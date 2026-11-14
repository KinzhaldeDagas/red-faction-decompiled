// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B800 rf_gameplay_priority_group_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Hit-test child pointers6F8208/count6F8288;signed nonnegative hit/nonnull callbackDWORD32 ->TWO ORIGINAL(x,y),cleanup8. No own
// upper-index/controlNULL/state9 recheck,sound,priority swap or sentinel shortcut. Child list/slider owns changes.
int __cdecl rf_gameplay_priority_group_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F8208, dword_6F8288);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F8208[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F8208[result] + 32))(physical_x, physical_y);
  }
  return result;
}

