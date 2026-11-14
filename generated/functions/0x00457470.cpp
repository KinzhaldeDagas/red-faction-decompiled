// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457470 rf_save_list_b_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Reads absolute pointer/shared193A03C, obtains LIVE count and receiver+4 of6F28EC, calls458BE0. Negative hit clears BYTE6F23D0=0 and exits.
// Nonzero button0 press-count AL: changed hit stores selected6F23D4 before sound42; nonnull re-fetched callback+32 receives TWO cdecl(X,Y), after which ADD4/stack-slot reuse forms
// sound43; no own mode-byte clear on click branch and no sound43 for null callback. Nonclick obtains dx,dy. Exact native admission is (dx!=0) OR ((dy!=0) AND (BYTE6F23D0==0));
// nonzero horizontal delta BYPASSES mode gate, not (dx OR dy) AND mode0. Without admitted motion no hover or drag calls. With motion, if button0 held AL nonzero and callbackDWORD+36
// nonnull, re-fetch and call(X,Y) with ADD8. Then re-read selected, if changed store hit BEFORE sound42. No velocity-based hover, selected/index/count/NULL guard, final mode reset on
// valid hit, callback snapshot or normalized return.
char rf_save_list_b_update_pointer()
{
  char *v0; // eax
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v5; // [esp+0h] [ebp-1Ch]
  int v6; // [esp+0h] [ebp-1Ch]
  int first_dword; // [esp+4h] [ebp-18h]
  int v8; // [esp+4h] [ebp-18h]
  int v9; // [esp+8h] [ebp-14h] BYREF
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v13; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  first_dword = rf_receiver_get_first_dword(byte_6F28EC);
  v0 = rf_receiver_plus4_address_458010(byte_6F28EC);
  v1 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, first_dword);
  v13 = v1;
  if ( v1 < 0 )
  {
    byte_6F23D0[0] = 0;
  }
  else if ( rf_mouse_button_has_press_count(0) )
  {
    if ( dword_6F23D4 != v13 )
    {
      dword_6F23D4 = v13;
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
    v1 = rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, v13);
    if ( *(_DWORD *)(*(_DWORD *)v1 + 32) )
    {
      v5 = physical_x;
      v2 = rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, v13);
      (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(v5);
      LOBYTE(v1) = rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
  }
  else
  {
    LOBYTE(v1) = rf_mouse_get_relative_deltas(&v10, &v9, &unk_193A03C);
    if ( v10 || v9 && !byte_6F23D0[0] )
    {
      LOBYTE(v1) = rf_mouse_get_button_held_byte(0);
      if ( (_BYTE)v1 )
      {
        v1 = rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, v13);
        if ( *(_DWORD *)(*(_DWORD *)v1 + 36) )
        {
          v8 = physical_y;
          v6 = physical_x;
          v3 = rf_inline_dword_array4_element_address_unchecked(byte_6F28EC, v13);
          LOBYTE(v1) = (*(int (__cdecl **)(int, int))(*(_DWORD *)v3 + 36))(v6, v8);
        }
      }
      if ( dword_6F23D4 != v13 )
      {
        dword_6F23D4 = v13;
        LOBYTE(v1) = rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  return v1;
}

