// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457010 rf_save_list_b_handle_input_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw eventDWORD. Event1 calls4564B0 pop adapter with ignored(-1,-1), no own sound. Event28: nonzero edit focusBYTE6F2750 directly calls456720
// with(-1,-1), no wrapper activation sound; otherwise unchecked control6F28EC[selected6F23D4] callback+32, re-fetch and call with TWO cdecl(-1,-1) slots, then sound43 only if
// callback nonnull. Event4111 decrements control, negative wrapped result stores LIVE controlCount-1;15 increments and signed>=LIVE count resets0. Both clear BYTE6F23D0 BEFORE
// sound42; no empty-count or enabled skipping. Event200 with BYTE6F2598 nonzero decrements row6F23EC and clamps negative wrapped result0; then UNCHECKED record filename at
// array6F26AC[row] is copied to edit6F2748 by4706C0 with font6F29AC,4573E0 ensure-visible, sound46. Event208 under same gate increments row, signed>=LIVE record count stores REREAD
// count-1 WITHOUT max0: empty count gives-1, and unchecked filename/edit call STILL follows, then ensure-visible and sound47. Other events: nonzero edit focus bypasses control-ID
// lookup and scans C string AT6F2788 to obtain signed32 length. ONLY length<35 admits further edit handling, so length>=35 suppresses all fallback edit keys (including deletion), not
// only insertion. Reject43,53,4105 and table-decoded4135,4136,4139,4147,4148,4149. Event57 forwards to470A40 only length>0; all other fallback codes forward unchanged. Standard
// event1/15/28/200/208/4111 cases run before this length gate. With edit focus0 scan LIVE controls for first matchingDWORD+28, store selected, invoke nonnull+32 callback(-1,-1) and
// sound43, stop. No enabled/index/count/NULL validation, bounded strlen, uniform result, or global snapshot across delegates.
void __cdecl rf_save_list_b_handle_input_event(int a1)
{
  int v1; // eax
  char *v2; // eax
  char *v3; // eax
  int v4; // kr00_4
  int v5; // eax
  int v6; // [esp+4h] [ebp-24h]
  int v7; // [esp+4h] [ebp-24h]
  int i; // [esp+20h] [ebp-8h]

  if ( a1 <= 200 )
  {
    if ( a1 == 200 )
    {
      if ( unk_6F2598 )
      {
        if ( --dword_6F23EC < 0 )
          dword_6F23EC = 0;
        v6 = unk_6F29AC;
        v2 = (char *)rf_record272_array_element_address_unchecked(dword_6F26AC, dword_6F23EC);
        rf_ui_edit_set_text_bounded(byte_6F2748, v2, v6);
        rf_save_list_b_ensure_selected_row_visible();
        rf_gamesound_play_event(46, 0, 0.0, 1.0);
      }
      return;
    }
    if ( a1 == 1 )
    {
      rf_frontend_panel_pop_adapter_4564b0();
      return;
    }
    if ( a1 != 15 )
    {
      if ( a1 == 28 )
      {
        if ( unk_6F2750 )
        {
          rf_save_list_b_request_save();
        }
        else if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F28EC, dword_6F23D4) + 32) )
        {
          v1 = rf_inline_dword_array4_element_address_unchecked(&unk_6F28EC, dword_6F23D4);
          (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(-1);
          rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        return;
      }
      goto LABEL_32;
    }
    ++dword_6F23D4;
    if ( dword_6F23D4 >= rf_receiver_get_first_dword(&unk_6F28EC) )
      dword_6F23D4 = 0;
LABEL_18:
    byte_6F23D0[0] = 0;
    rf_gamesound_play_event(42, 0, 0.0, 1.0);
    return;
  }
  if ( a1 == 208 )
  {
    if ( unk_6F2598 )
    {
      ++dword_6F23EC;
      if ( dword_6F23EC >= rf_receiver_get_first_dword(dword_6F26AC) )
        dword_6F23EC = rf_receiver_get_first_dword(dword_6F26AC) - 1;
      v7 = unk_6F29AC;
      v3 = (char *)rf_record272_array_element_address_unchecked(dword_6F26AC, dword_6F23EC);
      rf_ui_edit_set_text_bounded(byte_6F2748, v3, v7);
      rf_save_list_b_ensure_selected_row_visible();
      rf_gamesound_play_event(47, 0, 0.0, 1.0);
    }
    return;
  }
  if ( a1 == 4111 )
  {
    if ( --dword_6F23D4 < 0 )
      dword_6F23D4 = rf_receiver_get_first_dword(&unk_6F28EC) - 1;
    goto LABEL_18;
  }
LABEL_32:
  if ( unk_6F2750 )
  {
    v4 = strlen(unk_6F2788);
    if ( v4 < 35 )
    {
      if ( a1 > 4105 )
      {
        switch ( a1 )
        {
          case 4135:
          case 4136:
          case 4139:
          case 4147:
          case 4148:
          case 4149:
            return;
          default:
            goto LABEL_45;
        }
      }
      else if ( a1 != 4105 && a1 != 43 && a1 != 53 )
      {
        if ( a1 == 57 )
        {
          if ( v4 > 0 )
            rf_ui_edit_handle_key(byte_6F2748, a1);
        }
        else
        {
LABEL_45:
          rf_ui_edit_handle_key(byte_6F2748, a1);
        }
      }
    }
  }
  else
  {
    for ( i = 0; i < rf_receiver_get_first_dword(&unk_6F28EC); ++i )
    {
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F28EC, i) + 28) == a1 )
      {
        dword_6F23D4 = i;
        if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F28EC, i) + 32) )
        {
          v5 = rf_inline_dword_array4_element_address_unchecked(&unk_6F28EC, i);
          (*(void (__cdecl **)(int))(*(_DWORD *)v5 + 32))(-1);
          rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        return;
      }
    }
  }
}

