// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F1C0 rf_multiplayer_rules_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Cdecl FULL keyDWORD,stored nominal int return retained as incidental. EXACT1 ->delegate467320;EXACT15 increments focus6F3AF0,wrap0 if signed>=focus-array6F4358
// count;EXACT100F decrements,wrapcount-1 only when negative;both sound42(0,0.0,1.0),no disabled-control skip or empty-list guard. EXACT28 reads focused control DWORD32 callback
// first,then requires controlBYTE9 nonzero;if admitted invokes callback(-1,-1). Sound43 occurs ALWAYS for Enter,even NULL/disabled callback. EXACT203 tries stateBYTE8+nonnull
// callback for previous-time,then previous-kills,then previous-captures;EXACT205 likewise next arrows in same priority,passing(-1,-1). Other keys ignored,no general hotkey scan/text
// editing. No runtime/authority/game-mode/key normalization or focus-index bounds;these routes manipulate UI choices/checkboxes only,not active server rules directly. EAX/AL not
// uniform consumed status.
void __cdecl rf_multiplayer_rules_handle_key(int a1)
{
  int v1; // eax

  if ( a1 > 203 )
  {
    if ( a1 == 205 )
    {
      if ( unk_6F3C70 && unk_6F3C88 )
      {
        unk_6F3C88(-1, -1);
      }
      else if ( unk_6F3F90 && unk_6F3FA8 )
      {
        unk_6F3FA8(-1, -1);
      }
      else if ( unk_6F3EF8 && unk_6F3F10 )
      {
        unk_6F3F10(-1, -1);
      }
    }
    else if ( a1 == 4111 )
    {
      if ( --dword_6F3AF0 < 0 )
        dword_6F3AF0 = rf_receiver_get_first_dword(unk_6F4358) - 1;
LABEL_14:
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
  }
  else if ( a1 == 203 )
  {
    if ( unk_6F4660 && unk_6F4678 )
    {
      unk_6F4678(-1, -1);
    }
    else if ( unk_6F3E38 && unk_6F3E50 )
    {
      unk_6F3E50(-1, -1);
    }
    else if ( unk_6F3FD8 && unk_6F3FF0 )
    {
      unk_6F3FF0(-1, -1);
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
        ++dword_6F3AF0;
        if ( dword_6F3AF0 >= rf_receiver_get_first_dword(unk_6F4358) )
          dword_6F3AF0 = 0;
        goto LABEL_14;
      case 28:
        if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F4358, dword_6F3AF0) + 32)
          && *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F4358, dword_6F3AF0) + 9) )
        {
          v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F4358, dword_6F3AF0);
          (*(void (__cdecl **)(int, int))(*(_DWORD *)v1 + 32))(-1, -1);
        }
        rf_gamesound_play_event(43, 0, 0.0, 1.0);
        break;
      default:
        return;
    }
  }
}

