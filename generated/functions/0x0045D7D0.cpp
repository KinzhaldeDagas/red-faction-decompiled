// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D7D0 rf_multiplayer_setup_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Hit-test focus-array6F2EBC backing pointer/count. Hit+left-press:if changed focus store index and
// sound42;nonnull press callbackDWORD32 clears editLatch then invokes ORIGINAL TWO args(x,y),sound43;call467310 even when callbackNULL. Native callback call45D881 leaves y stack slot
// for subsequent sound gain1.0:ADD ESP4 cleans x and FLD1/FSTP overwrites y;decompiler's ONE-arg rendering is wrong. Hit without press:read relative deltas;only anyXY motion and
// editLatch==0 admit held-left drag callbackDWORD36(x,y),then changed-focus store/sound42. No hit+leftpress clears editLatch. After all branches,invoke vtable+8 update on EVERY focus
// control,then if467350 ALnonzero invoke focused control vtable+4/ECXthis (no stack arg). No focus-index bounds/controlNULL/empty-array guards in these loops. Own
// runtime/authority/screen scaling absent;hit-test delegate owns admission. Return incidental AL/vcall EAX.
int __cdecl rf_multiplayer_setup_update_pointer(int physical_x, int physical_y)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  _DWORD *v5; // eax
  int result; // eax
  _DWORD *v7; // eax
  int first_dword; // [esp+4h] [ebp-1Ch]
  int i; // [esp+10h] [ebp-10h]
  int v10; // [esp+14h] [ebp-Ch] BYREF
  int v11; // [esp+18h] [ebp-8h] BYREF
  int v12; // [esp+1Ch] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(dword_6F2EBC);
  v2 = rf_receiver_plus4_address_458010((char *)dword_6F2EBC);
  v12 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v2, first_dword);
  if ( v12 < 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
      unk_6F2D01 = 0;
  }
  else if ( rf_mouse_button_has_press_count(0) )
  {
    if ( dword_6F2CF4[0] != v12 )
    {
      dword_6F2CF4[0] = v12;
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, v12) + 32) )
    {
      unk_6F2D01 = 0;
      v3 = rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, v12);
      (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 32))(physical_x);
      rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
    rf_host_menu_pane_input_enable();
  }
  else
  {
    rf_mouse_get_relative_deltas(&v11, &v10, &unk_193A03C);
    if ( (v11 || v10) && !unk_6F2D01 )
    {
      if ( rf_mouse_get_button_held_byte(0)
        && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, v12) + 36) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, v12);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(physical_x, physical_y);
      }
      if ( dword_6F2CF4[0] != v12 )
      {
        dword_6F2CF4[0] = v12;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F2EBC); ++i )
  {
    v5 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v5 + 8))(*v5);
  }
  result = (unsigned __int8)rf_host_menu_pane_input_byte_get();
  if ( (_BYTE)result )
  {
    v7 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F2EBC, dword_6F2CF4[0]);
    return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v7 + 4))(*v7, *v7);
  }
  return result;
}

