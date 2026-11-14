// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004687B0 rf_controls_binding_group_drag_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Hit-test child array6F64E0/count6F6560;nonnegative hit/nonnull callbackDWORD36 ->TWO original(x,y),cleanup8. No sentinel shortcut,press-callback
// fallback,own bounds/state9 recheck,sound or binding change. Child slider owns mutation.
int __cdecl rf_controls_binding_group_drag_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F64E0, dword_6F6560);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F64E0[result] + 36) )
      return (*(int (__cdecl **)(int, int))(unk_6F64E0[result] + 36))(physical_x, physical_y);
  }
  return result;
}

