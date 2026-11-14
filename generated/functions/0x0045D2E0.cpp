// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D2E0 rf_multiplayer_setup_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl FULL keyDWORD,void. EXACT1 delegate467320. EXACT15 cycles focus6F2CF4++ with signed count wrap0;EXACT100F
// decrements and wraps count-1 when negative;both sound42 and clear editLatch6F2D01. EXACT28:if password-checkbox stateBYTE6F2E78 nonzero call callback6F2E90(-1,-1) WITHOUT NULL
// check;else if list stateBYTE6F333C nonzero toggle current row(-1,-1),then ensure-visible45D740. EXACT203/205 invoke nonNULL enabled left/right mode-arrow callback first,else
// player-count arrow,with(-1,-1). EXACT200/208 when list state nonzero move current row up/down,clamp respectively at0 or max(0,count-1),ensure visible,play46/47. Other NONZERO
// keys:server-name stateBYTE6F3118 has priority ->470A40(edit,key);else require password state6F36E0 and enabled6F36E1,call470A40 and ifALnonzero persist password Cstring6F3718 to
// registry ServerPassword. Only keyDWORD ZERO enters hotkey scan:for ALL focus-array controls whose DWORD28==0,set focused index,call467310,invoke nonNULL DWORD32 callback(-1,-1);no
// break,not a general nonzero-key hotkey scan. No own runtime/server admission,focus-index bounds/empty-focus-list rejection or credential validation. Native switch tables match
// these exact full values.
void __cdecl rf_multiplayer_setup_handle_key(int a1)
{
  int first_dword; // eax
  int v2; // eax
  int i; // [esp+Ch] [ebp-8h]

  if ( a1 > 203 )
  {
    switch ( a1 )
    {
      case 205:
        if ( unk_6F3418 && unk_6F3430 )
        {
          unk_6F3430(-1, -1);
        }
        else if ( unk_6F39B0 && unk_6F39C8 )
        {
          unk_6F39C8(-1, -1);
        }
        break;
      case 208:
        if ( unk_6F333C )
        {
          ++dword_6F2D08;
          if ( dword_6F2D08 >= rf_receiver_get_first_dword(dword_6F2DC4) )
          {
            first_dword = rf_receiver_get_first_dword(dword_6F2DC4);
            dword_6F2D08 = rf_int_max(0, first_dword - 1);
          }
          rf_multiplayer_level_scroll_ensure_current_row_visible();
          rf_gamesound_play_event(47, 0, 0.0, 1.0);
        }
        break;
      case 4111:
        if ( --dword_6F2CF4[0] < 0 )
          dword_6F2CF4[0] = rf_receiver_get_first_dword(dword_6F2EBC) - 1;
LABEL_16:
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
        unk_6F2D01 = 0;
        break;
      default:
LABEL_44:
        if ( a1 )
        {
          if ( unk_6F3118 )
          {
            rf_ui_edit_handle_key(byte_6F3110, a1);
          }
          else if ( unk_6F36E0 && unk_6F36E1 && rf_ui_edit_handle_key(byte_6F36D8, a1) )
          {
            rf_registry_write_cstring_without_terminator(nullptr, off_661EB8, &unk_6F3718);
          }
        }
        else
        {
          for ( i = 0; i < rf_receiver_get_first_dword(dword_6F2EBC); ++i )
          {
            if ( !*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, i) + 28) )
            {
              dword_6F2CF4[0] = i;
              rf_host_menu_pane_input_enable();
              if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, i) + 32) )
              {
                v2 = rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, dword_6F2CF4[0]);
                (*(void (__cdecl **)(int, int))(*(_DWORD *)v2 + 32))(-1, -1);
              }
            }
          }
        }
        break;
    }
  }
  else if ( a1 == 203 )
  {
    if ( unk_6F2DD8 && unk_6F2DF0 )
    {
      unk_6F2DF0(-1, -1);
    }
    else if ( unk_6F39F8 && unk_6F3A10 )
    {
      unk_6F3A10(-1, -1);
    }
  }
  else
  {
    switch ( a1 )
    {
      case 1:
        rf_host_menu_disable_pane_input_and_hide();
        break;
      case 15:
        ++dword_6F2CF4[0];
        if ( dword_6F2CF4[0] >= rf_receiver_get_first_dword(dword_6F2EBC) )
          dword_6F2CF4[0] = 0;
        goto LABEL_16;
      case 28:
        if ( unk_6F2E78 )
        {
          unk_6F2E90(-1, -1);
        }
        else if ( unk_6F333C )
        {
          rf_multiplayer_level_list_toggle_row(-1, -1);
          rf_multiplayer_level_scroll_ensure_current_row_visible();
        }
        break;
      case 200:
        if ( unk_6F333C )
        {
          if ( --dword_6F2D08 < 0 )
            dword_6F2D08 = 0;
          rf_multiplayer_level_scroll_ensure_current_row_visible();
          rf_gamesound_play_event(46, 0, 0.0, 1.0);
        }
        break;
      default:
        goto LABEL_44;
    }
  }
}

