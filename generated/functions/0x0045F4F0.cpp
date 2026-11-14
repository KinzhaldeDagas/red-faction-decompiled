// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F4F0 rf_multiplayer_rules_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Cdecl(x,y),stored int type preserved;return meaningful only as delegate/AL residue. FIRST invoke vtable+8 update withECXthis on EVERY focus-list6F4358 control,then
// enabled-button hit test with backing pointer/count. Hit+left press:changed focus store6F3AF0/sound42;nonnull hit DWORD32 callback receives ORIGINAL TWO(x,y) args,then
// sound43;call467310 even callbackNULL. Native45F5E0 ADD ESP4 cleans x only and45F5E3 FLD1/FSTP overwrites still-stacked y as gain1.0 for sound;decompiler's one-arg callback is
// wrong. Hit without press:read relative deltas;anyXY movement and changed hit ->focus store/sound42. No held-button drag callback path or edit-latch suppression here. No hit ->no
// focus change. Finally467350 ALnonzero ->focused vtable+4/ECXthis with NO extra stack args. No own controlNULL/focus-index bounds or state9 recheck beyond hit-test delegation;update
// ordering differs from setup pointer45D7D0 (which updates after handling). No rule apply/registry/network call.
char __cdecl rf_multiplayer_rules_update_pointer(int physical_x, int physical_y)
{
  _DWORD *v2; // eax
  char *v3; // eax
  int v4; // eax
  char result; // al
  _DWORD *v6; // eax
  int first_dword; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-10h] BYREF
  int v9; // [esp+14h] [ebp-Ch] BYREF
  int i; // [esp+18h] [ebp-8h]
  int v11; // [esp+1Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F4358); ++i )
  {
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F4358, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v2 + 8))(*v2);
  }
  first_dword = rf_receiver_get_first_dword(unk_6F4358);
  v3 = rf_receiver_plus4_address_458010((char *)unk_6F4358);
  v11 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v3, first_dword);
  if ( v11 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F3AF0 != v11 )
      {
        dword_6F3AF0 = v11;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F4358, v11) + 32) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(unk_6F4358, v11);
        (*(void (__cdecl **)(int))(*(_DWORD *)v4 + 32))(physical_x);
        rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      rf_host_menu_pane_input_enable();
    }
    else
    {
      rf_mouse_get_relative_deltas(&v9, &v8, &unk_193A03C);
      if ( (v9 || v8) && dword_6F3AF0 != v11 )
      {
        dword_6F3AF0 = v11;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  result = rf_host_menu_pane_input_byte_get();
  if ( result )
  {
    v6 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F4358, dword_6F3AF0);
    return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v6 + 4))(*v6, *v6);
  }
  return result;
}

