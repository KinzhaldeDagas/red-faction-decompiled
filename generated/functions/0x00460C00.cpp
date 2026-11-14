// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460C00 rf_multiplayer_profile_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(x,y). Hit-test focus-list6F5028. Hit+left press:changed focus/sound42;nonnull press callback32 receives TWO(x,y),then sound43;native460CAC ADD ESP4
// cleansx and nextFLD1 reusesy as gain1.0. Regardless callbackNULL,enable profile input460540. Hit/no press:only relativeXY movement AND editLatch6F4AD5==0 admit held-left drag
// callback36(x,y) and changed-focus/sound42. No hit+press clears edit latch. After handling,update EVERY focus control vtable+8/ECXthis/no stack args,then UNCONDITIONALLY invoke
// focused vtable+4/ECXthis/no stack args (no467350 gate). No own bounds/null/current-pane/runtime gate or edited-name commit. Return virtual delegate residue.
int __cdecl rf_multiplayer_profile_update_pointer(int physical_x, int physical_y)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  int first_dword; // [esp+4h] [ebp-1Ch]
  int i; // [esp+10h] [ebp-10h]
  int v10; // [esp+14h] [ebp-Ch] BYREF
  int v11; // [esp+18h] [ebp-8h] BYREF
  int v12; // [esp+1Ch] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(dword_6F5028);
  v2 = rf_receiver_plus4_address_458010((char *)dword_6F5028);
  v12 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v2, first_dword);
  if ( v12 < 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
      unk_6F4AD5 = 0;
  }
  else if ( rf_mouse_button_has_press_count(0) )
  {
    if ( unk_6F4A50 != v12 )
    {
      unk_6F4A50 = v12;
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F5028, v12) + 32) )
    {
      v3 = rf_inline_dword_array4_element_address_unchecked(dword_6F5028, v12);
      (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 32))(physical_x);
      rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
    rf_multiplayer_profile_input_enable();
  }
  else
  {
    rf_mouse_get_relative_deltas(&v11, &v10, &unk_193A03C);
    if ( (v11 || v10) && !unk_6F4AD5 )
    {
      if ( rf_mouse_get_button_held_byte(0)
        && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F5028, v12) + 36) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(dword_6F5028, v12);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(physical_x, physical_y);
      }
      if ( unk_6F4A50 != v12 )
      {
        unk_6F4A50 = v12;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F5028); ++i )
  {
    v5 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F5028, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v5 + 8))(*v5);
  }
  v6 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F5028, unk_6F4A50);
  return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v6 + 4))(*v6, *v6);
}

