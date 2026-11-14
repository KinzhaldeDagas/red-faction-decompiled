// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004551F0 rf_save_list_a_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments.58AB60 supplies absoluteX/Y and shared193A03C; LIVE count486DE0(6F22FC) and receiver+4 base458010 feed458BE0 enabled hit test. Negative hit
// exits; no separate upper-index check. Nonzero58ACF0(button0) AL click: changed hit stores selected6F1F88 before sound42; nonnull callback+32 re-fetched and invoked with TWO
// cdecl(X,Y), not decompiler one-argument expression. ADD4 after call leaves one slot reused for float1 of sound43; null callback has no activation sound. Nonclick reads relative
// deltas58AD50; ONLY nonzero dx OR dy admits subsequent work (panel velocity/NaN is not tested here). If58AC50(button0) AL nonzero and current object+36 callback nonnull, re-fetch
// and call(X,Y) with ADD8. After drag callback, re-read selected; changed hit is stored then sound42. No action/hover update without movement, no own interaction gate, object/count
// snapshot or NULL validation. Return is hit/helper/pointer/callback/sound residue, not canonical Boolean.
int rf_save_list_a_update_pointer()
{
  char *v0; // eax
  int result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+0h] [ebp-1Ch]
  int first_dword; // [esp+4h] [ebp-18h]
  int v7; // [esp+4h] [ebp-18h]
  int v8; // [esp+8h] [ebp-14h] BYREF
  int v9; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v12; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  first_dword = rf_receiver_get_first_dword(byte_6F22FC);
  v0 = rf_receiver_plus4_address_458010(byte_6F22FC);
  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, first_dword);
  v12 = result;
  if ( result >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F1F88 != v12 )
      {
        dword_6F1F88 = v12;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
      result = rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, v12);
      if ( *(_DWORD *)(*(_DWORD *)result + 32) )
      {
        v4 = physical_x;
        v2 = rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, v12);
        (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(v4);
        return rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
    }
    else
    {
      result = rf_mouse_get_relative_deltas(&v9, &v8, &unk_193A03C);
      if ( v9 || v8 )
      {
        if ( rf_mouse_get_button_held_byte(0)
          && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, v12) + 36) )
        {
          v7 = physical_y;
          v5 = physical_x;
          v3 = rf_inline_dword_array4_element_address_unchecked(byte_6F22FC, v12);
          (*(void (__cdecl **)(int, int))(*(_DWORD *)v3 + 36))(v5, v7);
        }
        result = dword_6F1F88;
        if ( dword_6F1F88 != v12 )
        {
          dword_6F1F88 = v12;
          return rf_gamesound_play_event(42, 0, 0.0, 1.0);
        }
      }
    }
  }
  return result;
}

