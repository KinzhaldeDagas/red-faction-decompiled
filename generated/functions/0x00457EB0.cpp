// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457EB0 rf_frontend_b_frame_dispatch_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one DWORD LOWBYTE option. Option0 polls4477F0(callback457010,extraDWORD0), then457470. Always iterates signed i0..<LIVE486DE0(6F28EC), fetching
// via416F70 and invoking vtable+8 with ECXobject, NO explicit arguments. Clears focus on6F2668. Option0 unchecked-fetches index6F23D4 and invokes vtable+4 with ECXobject, NO explicit
// argument despite pseudocode duplicate self; nonzero BYTE6F2598 then sets6F2668 focus. Always457600 layout/draw and forwards EAX. No selected/count/NULL guard, object/count snapshot
// across virtual calls, or local interaction/ready test.
int __cdecl rf_frontend_b_frame_dispatch_and_draw(char a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( !a1 )
  {
    rf_ui_poll_and_dispatch_event((int (__cdecl *)(int))rf_save_list_b_handle_input_event);
    rf_save_list_b_update_pointer();
  }
  for ( i = 0; i < rf_receiver_get_first_dword(byte_6F28EC); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
  }
  rf_ui_button_clear_focus(&dword_6F2668);
  if ( !a1 )
  {
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, dword_6F23D4);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
    if ( unk_6F2598 )
      rf_ui_button_set_focus(&dword_6F2668);
  }
  return rf_save_list_b_animate_and_draw();
}

