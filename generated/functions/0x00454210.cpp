// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454210 rf_extras_menu_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl LOWBYTE suppressInput, rawEAX from453DC0. Only callerBYTE0 AND activeBYTE6F1DA8 ANY nonzero
// runs4477F0 with TWO raw slots(handler4542B0,0), cleans8, then454430 pointer helper. No own animation-readiness check; delegated input handlers own further gates. Regardless of
// input suppression/inactive state, loop signed0..<LIVE firstDWORD focus-list6F1F24 count, unchecked416F70, invoke virtual+8 ECX control/no stack args for every entry including
// disabled ones. Then read CURRENT selection6F1DAC and CURRENT list slot without bounds/NULL guard; invoke virtual+4 ECX selected control with NO explicit args (extra pointer in
// pseudocode is false signature inference); finally453DC0 integrates/draws. No active/focus/list validity recheck after event/pointer/virtual callbacks, no count/entry snapshot
// across callbacks, no parent pause/modal/resource validation or renderer restoration.
int __cdecl rf_extras_menu_frame(char a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( !a1 && unk_6F1DA8 )
  {
    rf_ui_poll_and_dispatch_event(rf_extras_menu_handle_input_event);
    rf_extras_menu_update_pointer();
  }
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F1F24); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
  }
  v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, dword_6F1DAC);
  (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
  return rf_extras_menu_integrate_x_positions_and_render();
}

