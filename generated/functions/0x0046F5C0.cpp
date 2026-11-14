// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F5C0 rf_ui_modal_handle_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl raw FULL-DWORD key, no modifier masking. Keys15/208 DECREMENT focus with negative wrap to count-1; keys200/0x100F INCREMENT with wrap0; each scans at most focusCount
// skipping BYTE9==0, plays sound42, then FALLS THROUGH common dispatch with original key. Escape1 clears active only when edit CONTROL BYTE6F8DC9 is nonzero, regardless current
// focus; noneditable Escape does not close. Enter28 invokes nonnull focused+32 callback with TWO(-1,-1), sound43, without own BYTE9 guard, then falls through. Common phase: if
// key!=0, focus==EXACT4 and edit BYTE9!=0, forwards key to470A40(edit6F8DC0); Enter then UNCONDITIONALLY invokes action0 callback+32 with TWO(-1,-1) and sound43, no null/state guard.
// Else scans entire focus list: full hotkeyDWORD+28==key AND BYTE9!=0 sets focus and invokes nonnull callback+32 TWO(-1,-1), sound43. NO break: duplicate hotkeys can invoke multiple
// callbacks. State after earlier callbacks controls later tests; no active check or key consumption. ADD ESP,4/reused gain slot proves two callback arguments, not three.
char __cdecl rf_ui_modal_handle_input(int a1)
{
  int v1; // eax
  int first_dword; // eax
  int v3; // eax
  int v4; // eax
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]
  int k; // [esp+10h] [ebp-4h]

  if ( a1 > 200 )
  {
    if ( a1 == 208 )
    {
LABEL_10:
      for ( i = 0; i < rf_receiver_get_first_dword(unk_6F8F84); ++i )
      {
        if ( --dword_6F8C80 < 0 )
          dword_6F8C80 = rf_receiver_get_first_dword(unk_6F8F84) - 1;
        if ( *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, dword_6F8C80) + 9) )
          break;
      }
LABEL_16:
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
      goto LABEL_29;
    }
    if ( a1 != 4111 )
      goto LABEL_29;
LABEL_17:
    for ( j = 0; j < rf_receiver_get_first_dword(unk_6F8F84); ++j )
    {
      ++dword_6F8C80;
      if ( dword_6F8C80 >= rf_receiver_get_first_dword(unk_6F8F84) )
        dword_6F8C80 = 0;
      if ( *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, dword_6F8C80) + 9) )
        break;
    }
    goto LABEL_16;
  }
  if ( a1 == 200 )
    goto LABEL_17;
  if ( a1 != 1 )
  {
    if ( a1 != 15 )
    {
      if ( a1 == 28
        && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, dword_6F8C80) + 32) )
      {
        v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, dword_6F8C80);
        (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(-1);
        rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      goto LABEL_29;
    }
    goto LABEL_10;
  }
  if ( unk_6F8DC9 )
    rf_ui_modal_cancel();
LABEL_29:
  if ( a1 && dword_6F8C80 == 4 && unk_6F8DC9 )
  {
    LOBYTE(first_dword) = rf_ui_edit_handle_key(byte_6F8DC0, a1);
    if ( a1 == 28 )
    {
      v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, 0);
      (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 32))(-1);
      LOBYTE(first_dword) = rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
  }
  else
  {
    for ( k = 0; ; ++k )
    {
      first_dword = rf_receiver_get_first_dword(unk_6F8F84);
      if ( k >= first_dword )
        break;
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, k) + 28) == a1 )
      {
        if ( *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, k) + 9) )
        {
          dword_6F8C80 = k;
          if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, k) + 32) )
          {
            v4 = rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, dword_6F8C80);
            (*(void (__cdecl **)(int))(*(_DWORD *)v4 + 32))(-1);
            rf_gamesound_play_event(43, 0, 0.0, 1.0);
          }
        }
      }
    }
  }
  return first_dword;
}

