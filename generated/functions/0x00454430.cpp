// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454430 rf_extras_menu_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Reads absolute x/y via58AB60 and shared193A03C, gets LIVE count from DWORD0 getter486DE0(6F1F0C), and pointer-array base receiver+4
// through458010;458BE0(x,y,base,count) supplies hit. Negative hit exits. Nonzero58ACF0(button0) AL: changed hit stores selected6F1DAC BEFORE sound40. Reads callback+32 from
// corresponding6F1F24 button; null means no activation sound. Nonnull: pushes actual Y then X, re-fetches button and invokes cdecl callback(X,Y), not the decompiler one-argument
// call. ADD ESP4 after callback leaves one outgoing slot, immediately reused for float1 of sound41; total native stack balance preserves both callback argument slots. Nonclick reads
// relative deltas; any nonzero delta or ordered-nonzero/unorderedNaN FLOAT6F1DB4 versus DOUBLE0 allows hover change, which stores selection before sound40 only when hit differs. No
// own enabled/count-agreement guard between separate arrays, upper-hit check or interaction gate.
void rf_extras_menu_update_pointer()
{
  char *v0; // eax
  int v1; // eax
  int v2; // [esp+0h] [ebp-1Ch]
  int first_dword; // [esp+4h] [ebp-18h]
  int v4; // [esp+8h] [ebp-14h] BYREF
  int v5; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  first_dword = rf_receiver_get_first_dword(dword_6F1F0C);
  v0 = rf_receiver_plus4_address_458010((char *)dword_6F1F0C);
  v8 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, first_dword);
  if ( v8 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F1DAC != v8 )
      {
        dword_6F1DAC = v8;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, v8) + 32) )
      {
        v2 = physical_x;
        v1 = rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, v8);
        (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(v2);
        rf_gamesound_play_event(41, 0, 0.0, 1.0);
      }
    }
    else
    {
      rf_mouse_get_relative_deltas(&v5, &v4, &unk_193A03C);
      if ( (v5 || v4 || unk_6F1DB4 != 0.0) && dword_6F1DAC != v8 )
      {
        dword_6F1DAC = v8;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
    }
  }
}

