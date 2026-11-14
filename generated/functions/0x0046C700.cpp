// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046C700 rf_gameplay_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl FULL keyDWORD;PE selector/jump tables verified.1 disable/hide OPTIONS pane/sound43.15 focus6F7B80++/wrap focus-list6F8398 count;100F
// decrement/negative wrapcount-1;always42,NO disabled skip/empty-count guard.28 nonnull focused callback32 getsTWO(-1,-1),then43;NO BYTE9 guard.203/205 only difficulty
// chooserBYTE8(6F7DF0) nonzero/arrowcallback nonNULL:call leaf previous6F7F78/next6F82F8 TWO(-1,-1),bypassing group commit46B5C0;display choice changes but configured/active
// difficulty not directly updated here.200/208 only priority-listBYTE8(6F7C9C) nonzero:decrement selected/clamp0 or increment/clamp(count-1),ensurevisible,sound46/47;empty count may
// set-1. Raw40C8/40D0 (16584/16592):same listBYTE gate,move selected UP/DOWN with TWO ignored(-1,-1),sound46/47 even no swap. Other keys:first focus-list DWORD28 hotkey match stores
// focus,virtual+4 ECX/noargs,nonnull callback32 TWO(0,0),sound43;no BYTE9 check,further match or key normalization. Callback cleanup4 reuses second coordinate as sound gain. No
// player/focus bounds/mainInput/paneInput/selection-capacity checks or save;parent owns input admission.
int __cdecl rf_gameplay_handle_key(int a1)
{
  int result; // eax
  int v2; // eax
  _DWORD *v3; // eax
  int v4; // eax
  int i; // [esp+10h] [ebp-4h]

  result = a1;
  if ( a1 <= 205 )
  {
    if ( a1 == 205 )
    {
      if ( byte_6F7DF0[0] && unk_6F82F8 )
        return unk_6F82F8(-1, -1);
    }
    else
    {
      switch ( a1 )
      {
        case 1:
          rf_options_menu_disable_pane_input_and_hide();
          result = rf_gamesound_play_event(43, 0, 0.0, 1.0);
          break;
        case 15:
          ++dword_6F7B80;
          if ( dword_6F7B80 >= rf_receiver_get_first_dword(dword_6F8398) )
            dword_6F7B80 = 0;
          return rf_gamesound_play_event(42, 0, 0.0, 1.0);
        case 28:
          result = rf_inline_dword_array4_element_address_unchecked(dword_6F8398, dword_6F7B80);
          if ( *(_DWORD *)(*(_DWORD *)result + 32) )
          {
            v2 = rf_inline_dword_array4_element_address_unchecked(dword_6F8398, dword_6F7B80);
            (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(-1);
            result = rf_gamesound_play_event(43, 0, 0.0, 1.0);
          }
          break;
        case 200:
          if ( byte_6F7C9C[0] )
          {
            --unk_6F7B88;
            if ( unk_6F7B88 < 0 )
              unk_6F7B88 = 0;
            rf_gameplay_priority_ensure_selected_visible();
            result = rf_gamesound_play_event(46, 0, 0.0, 1.0);
          }
          break;
        case 203:
          result = byte_6F7DF0[0];
          if ( byte_6F7DF0[0] && unk_6F7F78 )
            result = unk_6F7F78(-1, -1);
          break;
        default:
          goto LABEL_45;
      }
    }
    return result;
  }
  if ( a1 > 16584 )
  {
    if ( a1 == 16592 )
    {
      if ( byte_6F7C9C[0] )
      {
        rf_gameplay_priority_move_selected_down();
        return rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
      return result;
    }
  }
  else
  {
    switch ( a1 )
    {
      case 16584:
        if ( byte_6F7C9C[0] )
        {
          rf_gameplay_priority_move_selected_up();
          return rf_gamesound_play_event(46, 0, 0.0, 1.0);
        }
        return result;
      case 208:
        result = byte_6F7C9C[0];
        if ( byte_6F7C9C[0] )
        {
          ++unk_6F7B88;
          if ( unk_6F7B88 >= dword_6F7B7C )
            unk_6F7B88 = dword_6F7B7C - 1;
          rf_gameplay_priority_ensure_selected_visible();
          return rf_gamesound_play_event(47, 0, 0.0, 1.0);
        }
        return result;
      case 4111:
        if ( --dword_6F7B80 < 0 )
          dword_6F7B80 = rf_receiver_get_first_dword(dword_6F8398) - 1;
        return rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
  }
LABEL_45:
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F8398);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F8398, i) + 28) == a1 )
    {
      dword_6F7B80 = i;
      v3 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F8398, i);
      (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v3 + 4))(*v3, *v3);
      result = rf_inline_dword_array4_element_address_unchecked(dword_6F8398, i);
      if ( *(_DWORD *)(*(_DWORD *)result + 32) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(dword_6F8398, i);
        (*(void (__cdecl **)(_DWORD))(*(_DWORD *)v4 + 32))(0);
        return rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      return result;
    }
  }
  return result;
}

