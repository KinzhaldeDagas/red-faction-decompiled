// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6120 rf_text_list_process_input
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall list,input code. Virtual predicate vtable+16 true returns code unchanged. Otherwise reflows dirty blocks and updates scrollbar enabled state via0x5F1260/0x5F1210 according to content exceeding inner viewport. Gate0x5AB8F0 branch invokes global helper0x5A9720(7) on selected mouse/key conditions and returns original code. Other branch preprocesses through0x5AB750,polls scrollbar actions. Mouse press global0x1CF7593 plus0x5ABC00 and flags+628 mask8 clear selects block under local mouse coordinates inside padded bounds; new selection emits virtual+4(event24,-99999),same selection plus0x1CF75C4 emits25;sets BYTE+688. Calls0x5ABB50 afterward. Type-ahead count+664 expires when signed elapsed helper0x55F3B0(deadline+668)>1500. Only when list==global focus0x1CF75D8,positive/negative wheel globals invoke scroll0x5A7B00/0x5A7D20. Codes200/208
// select previous/next,201/209 page previous/next,203/205 scroll X;these set return code0. Other codes14/28 clear type-ahead count;otherwise while count<32 strips bit0x1000,converts through0x58B980,appends non255 byte into buffer+632 and resets deadline offset0. Scans entries comparing tolower(entry byte) against stored prefix bytes,count-limited (no NUL appended);first match selects/reveals entry and emits24. Does not normalize prefix bytes explicitly. Return is preprocessed/possibly modified input code,not boolean handled. Shared global mouse/focus state and synchronous virtual callbacks; no pointer/lifetime validation around notifications.
int __thiscall rf_text_list_process_input(int *this, int a2)
{
  int v3; // edx
  int j; // [esp+8h] [ebp-1Ch]
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int *i; // [esp+14h] [ebp-10h]
  _DWORD *block_at_content_position; // [esp+18h] [ebp-Ch]
  int v10; // [esp+1Ch] [ebp-8h]
  int v11; // [esp+20h] [ebp-4h]
  int v12; // [esp+2Ch] [ebp+8h]

  if ( (*(unsigned __int8 (__thiscall **)(int *))(*this + 16))(this) )
    return a2;
  rf_text_list_reflow_dirty_blocks(this);
  if ( *(this + 196) )
  {
    if ( *(this + 171) > rf_text_list_inner_height(this) )
      rf_ui_base_set_enabled((_BYTE *)*(this + 196), v3, 1);
    else
      rf_ui_base_set_disabled_raw((_BYTE *)*(this + 196), 1);
  }
  if ( *(this + 197) )
  {
    if ( *(this + 170) > rf_text_list_inner_width(this) )
      rf_ui_base_set_enabled((_BYTE *)*(this + 197), (int)this, 1);
    else
      rf_ui_base_set_disabled_raw((_BYTE *)*(this + 197), 1);
  }
  if ( rf_ui_gadget_is_interaction_blocked(this) )
  {
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target(this) )
      rf_ui_play_feedback_sound(7);
    if ( rf_ui_gadget_matches_bound_key(this, a2) )
      rf_ui_play_feedback_sound(7);
    return a2;
  }
  else
  {
    v12 = rf_ui_gadget_process_children_input(this, a2);
    rf_text_list_poll_scrollbar_actions(this);
    if ( rf_ui_gadget_is_owner_hover_target(this) && unk_1CF7593 )
    {
      if ( (*(this + 157) & 8) == 0 )
      {
        v10 = unk_1CF7594 - rf_ui_gadget_absolute_x(this, 0);
        v11 = unk_1CF75C0 - rf_ui_gadget_absolute_y(this, 0);
        if ( v10 >= *(this + 175)
          && v10 < *(this + 5) - *(this + 175)
          && v11 >= *(this + 176)
          && v11 < *(this + 6) - *(this + 176) )
        {
          block_at_content_position = rf_text_list_find_block_at_content_position(this, 0, *(this + 178) + v11, 0);
          if ( block_at_content_position )
          {
            if ( (_DWORD *)*(this + 173) == block_at_content_position )
            {
              if ( unk_1CF75C4 )
                (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 25, -99999);
            }
            else
            {
              *(this + 173) = (int)block_at_content_position;
              (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 24, -99999);
            }
            *((_BYTE *)this + 688) = 1;
          }
        }
      }
      rf_ui_gadget_take_keyboard_focus(this);
    }
    if ( *(this + 166) > 0 && rf_clock_deadline_elapsed_signed_half_period(this + 167) > 1500 )
      *(this + 166) = 0;
    if ( this == (int *)unk_1CF75D8 )
    {
      if ( unk_1CF7598 <= 0 )
      {
        if ( unk_1CF7598 < 0 )
          rf_text_list_scroll_next_line_or_block(this);
      }
      else
      {
        rf_text_list_scroll_previous_line_or_block(this);
      }
      if ( v12 )
      {
        switch ( v12 )
        {
          case 200:
            rf_text_list_select_previous_or_scroll_up(this);
            v12 = 0;
            break;
          case 201:
            rf_text_list_page_select_previous((int)this);
            v12 = 0;
            break;
          case 203:
            rf_text_list_scroll_left_step(this);
            v12 = 0;
            break;
          case 205:
            rf_text_list_scroll_right_step(this);
            v12 = 0;
            break;
          case 208:
            rf_text_list_select_next_or_scroll_down(this);
            v12 = 0;
            break;
          case 209:
            rf_text_list_page_select_next((int)this);
            v12 = 0;
            break;
          default:
            if ( v12 == 14 || v12 == 28 )
            {
              *(this + 166) = 0;
            }
            else if ( *(this + 166) < 32 )
            {
              v12 &= ~0x1000u;
              v7 = rf_input_keycode_to_character(v12);
              if ( v7 != 255 )
              {
                *((_BYTE *)this + (*(this + 166))++ + 632) = v7;
                rf_clock_deadline_set_wrapped_offset(this + 167, 0);
              }
            }
            if ( *(this + 166) )
            {
              for ( i = (int *)*(this + 183); i != this + 181; i = (int *)i[2] )
              {
                v6 = i[12];
                for ( j = 0; j < *(this + 166) && tolower(*(char *)(j + v6)) == *((char *)this + j + 632); ++j )
                  ;
                if ( j == *(this + 166) )
                {
                  rf_text_list_select_entry_optional_reveal(this, (int)i, 1);
                  (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 24, -99999);
                  return v12;
                }
              }
            }
            break;
        }
      }
    }
    return v12;
  }
}

