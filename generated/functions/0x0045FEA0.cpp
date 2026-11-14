// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FEA0 rf_multiplayer_menu_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl FULL keyDWORD,previous untyped definition preserved;EAX incidental. If profileInput6F4850 nonzero,only current pane661F8C EXACT0 forwards key to
// profile460AA0;all other current values ignore key. Otherwise:EXACT1 set main focus3,invoke Back noarg with two ignored extra(-1,-1) words,sound41;EXACT28 nonNULL focused DWORD32
// callback(-1,-1),then sound41 even callbackNULL (no own BYTE9 check). EXACT200/100F previous enabled main item,EXACT208/15 next,always sound40. Other keys scan exactly4
// contiguous68-byte button records:DWORD28 equals raw key;first match stops even if BYTE9 zero. Enabled match sets focus,calls nonNULL callback32(-1,-1),sound41. No key
// normalization,profile transition readiness beyond current==0,focus-index bounds or runtime/session gate. Main input flag checked by driver,not this body.
int __cdecl rf_multiplayer_menu_handle_key(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int i; // [esp+10h] [ebp-4h]

  result = byte_6F4850[0];
  if ( byte_6F4850[0] )
  {
    if ( !dword_661F8C )
      return rf_multiplayer_profile_handle_key(a1);
    return result;
  }
  result = a1;
  if ( a1 > 200 )
  {
    if ( a1 == 208 )
    {
LABEL_19:
      rf_multiplayer_menu_focus_next_enabled();
      return rf_gamesound_play_event(40, 0, 0.0, 1.0);
    }
    if ( a1 != 4111 )
      goto LABEL_20;
LABEL_18:
    rf_multiplayer_menu_focus_previous_enabled();
    return rf_gamesound_play_event(40, 0, 0.0, 1.0);
  }
  switch ( a1 )
  {
    case 200:
      goto LABEL_18;
    case 1:
      dword_6F484C = 3;
      rf_multiplayer_menu_request_back();
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
    case 15:
      goto LABEL_19;
    case 28:
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, dword_6F484C) + 32) )
      {
        v2 = rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, dword_6F484C);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v2 + 32))(-1, -1);
      }
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
  }
LABEL_20:
  for ( i = 0; i < 4; ++i )
  {
    if ( unk_6F48B4[17 * i] == a1 )
    {
      result = 68 * i;
      if ( unk_6F48A1[68 * i] )
      {
        dword_6F484C = i;
        if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, i) + 32) )
        {
          v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F49FC, dword_6F484C);
          (*(void (__cdecl **)(int, int))(*(_DWORD *)v3 + 32))(-1, -1);
        }
        return rf_gamesound_play_event(41, 0, 0.0, 1.0);
      }
      return result;
    }
    result = i + 1;
  }
  return result;
}

