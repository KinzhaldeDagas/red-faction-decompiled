// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FDF0 rf_multiplayer_menu_update_and_draw
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl suppressInput lowBYTE. Always vtable+8 update EVERY focus-list6F49FC control viaECXthis/no stack args. Only suppressInputBYTE0 AND menuInput6F4868
// nonzero:poll_dispatch(handler45FEA0,0) (TWO native stack words),then main pointer460170;if profileInputBYTE6F4850==0,invoke focused main control vtable+4/ECXthis/no stack args. No
// focus bounds/null guard. Always call animation/draw4602E0 afterward,including suppressed input/inactive menu;motion/drawing continues. Does not gate on coordinate-completion
// queries. Stored int return draw residue.
int __cdecl rf_multiplayer_menu_update_and_draw(char a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F49FC); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
  }
  if ( !a1 )
  {
    if ( unk_6F4868 )
    {
      rf_ui_poll_and_dispatch_event(rf_multiplayer_menu_handle_key);
      rf_multiplayer_menu_update_pointer();
      if ( !unk_6F4850 )
      {
        v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, unk_6F484C);
        (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
      }
    }
  }
  return rf_multiplayer_menu_animate_and_draw();
}

