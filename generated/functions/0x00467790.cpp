// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467790 rf_options_menu_update_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl suppressInputLOWBYTE. FIRST clear focusBYTE8 on exactly5 contiguous68-byte buttons6F6110,even inactive/suppressed. Only suppress0 AND mainInput6F602C
// nonzero:poll_dispatch(handler467810,0),TWO native args;pointer467B70;then if paneInput6F6000==0,set focused main button atunchecked focus6F5FFC. No main virtual+8/+4 loop here.
// Always animate/draw467CE0 afterward,including suppressed/inactive states;draw return residue.
int __cdecl rf_options_menu_update_and_draw(char a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 5; ++i )
    rf_ui_button_clear_focus((_BYTE *)&unk_6F6110 + 68 * i);
  if ( !a1 )
  {
    if ( unk_6F602C )
    {
      rf_ui_poll_and_dispatch_event(rf_options_menu_handle_key);
      rf_options_menu_update_pointer();
      if ( !unk_6F6000 )
        rf_ui_button_set_focus((_BYTE *)&unk_6F6110 + 68 * unk_6F5FFC);
    }
  }
  return rf_options_menu_animate_and_draw();
}

