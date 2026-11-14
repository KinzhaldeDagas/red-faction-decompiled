// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454ED0 rf_save_list_a_handle_input_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw signed eventDWORD; EAX is path-dependent residue, not a returned object pointer or status. Event1 calls454880 pop adapter with two ignored-1 slots,
// no own sound. Event28 unchecked-fetches control6F22FC[selected6F1F88], tests callbackDWORD+32; nonnull callback is RE-FETCHED then invoked with TWO cdecl slots(-1,-1), not one
// argument. Caller ADD4 and reuse of remaining slot for sound43 proves actual stack balance; null callback has no activation sound. Event4111 decrements control index with32-bit
// wrap; negative result becomes LIVE controlCount-1, so count0 gives-1. Event15 increments index and signed>=LIVE count becomes0. Both request sound42, no enabled skipping or
// count-empty guard. Event200 acts ONLY if BYTE6F2364 nonzero: decrement selected row6F1FA0, negative wrapped result clamp0,455160 ensure-visible, sound46. Event208 under same gate
// increments row; if signed>=LIVE recordCount6F21AC, rereads count and stores maxSigned(0,count-1), then455160 and sound47. Empty array may leave selected0 but no record dereference
// in this branch. Every other event scans i0..<LIVE controlCount, compares objectDWORD+28, FIRST match stores control selection, invokes nonnull+32 callback(-1,-1) and sound43, then
// stops even null callback. No control enabled-byte, selected bounds/NULL, caller interaction/readiness guard, or snapshot across callback/getters.
int __cdecl rf_save_list_a_handle_input_event(int event)
{
  int result; // eax
  int v2; // eax
  int first_dword; // eax
  int v4; // eax
  int i; // [esp+Ch] [ebp-4h]

  result = event;
  if ( event <= 200 )
  {
    if ( event == 200 )
    {
      if ( unk_6F2364 )
      {
        if ( --dword_6F1FA0 < 0 )
          dword_6F1FA0 = 0;
        rf_save_list_a_ensure_selected_row_visible();
        return rf_gamesound_play_event(46, 0, 0.0, 1.0);
      }
      return result;
    }
    if ( event == 1 )
    {
      rf_frontend_panel_pop_adapter_454880();
      return result;
    }
    if ( event != 15 )
    {
      if ( event == 28 )
      {
        result = rf_inline_dword_array4_element_address_unchecked(&unk_6F22FC, dword_6F1F88);
        if ( *(_DWORD *)(*(_DWORD *)result + 32) )
        {
          v2 = rf_inline_dword_array4_element_address_unchecked(&unk_6F22FC, dword_6F1F88);
          (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(-1);
          return rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        return result;
      }
      goto LABEL_30;
    }
    ++dword_6F1F88;
    if ( dword_6F1F88 >= rf_receiver_get_first_dword(&unk_6F22FC) )
      dword_6F1F88 = 0;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
  if ( event == 208 )
  {
    if ( unk_6F2364 )
    {
      ++dword_6F1FA0;
      if ( dword_6F1FA0 >= rf_receiver_get_first_dword(dword_6F21AC) )
      {
        first_dword = rf_receiver_get_first_dword(dword_6F21AC);
        dword_6F1FA0 = rf_int_max(0, first_dword - 1);
      }
      rf_save_list_a_ensure_selected_row_visible();
      return rf_gamesound_play_event(47, 0, 0.0, 1.0);
    }
    return result;
  }
  if ( event == 4111 )
  {
    if ( --dword_6F1F88 < 0 )
      dword_6F1F88 = rf_receiver_get_first_dword(&unk_6F22FC) - 1;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
LABEL_30:
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(&unk_6F22FC);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F22FC, i) + 28) == event )
    {
      dword_6F1F88 = i;
      result = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked(&unk_6F22FC, i);
      if ( *(_DWORD *)(result + 32) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(&unk_6F22FC, i);
        (*(void (__cdecl **)(int))(*(_DWORD *)v4 + 32))(-1);
        return rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      return result;
    }
  }
  return result;
}

