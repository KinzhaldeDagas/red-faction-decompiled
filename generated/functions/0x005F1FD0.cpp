// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1FD0 rf_ui_checkbox_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall checkbox,key code. Saves prior visual state908,sets current0 even before hidden test. Hidden returns code. Blocked sets visual3,sound3 on primary press while hover or matching bound key,returns code. Otherwise bound hotkey or owner-navigation-target Enter28 toggles checked BYTE628,emits virtual+4 event19,arg-99999,consumes code0. If both owner hover and navigation targets match,held primary takes global keyboard focus and sets visual2,else1. Primary release with PRIOR visual2 and current hover toggles/emits19 regardless current navigation match. Keyboard and release paths can both toggle in one call. Returns final code;does not process children or explicitly release focus.
int __thiscall rf_ui_checkbox_process_input(_DWORD *this, int a2)
{
  int v4; // [esp+4h] [ebp-4h]

  v4 = *(this + 227);
  *(this + 227) = 0;
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) )
    return a2;
  if ( rf_ui_gadget_is_interaction_blocked(this) )
  {
    *(this + 227) = 3;
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target(this) )
      rf_ui_play_feedback_sound(3);
    if ( rf_ui_gadget_matches_bound_key(this, a2) )
      rf_ui_play_feedback_sound(3);
    return a2;
  }
  else
  {
    if ( rf_ui_gadget_matches_bound_key(this, a2) || rf_ui_gadget_is_owner_navigation_target(this) && a2 == 28 )
    {
      rf_ui_checkbox_toggle_checked(this);
      (*(void (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 19, -99999);
      a2 = 0;
    }
    if ( rf_ui_gadget_is_owner_hover_target(this) && rf_ui_gadget_is_owner_navigation_target(this) )
    {
      if ( rf_mouse_get_button_held_byte(0) )
      {
        rf_ui_gadget_take_keyboard_focus(this);
        *(this + 227) = 2;
      }
      else
      {
        *(this + 227) = 1;
      }
    }
    if ( unk_1CF7591 && v4 == 2 && rf_ui_gadget_is_owner_hover_target(this) )
    {
      rf_ui_checkbox_toggle_checked(this);
      (*(void (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 19, -99999);
    }
    return a2;
  }
}

