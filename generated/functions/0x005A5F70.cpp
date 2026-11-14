// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5F70 rf_text_list_poll_scrollbar_actions
// UNREALRED VERIFIED [text-layout-20261029]: Horizontal bar list+788 first: tests child pointers+672/+676 through action predicate0x5EFE10,dispatches0x5A78C0/0x5A7890 and RETURNS EARLY on either action. Otherwise if bar position differs from list scrollX+708,calls X setter0x5A87B0 and copies clamped value back. Then vertical bar+784 tests same child fields,dispatches0x5A7D20/0x5A7B00; else differing position calls Y setter0x5A8830(value,0),copies resulting scrollY+712 back. Action predicate gates virtual state and accepts codes6/8; no event dequeue here. Return low byte is incidental helper/this/position,not reliable did-scroll boolean.
char __thiscall rf_text_list_poll_scrollbar_actions(int *this)
{
  int v1; // eax
  int position; // eax
  int v3; // eax

  if ( *(this + 197) )
  {
    if ( *(_DWORD *)(*(this + 197) + 672) && rf_ui_button_is_primary_activation_state(*(_DWORD **)(*(this + 197) + 672)) )
    {
      LOBYTE(v1) = (unsigned __int8)rf_text_list_scroll_right_step(this);
      return v1;
    }
    if ( *(_DWORD *)(*(this + 197) + 676) && rf_ui_button_is_primary_activation_state(*(_DWORD **)(*(this + 197) + 676)) )
    {
      LOBYTE(v1) = (unsigned __int8)rf_text_list_scroll_left_step(this);
      return v1;
    }
    if ( *(this + 177) != rf_scrollbar_get_position((_DWORD *)*(this + 197)) )
    {
      position = rf_scrollbar_get_position((_DWORD *)*(this + 197));
      rf_text_list_set_scroll_x(this, position);
      rf_scrollbar_set_position_unclamped((_DWORD *)*(this + 197), *(this + 177));
    }
  }
  LOBYTE(v1) = (_BYTE)this;
  if ( *(this + 196) )
  {
    if ( *(_DWORD *)(*(this + 196) + 672) && rf_ui_button_is_primary_activation_state(*(_DWORD **)(*(this + 196) + 672)) )
    {
      LOBYTE(v1) = rf_text_list_scroll_next_line_or_block(this);
    }
    else if ( *(_DWORD *)(*(this + 196) + 676)
           && rf_ui_button_is_primary_activation_state(*(_DWORD **)(*(this + 196) + 676)) )
    {
      LOBYTE(v1) = rf_text_list_scroll_previous_line_or_block(this);
    }
    else
    {
      v1 = rf_scrollbar_get_position((_DWORD *)*(this + 196));
      if ( *(this + 178) != v1 )
      {
        v3 = rf_scrollbar_get_position((_DWORD *)*(this + 196));
        rf_text_list_set_scroll_y_with_optional_snap(this, v3, 0);
        LOBYTE(v1) = (unsigned __int8)rf_scrollbar_set_position_unclamped((_DWORD *)*(this + 196), *(this + 178));
      }
    }
  }
  return v1;
}

