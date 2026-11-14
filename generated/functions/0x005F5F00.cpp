// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F5F00 rf_ui_radio_button_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Saves visual908,sets it0 before hidden check. Hidden returns code;blocked sets3,sound2 on hovered primary press or bound key match,returns. Keyboard bound key or navigation-target Enter28 iterates ALL children of parent616 and writes checked BYTE628=0 via checkbox setter WITHOUT type filter,then toggles this to1,consumes key0 and DOES NOT emit event19. This can overwrite byte628 of unrelated sibling gadget types. Hover+navigation:checked or primary not held setsvisual1;otherwise takes global keyboard focus,setsvisual2. Primary release with PRIOR visual2 and current hover iterates siblings but this time clears ONLY type5 radio buttons,then toggles this and emits virtual+4 event19,arg-99999. No parent NULL guard. Both keyboard and mouse paths may execute same call;returns final code.
int __thiscall rf_ui_radio_button_process_input(_DWORD *this, int a2)
{
  int v4; // [esp+4h] [ebp-8h]
  _DWORD *i; // [esp+8h] [ebp-4h]
  _DWORD *j; // [esp+8h] [ebp-4h]

  v4 = *(this + 227);
  *(this + 227) = 0;
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) )
    return a2;
  if ( rf_ui_gadget_is_interaction_blocked(this) )
  {
    *(this + 227) = 3;
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target(this) )
      rf_ui_play_feedback_sound(2);
    if ( rf_ui_gadget_matches_bound_key(this, a2) )
      rf_ui_play_feedback_sound(2);
    return a2;
  }
  else
  {
    if ( rf_ui_gadget_matches_bound_key(this, a2) || rf_ui_gadget_is_owner_navigation_target(this) && a2 == 28 )
    {
      for ( i = (_DWORD *)rf_ui_gadget_get_first_child((_DWORD *)*(this + 154));
            i;
            i = (_DWORD *)rf_ui_gadget_get_next_sibling(i) )
      {
        rf_ui_checkbox_set_checked_raw(i, 0);
      }
      rf_ui_checkbox_toggle_checked(this);
      a2 = 0;
    }
    if ( rf_ui_gadget_is_owner_hover_target(this) && rf_ui_gadget_is_owner_navigation_target(this) )
    {
      if ( rf_ui_checkbox_get_checked_raw(this) || !rf_mouse_get_button_held_byte(0) )
      {
        *(this + 227) = 1;
      }
      else
      {
        rf_ui_gadget_take_keyboard_focus(this);
        *(this + 227) = 2;
      }
    }
    if ( unk_1CF7591 && v4 == 2 && rf_ui_gadget_is_owner_hover_target(this) )
    {
      for ( j = (_DWORD *)rf_ui_gadget_get_first_child((_DWORD *)*(this + 154));
            j;
            j = (_DWORD *)rf_ui_gadget_get_next_sibling(j) )
      {
        if ( rf_ui_gadget_get_type(j) == 5 )
          rf_ui_checkbox_set_checked_raw(j, 0);
      }
      rf_ui_checkbox_toggle_checked(this);
      (*(void (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 19, -99999);
    }
    return a2;
  }
}

