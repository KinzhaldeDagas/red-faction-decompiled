// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468730 rf_controls_binding_group_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). BOTH coordinates strictlynegative ->direct action_list_press468320(x,y),without child hit-test. Otherwise hit-test child
// array6F64E0/count6F6560;nonnegative hit/nonnull callbackDWORD32 ->TWO ORIGINAL(x,y),cleanup8. Zero or only one negative coordinate does not take sentinel shortcut. No own
// upper-index/controlNULL/state9 check,sound or capture/selection guard.
int __cdecl rf_controls_binding_group_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-4h]

  if ( physical_x < 0 && physical_y < 0 )
    return (int)rf_controls_action_list_press(physical_x, physical_y);
  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F64E0, dword_6F6560);
  v3 = result;
  if ( result >= 0 )
  {
    result = unk_6F64E0[result];
    if ( *(_DWORD *)(result + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F64E0[v3] + 32))(physical_x, physical_y);
  }
  return result;
}

