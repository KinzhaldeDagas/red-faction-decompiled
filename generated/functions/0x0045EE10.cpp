// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045EE10 rf_multiplayer_rules_capture_limit_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Native cdecl(x,y),explicit verified prototype added where no stored type existed. Enabled-button hit-test(table6F4710,countDWORD6F4790,originalx/y);signed index>=0 and
// hit control DWORD32 callback nonNULL ->invoke with ORIGINAL(x,y),return callbackEAX. Otherwise return raw hit index. No extra upper-index/controlNULL/BYTE9 test,sound,choice
// mutation or gameplay-rule apply in wrapper;child callback owns capture-choice changes. Physical RET has no immediate;caller owns argument cleanup.
int __cdecl rf_multiplayer_rules_capture_limit_press_dispatch(int x, int y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(x, y, (void *const *)unk_6F4710, dword_6F4790);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F4710[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F4710[result] + 32))(x, y);
  }
  return result;
}

