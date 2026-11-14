// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004632D0 rf_browser_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Read absolute mouseXY;FIRST invoke EVERY focus-list6F5C60 control virtual+8 with ECXthis and NO stack args. Hit-test backing/count. Hit+left press:if changed,store
// focus6F519C and sound42;nonnull callbackDWORD32 gets TWO original(x,y),cleanup8. No extra action sound after callback. Hit without press:only nonzero relativeXY enables hover;if
// left held and drag callbackDWORD36 nonnull,call(x,y),then changed focus/sound42. No hit leaves focus alone. No own active/input/focus bounds/controlNULL check;driver supplies input
// gate and focused virtual+4. Stored pointer return incidental.
char rf_browser_update_pointer()
{
  _DWORD *v0; // eax
  char *v1; // eax
  _DWORD *v2; // eax
  int v3; // eax
  int v4; // eax
  int v6; // [esp+0h] [ebp-24h]
  int v7; // [esp+0h] [ebp-24h]
  int first_dword; // [esp+4h] [ebp-20h]
  int v9; // [esp+4h] [ebp-20h]
  int v10; // [esp+4h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-18h] BYREF
  int v12; // [esp+10h] [ebp-14h] BYREF
  int i; // [esp+14h] [ebp-10h]
  int physical_x; // [esp+18h] [ebp-Ch] BYREF
  int physical_y; // [esp+1Ch] [ebp-8h] BYREF
  _DWORD *v16; // [esp+20h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F5C60); ++i )
  {
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, i);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v0 + 8))(*v0, *v0);
  }
  first_dword = rf_receiver_get_first_dword(unk_6F5C60);
  v1 = rf_receiver_plus4_address_458010((char *)unk_6F5C60);
  v2 = (_DWORD *)rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v1, first_dword);
  v16 = v2;
  if ( (int)v2 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( (_DWORD *)unk_6F519C != v16 )
      {
        unk_6F519C = v16;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
      v2 = *(_DWORD **)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, (int)v16);
      if ( v2[8] )
      {
        v9 = physical_y;
        v6 = physical_x;
        v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, (int)v16);
        LOBYTE(v2) = (unsigned __int8)(*(_DWORD *(__cdecl **)(int, int))(*(_DWORD *)v3 + 32))(v6, v9);
      }
    }
    else
    {
      LOBYTE(v2) = rf_mouse_get_relative_deltas(&v12, &v11, &unk_193A03C);
      if ( v12 || v11 )
      {
        LOBYTE(v2) = rf_mouse_get_button_held_byte(0);
        if ( (_BYTE)v2 )
        {
          v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, (int)v16);
          if ( *(_DWORD *)(*v2 + 36) )
          {
            v10 = physical_y;
            v7 = physical_x;
            v4 = rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, (int)v16);
            LOBYTE(v2) = (*(int (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(v7, v10);
          }
        }
        if ( (_DWORD *)unk_6F519C != v16 )
        {
          unk_6F519C = v16;
          LOBYTE(v2) = rf_gamesound_play_event(42, 0, 0.0, 1.0);
        }
      }
    }
  }
  return (char)v2;
}

