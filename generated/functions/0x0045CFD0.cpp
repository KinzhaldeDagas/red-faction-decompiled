// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CFD0 rf_multiplayer_setup_password_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Hit-test6F2F90/count6F3010. Only signed nonnegative index,hit BYTE9 NONZERO,and hit DWORD32 callback
// nonNULL ->invoke original(x,y). Additional BYTE9 predicate is real here,unlike other press wrappers. No controlNULL/upper-index guard or own password change/validation. Return
// callback EAX or raw hit index,not normalized admission.
int __cdecl rf_multiplayer_setup_password_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F2F90, dword_6F3010);
  if ( result >= 0 && *(_BYTE *)(unk_6F2F90[result] + 9) )
  {
    if ( *(_DWORD *)(unk_6F2F90[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F2F90[result] + 32))(physical_x, physical_y);
  }
  return result;
}

