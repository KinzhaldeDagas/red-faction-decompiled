// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460170 rf_multiplayer_menu_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Read absolute mouseXY;hit-test EXACT4 pointers from hit-list6F49A8 backing (not its dynamic count). Hit+left press:changed focus store/sound40;nonNULL
// focus-list callbackDWORD32 receives TWO original mouse(x,y),then sound41. Native460224 ADD ESP4 cleans x only;FLD1/FSTP reuses y as sound gain1.0,explaining false one-arg
// decompiler call. Hit/no press:only profileInput==0 admits hover;if any relativeXY motion OR button horizontal speed nonzero/UNORDERED NaN,changed focus store/sound40. No hit has no
// main focus mutation. Finally profileInput nonzero AND currentPane EXACT0 ->profile pointer460C00(same absoluteXY),even after main click callback may change flag. No own
// menu-active/bounds/state9 recheck outside hit-test delegation.
void rf_multiplayer_menu_update_pointer()
{
  char *v0; // eax
  int v1; // eax
  int v2; // [esp+0h] [ebp-1Ch]
  int v3; // [esp+8h] [ebp-14h] BYREF
  int v4; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v7; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  v0 = rf_receiver_plus4_address_458010((char *)dword_6F49A8);
  v7 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, 4);
  if ( v7 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F484C != v7 )
      {
        dword_6F484C = v7;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, v7) + 32) )
      {
        v2 = physical_x;
        v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, v7);
        (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(v2);
        rf_gamesound_play_event(41, 0, 0.0, 1.0);
      }
    }
    else if ( !byte_6F4850[0] )
    {
      rf_mouse_get_relative_deltas(&v4, &v3, &unk_193A03C);
      if ( (v4 || v3 || unk_6F4858 != 0.0) && dword_6F484C != v7 )
      {
        dword_6F484C = v7;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
    }
  }
  if ( byte_6F4850[0] )
  {
    if ( !dword_661F8C )
      rf_multiplayer_profile_update_pointer(physical_x, physical_y);
  }
}

