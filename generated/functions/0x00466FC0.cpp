// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466FC0 rf_host_menu_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Cdecl FULL keyDWORD,initially untyped ABI retained. PaneInput6F5E29 nonzero:currentPane0 forwards raw key to setup,1 to rules,all other current values
// ignore;no main key handling. PaneInput0:200/100F ->focus previous466630;208/15 ->next4665E0.1 ->Back noarg with TWO ignored(-1,-1),then sound41.28 ->nonnull focused callbackDWORD32
// gets TWO(-1,-1),then sound41 EVEN callbackNULL;no BYTE9 guard. Other keys scan actual focus-list count;FIRST hotkeyDWORD28 match sets focus,calls nonnull
// callback(-1,-1),sound41,then returns even when callbackNULL. No disabled-state admission,key normalization,focus bounds or own mainInput check;driver owns gate. Native Escape
// reuses leftover sentinel slot as sound gain (ADD ESP4);callback paths clean8.
void __cdecl rf_host_menu_handle_key(int a1)
{
  int v1; // eax
  int v2; // eax
  int i; // [esp+10h] [ebp-4h]

  if ( unk_6F5E29 )
  {
    if ( unk_6F5E30 )
    {
      if ( unk_6F5E30 == 1 )
        rf_multiplayer_rules_handle_key(a1);
    }
    else
    {
      rf_multiplayer_setup_handle_key(a1);
    }
    return;
  }
  if ( a1 > 200 )
  {
    if ( a1 == 208 )
      goto LABEL_11;
    if ( a1 != 4111 )
      goto LABEL_16;
LABEL_10:
    rf_host_menu_focus_previous();
    return;
  }
  switch ( a1 )
  {
    case 200:
      goto LABEL_10;
    case 1:
      rf_host_menu_request_back();
      rf_gamesound_play_event(41, 0, 0.0, 1.0);
      return;
    case 15:
LABEL_11:
      rf_host_menu_focus_next();
      return;
    case 28:
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, dword_6F5E34) + 32) )
      {
        v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, dword_6F5E34);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v1 + 32))(-1, -1);
      }
LABEL_15:
      rf_gamesound_play_event(41, 0, 0.0, 1.0);
      return;
  }
LABEL_16:
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F5E94); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, i) + 28) == a1 )
    {
      dword_6F5E34 = i;
      if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, i) + 32) )
      {
        v2 = rf_inline_dword_array4_element_address_unchecked(unk_6F5E94, i);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v2 + 32))(-1, -1);
      }
      goto LABEL_15;
    }
  }
}

