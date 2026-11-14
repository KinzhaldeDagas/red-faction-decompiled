// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004605E0 rf_multiplayer_profile_character_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(x,y). Clear edit-latch6F4AD5 BEFORE hit test against6F4F10/count6F4F90. Signed nonnegative hit and nonNULL control DWORD32 callback ->invoke
// ORIGINAL(x,y),return callbackEAX;else raw hit index. No own upper-index/controlNULL/BYTE9 check,sound,character assignment or profile-input test. Child arrows/portrait callback
// owns change.
int __cdecl rf_multiplayer_profile_character_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  unk_6F4AD5 = 0;
  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F4F10, dword_6F4F90);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F4F10[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F4F10[result] + 32))(physical_x, physical_y);
  }
  return result;
}

