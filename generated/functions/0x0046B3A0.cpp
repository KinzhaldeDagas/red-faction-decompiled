// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B3A0 rf_performance_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl original absolute(x,y). Hit-test focus-list6F7980 backing/count. Hit+left press:changed focus6F69D0/sound42;nonnull focused callback32 getsTWO
// original(x,y),cleanup8;NO extra action sound43. ALWAYS enable OPTIONS pane input467F90 after hit press,even callbackNULL. Hit/no press:only nonzero relativeXY admits held-left
// nonnull drag36(x,y),then changed hoverfocus/sound42. No velocity hover path/no-hit mutation. ALWAYS afterward virtual+8 every focus control,ECX/noargs;only
// options_pane_input_getALnonzero calls focused virtual+4 ECX/noargs. No own mainInput/currentpane/player/focus bounds check;parent can call while paneInput0 until transition changes
// current pane. Stored int return actual AL/delegate residue.
unsigned __int8 __cdecl rf_performance_update_pointer(int physical_x, int physical_y)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  _DWORD *v5; // eax
  unsigned __int8 result; // al
  _DWORD *v7; // eax
  int first_dword; // [esp+4h] [ebp-1Ch]
  int i; // [esp+10h] [ebp-10h]
  int v10; // [esp+14h] [ebp-Ch] BYREF
  int v11; // [esp+18h] [ebp-8h] BYREF
  int v12; // [esp+1Ch] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(dword_6F7980);
  v2 = rf_receiver_plus4_address_458010((char *)dword_6F7980);
  v12 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v2, first_dword);
  if ( v12 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F69D0 != v12 )
      {
        dword_6F69D0 = v12;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, dword_6F69D0) + 32) )
      {
        v3 = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, dword_6F69D0);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v3 + 32))(physical_x, physical_y);
      }
      rf_options_menu_pane_input_enable();
    }
    else
    {
      rf_mouse_get_relative_deltas(&v11, &v10, &unk_193A03C);
      if ( v11 || v10 )
      {
        if ( rf_mouse_get_button_held_byte(0)
          && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, v12) + 36) )
        {
          v4 = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, v12);
          (*(void (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(physical_x, physical_y);
        }
        if ( dword_6F69D0 != v12 )
        {
          dword_6F69D0 = v12;
          rf_gamesound_play_event(42, 0, 0.0, 1.0);
        }
      }
    }
  }
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F7980); ++i )
  {
    v5 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v5 + 8))(*v5);
  }
  result = rf_options_menu_pane_input_byte_get();
  if ( result )
  {
    v7 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, dword_6F69D0);
    return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v7 + 4))(*v7, *v7);
  }
  return result;
}

