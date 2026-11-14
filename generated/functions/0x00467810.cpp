// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467810 rf_options_menu_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl FULL keyDWORD,initially untyped ABI preserved. PaneInput6F6000 nonzero:currentPane661FF4 unsigned0..3 routes0->46C700 Game,1->46AE70 Video,2->46D310 Audio
// (raw keyVALUE),3->4691E0 Controls(ADDRESS of own key stack slot);other pane values no-op. No main keys while paneInput. Main mode:200/100F focus previous;208/15 next;1 activate
// index4 Back;28 activate unchecked focus6F5FFC. Other keys scan EXACT5 button DWORD28 hotkeys,stride68;first match sets focus then activates index,no BYTE9 enabled check. No key
// normalization or own mainInput/readiness check;driver owns gate. Controls may overwrite only this local key slot via pointer.
int __cdecl rf_options_menu_handle_key(int a1)
{
  int result; // eax
  int i; // [esp+8h] [ebp-4h]

  result = byte_6F6000[0];
  if ( byte_6F6000[0] )
  {
    switch ( dword_661FF4 )
    {
      case 0:
        result = rf_gameplay_handle_key(a1);
        break;
      case 1:
        result = rf_performance_handle_key(a1);
        break;
      case 2:
        result = rf_audio_handle_key(a1);
        break;
      case 3:
        result = rf_controls_handle_key_pointer(&a1);
        break;
      default:
        result = byte_6F6000[0];
        break;
    }
    return result;
  }
  if ( a1 <= 200 )
  {
    if ( a1 != 200 )
    {
      if ( a1 == 1 )
        return rf_options_menu_activate_item(4);
      if ( a1 != 15 )
      {
        if ( a1 == 28 )
          return rf_options_menu_activate_item(dword_6F5FFC);
        goto LABEL_14;
      }
      return rf_options_menu_focus_next();
    }
    return rf_options_menu_focus_previous();
  }
  if ( a1 == 208 )
    return rf_options_menu_focus_next();
  if ( a1 == 4111 )
    return rf_options_menu_focus_previous();
LABEL_14:
  for ( i = 0; i < 5; ++i )
  {
    if ( unk_6F612C[17 * i] == a1 )
    {
      dword_6F5FFC = i;
      return rf_options_menu_activate_item(i);
    }
    result = i + 1;
  }
  return result;
}

