// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046CD90 rf_audio_effects_group_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Hit-test child pointers6F85F8/count6F8678;nonnegative hit/nonnull callbackDWORD32 ->TWO ORIGINAL(x,y),cleanup8. Same wrapper used for
// group press AND drag,so both dispatch child PRESS field32. No own upper-index/controlNULL/state9 recheck,channel apply,sound or save;child owns live gain change.
int __cdecl rf_audio_effects_group_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F85F8, dword_6F8678);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F85F8[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F85F8[result] + 32))(physical_x, physical_y);
  }
  return result;
}

