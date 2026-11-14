// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B530 rf_ui_dispatch_button_hit_6F3A60
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl(x,y). Call enabled-button hit test(x,y,global pointer-array6F3A60,countDWORD6F3AE0). If returned SIGNED index>=0,load
// button pointer and if callbackDWORD36 nonNULL call it cdecl with ORIGINAL(x,y). No own upper-index/buttonNULL check,coordinate transform,second enabled-state check or
// sound;delegate owns hit admission. Return signed hit index when no callback,otherwise callback EAX;not uniform bool. Registered as multiplayer setup UI callback by45BCD0.
int __cdecl rf_ui_dispatch_button_hit_6F3A60(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F3A60, dword_6F3AE0);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F3A60[result] + 36) )
      return (*(int (__cdecl **)(int, int))(unk_6F3A60[result] + 36))(physical_x, physical_y);
  }
  return result;
}

