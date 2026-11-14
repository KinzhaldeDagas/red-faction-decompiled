// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004697A0 rf_controls_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl original absolute(x,y). Hit-test focus-list6F6940. Hit+left press:changed focus6F62B0/sound42;nonnull callback32 gets TWO(x,y),then sound43;ADD ESP4 reuses
// remaining y as gain1.0. ALWAYS enable OPTIONS pane input467F90 after a hit press,even callbackNULL. Hit/no press:only nonzero relativeXY admits held-left nonnull drag36(x,y) and
// changed hoverfocus/sound42;no velocity hover admission here. NO HIT:if captureDWORD==1 and left press,end capture. Then re-read capture==1:if button1/2 press or any wheel
// delta,poll binding4683C0(-1);left-button binding handled by list-press path,not this fallback. ALWAYS afterward update every focus control virtual+8 ECX/noargs;only
// options_pane_input_getALnonzero invokes focused virtual+4 ECX/noargs. No own currentpane/mainInput/player/bounds guard. Capture may change during callbacks;checks use updated
// state. Stored int return actual AL/delegate residue.
unsigned __int8 __cdecl rf_controls_update_pointer(int physical_x, int physical_y)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  _DWORD *v5; // eax
  unsigned __int8 result; // al
  _DWORD *v7; // eax
  int first_dword; // [esp+4h] [ebp-28h]
  int i; // [esp+10h] [ebp-1Ch]
  int v10; // [esp+14h] [ebp-18h] BYREF
  int v11; // [esp+18h] [ebp-14h] BYREF
  int v12; // [esp+1Ch] [ebp-10h] BYREF
  int v13; // [esp+20h] [ebp-Ch] BYREF
  int v14; // [esp+24h] [ebp-8h] BYREF
  int v15; // [esp+28h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(unk_6F6940);
  v2 = rf_receiver_plus4_address_458010((char *)unk_6F6940);
  v15 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v2, first_dword);
  if ( v15 < 0 )
  {
    if ( unk_6F62B4 == 1 && rf_mouse_button_has_press_count(0) )
      rf_controls_binding_capture_end();
  }
  else if ( rf_mouse_button_has_press_count(0) )
  {
    if ( dword_6F62B0 != v15 )
    {
      dword_6F62B0 = v15;
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, v15) + 32) )
    {
      v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F6940, v15);
      (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 32))(physical_x);
      rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
    rf_options_menu_pane_input_enable();
  }
  else
  {
    rf_mouse_get_relative_deltas(&v14, &v13, &unk_193A03C);
    if ( v14 || v13 )
    {
      if ( rf_mouse_get_button_held_byte(0)
        && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, v15) + 36) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(unk_6F6940, v15);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(physical_x, physical_y);
      }
      if ( dword_6F62B0 != v15 )
      {
        dword_6F62B0 = v15;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  if ( unk_6F62B4 == 1 )
  {
    rf_mouse_get_relative_deltas(&v10, &v12, &v11);
    if ( rf_mouse_button_has_press_count(1) || rf_mouse_button_has_press_count(2) || v11 )
      rf_controls_accept_binding_input(-1);
  }
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F6940); ++i )
  {
    v5 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v5 + 8))(*v5);
  }
  result = rf_options_menu_pane_input_byte_get();
  if ( result )
  {
    v7 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, dword_6F62B0);
    return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v7 + 4))(*v7, *v7);
  }
  return result;
}

