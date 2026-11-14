// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455E90 rf_frontend_a_frame_dispatch_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one DWORD LOWBYTE option. Only option0 calls4477F0(callback454ED0,extraDWORD0), then4551F0. Always loops i0..<LIVE486DE0(6F22FC), fetching pointer
// through416F70 and calling vtable+8 with ECX=object and NO explicit stack arguments. Then clears button6F2318 focus455F90. Option0 fetches selected index6F1F88 without
// bounds/count/NULL validation and invokes vtable+4 with ECX=object, again NO explicit arguments despite duplicated-self pseudocode. Afterwards nonzero BYTE6F2364 sets6F2318
// focus449B00. Always calls455370 layout/draw, forwards EAX. Count/objects can change through virtual calls; no snapshot, reentrancy protection or own readiness gate.
int __cdecl rf_frontend_a_frame_dispatch_and_draw(char a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( !a1 )
  {
    rf_ui_poll_and_dispatch_event(rf_save_list_a_handle_input_event);
    rf_save_list_a_update_pointer();
  }
  for ( i = 0; i < rf_receiver_get_first_dword(byte_6F22FC); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
  }
  rf_ui_button_clear_focus(&dword_6F2318);
  if ( !a1 )
  {
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, dword_6F1F88);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
    if ( unk_6F2364 )
      rf_ui_button_set_focus(&dword_6F2318);
  }
  return rf_save_list_a_animate_and_draw();
}

