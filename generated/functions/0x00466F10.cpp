// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466F10 rf_host_menu_update_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Cdecl suppressInputLOWBYTE. Always update EVERY focus-list6F5E94 control virtual+8,ECXthis/NO stack args. Only suppress0 AND mainInput6F5E28
// nonzero:poll_dispatch(handler466FC0,0) TWO native args,main pointer467180;if paneInput6F5E29==0,focused main control virtual+4 ECX/no stack args. No own focus-index/controlNULL
// check or pane position-completion admission. Always animate/draw466960 even inactive/suppressed;EAX draw residue.
int __cdecl rf_host_menu_update_and_draw(char a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F5E94); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
  }
  if ( !a1 )
  {
    if ( unk_6F5E28 )
    {
      rf_ui_poll_and_dispatch_event(rf_host_menu_handle_key);
      rf_host_menu_update_pointer();
      if ( !unk_6F5E29 )
      {
        v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, dword_6F5E34);
        (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
      }
    }
  }
  return rf_host_menu_animate_and_draw();
}

