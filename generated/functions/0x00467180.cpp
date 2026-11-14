// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467180 rf_host_menu_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Read absoluteXY;hit-test backing/count of draw-list6F5E80 (callbacks resolved from parallel focus-list6F5E94). Hit+left press:changed focus
// store/sound40;nonnull callbackDWORD32 gets TWO original(x,y),then sound41. Native46723D ADD ESP4 cleansx only;remainingy reused for sound gain1.0,explaining wrong one-arg
// decompiler output. Hit/no press:only paneInput0;any relativeXY OR buttonXspeed6F5E40 nonzero/UNORDERED NaN permits hover focus/sound40. No hit leaves main focus alone. Finally
// re-read paneInput after callback;nonzero/currentPane0 ->setup pointer(x,y),1 ->rules pointer(x,y),others none,even when main hit absent. No own mainInput/bounds check beyond
// delegated hit-test.
void rf_host_menu_update_pointer()
{
  char *v0; // eax
  int v1; // eax
  int v2; // [esp+0h] [ebp-20h]
  int first_dword; // [esp+4h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+10h] [ebp-10h] BYREF
  int physical_x; // [esp+14h] [ebp-Ch] BYREF
  int physical_y; // [esp+18h] [ebp-8h] BYREF
  int v8; // [esp+1Ch] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  first_dword = rf_receiver_get_first_dword(unk_6F5E80);
  v0 = rf_receiver_plus4_address_458010((char *)unk_6F5E80);
  v8 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, first_dword);
  if ( v8 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F5E34 != v8 )
      {
        dword_6F5E34 = v8;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, v8) + 32) )
      {
        v2 = physical_x;
        v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, v8);
        (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(v2);
        rf_gamesound_play_event(41, 0, 0.0, 1.0);
      }
    }
    else if ( !unk_6F5E29 )
    {
      rf_mouse_get_relative_deltas(&v5, &v4, &unk_193A03C);
      if ( (v5 || v4 || unk_6F5E40 != 0.0) && dword_6F5E34 != v8 )
      {
        dword_6F5E34 = v8;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
    }
  }
  if ( unk_6F5E29 )
  {
    if ( unk_6F5E30 )
    {
      if ( unk_6F5E30 == 1 )
        rf_multiplayer_rules_update_pointer(physical_x, physical_y);
    }
    else
    {
      rf_multiplayer_setup_update_pointer(physical_x, physical_y);
    }
  }
}

