// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B860 rf_gameplay_priority_group_drag_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Hit-test same child array6F8208/count6F8288;nonnegative hit/nonnull callbackDWORD36 ->TWO original(x,y),cleanup8. No press-field
// fallback,sentinel handling,own bounds/state9 recheck or sound. Child drag/slider owns changes.
int __cdecl rf_gameplay_priority_group_drag_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F8208, dword_6F8288);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F8208[result] + 36) )
      return (*(int (__cdecl **)(int, int))(unk_6F8208[result] + 36))(physical_x, physical_y);
  }
  return result;
}

