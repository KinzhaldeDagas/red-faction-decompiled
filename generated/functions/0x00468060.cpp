// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468060 rf_controls_sensitivity_group_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Hit-test child pointer array6F67A0/count6F6820;signed nonnegative hit/nonnull callbackDWORD32 ->TWO ORIGINAL(x,y),cleanup8. Used for both parent
// press/drag fields;both dispatch child's PRESS callback32. No own upper-index/controlNULL/state9 recheck,sound or sensitivity mutation. EAX hit/callback residue.
int __cdecl rf_controls_sensitivity_group_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F67A0, dword_6F6820);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F67A0[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F67A0[result] + 32))(physical_x, physical_y);
  }
  return result;
}

