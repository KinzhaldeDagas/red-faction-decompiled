// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046A150 rf_performance_gamma_group_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Hit-test child pointers6F6AD8/count6F6B58;nonnegative hit/nonnull callbackDWORD32 ->TWO ORIGINAL(x,y),cleanup8. Builder uses same wrapper
// for parent press AND drag,so both dispatch child PRESS field32. No own upper-index/controlNULL/state9 recheck,gamma calculation,save or sound;child46A1B0 owns change.
int __cdecl rf_performance_gamma_group_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F6AD8, dword_6F6B58);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F6AD8[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F6AD8[result] + 32))(physical_x, physical_y);
  }
  return result;
}

