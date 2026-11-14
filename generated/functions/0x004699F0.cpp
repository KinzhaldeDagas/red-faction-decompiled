// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004699F0 rf_performance_options_group_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Hit-test child pointer array6F7080/count6F7100;signed nonnegative hit/nonnull callbackDWORD32 ->TWO original(x,y),cleanup8. No own
// upper-index/controlNULL/state9 recheck,sound,preset or rendering mutation;delegates own changes.
int __cdecl rf_performance_options_group_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F7080, dword_6F7100);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F7080[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F7080[result] + 32))(physical_x, physical_y);
  }
  return result;
}

