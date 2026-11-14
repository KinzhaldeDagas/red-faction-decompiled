// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004542B0 rf_extras_menu_handle_input_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one raw eventDWORD. Events200/4111 call453CA0 previous;15/208 call453C50 next. Event1 passes two stack DWORDs-1,-1 to453DB0 (callee may ignore extra
// slots), reuses one outgoing slot for following sound41(0,float0,float1). Event28 unchecked-indexes inline array6F1F24 with selected6F1DAC, dereferences button, reads callback
// DWORD+32; if nonnull re-fetches selected element and invokes callback(-1,-1) with caller cleanup8. Always sound41 on Enter, including null callback. Other events loop signed
// i0..<LIVE raw DWORD0 getter486DE0(6F1F24), fetching each button pointer from416F70 and comparing DWORD+28 to event. First match stores selection, invokes current nonnull
// callback+32 with(-1,-1), then sound41 and stops. No enabled-byte check, object-null guard, count snapshot, or selected bounds validation; callback can mutate shared
// arrays/selection. Unmatched return is final getter EAX; action/navigation returns delegated residue, not Boolean.
int __cdecl rf_extras_menu_handle_input_event(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int i; // [esp+Ch] [ebp-4h]

  if ( a1 > 200 )
  {
    if ( a1 == 208 )
      return rf_extras_menu_select_next();
    if ( a1 != 4111 )
      goto LABEL_15;
    return rf_extras_menu_select_previous();
  }
  switch ( a1 )
  {
    case 200:
      return rf_extras_menu_select_previous();
    case 1:
      rf_extras_menu_request_stack_pop();
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
    case 15:
      return rf_extras_menu_select_next();
    case 28:
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, dword_6F1DAC) + 32) )
      {
        v2 = rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, dword_6F1DAC);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v2 + 32))(-1, -1);
      }
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
  }
LABEL_15:
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F1F24);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, i) + 28) == a1 )
    {
      dword_6F1DAC = i;
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, i) + 32) )
      {
        v3 = rf_inline_dword_array4_element_address_unchecked(dword_6F1F24, i);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v3 + 32))(-1, -1);
      }
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
    }
  }
  return result;
}

