// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046AE70 rf_performance_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl FULL keyDWORD.1 disable/hide OPTIONS pane/sound43.15 focus6F69D0++/wrap dynamic focus-list6F7980 count;100F decrement/negative
// wrapcount-1;always sound42,NO disabled skipping/empty-count guard.28 nonnull focused callback32 getsTWO(-1,-1),then sound43;NO BYTE9 check. Native cleanup4 reuses remaining
// sentinel as gain1.0.203/205:priority gamma controlBYTE8(6F6CA8) nonzero ->slider value minus/plus original double0.10000000149011612,roundfloat BEFORE clamped set,read back stored
// globalFLOAT gamma,truncate gamma*100.0 topercent,apply ramp,sound47/46 even at unchanged limit. Else first chooser with BYTE8 nonzero AND corresponding arrowcallback nonNULL
// wins,in order preset,texture,character,filter;callTWO(-1,-1),no parent group dispatch. Thus preset arrows apply immediately but texture/character/filter arrows ONLY cycle UI/sound
// via leaves,without player/renderer/Custom update until a later apply operation. Other keys scan focus-list;FIRST raw hotkeyDWORD28 match calls virtual+4 ECX/noargs,then nonnull
// callback32 getsTWO(0,0) (NOT sentinels),sound43;no BYTE9 guard,explicit focus-index write or subsequent match. No own mainInput/paneInput/player/focus bounds/key
// normalization/save;parent driver supplies admission. Existing int return incidental.
int __cdecl rf_performance_handle_key(int a1)
{
  int result; // eax
  int v2; // eax
  _DWORD *v3; // eax
  int v4; // eax
  float v5; // [esp+Ch] [ebp-10h]
  float v6; // [esp+10h] [ebp-Ch]
  int i; // [esp+18h] [ebp-4h]

  if ( a1 <= 203 )
  {
    if ( a1 == 203 )
    {
      if ( unk_6F6CA8 )
      {
        v5 = rf_ui_slider_value_get(flt_6F6CA0) - 0.1000000014901161;
        rf_ui_slider_set_value_clamped(flt_6F6CA0, v5);
        rf_graphics_gamma = rf_ui_slider_value_get(flt_6F6CA0);
        rf_graphics_gamma_percent = (int)(rf_graphics_gamma * 100.0);
        rf_graphics_gamma_set(rf_graphics_gamma);
        return rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
      else if ( unk_6F75A8 && unk_6F7328 )
      {
        return unk_6F7328(-1, -1);
      }
      else
      {
        result = byte_6F6CF0[0];
        if ( byte_6F6CF0[0] && unk_6F7A78 )
        {
          return unk_6F7A78(-1, -1);
        }
        else if ( unk_6F73A0 && unk_6F7A30 )
        {
          return unk_6F7A30(-1, -1);
        }
        else if ( byte_6F6E60[0] && unk_6F7818 )
        {
          return unk_6F7818(-1, -1);
        }
      }
      return result;
    }
    if ( a1 == 1 )
    {
      rf_options_menu_disable_pane_input_and_hide();
      return rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
    if ( a1 != 15 )
    {
      if ( a1 == 28 )
      {
        result = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, dword_6F69D0);
        if ( *(_DWORD *)(*(_DWORD *)result + 32) )
        {
          v2 = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, dword_6F69D0);
          (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(-1);
          return rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        return result;
      }
      goto LABEL_50;
    }
    ++dword_6F69D0;
    if ( dword_6F69D0 >= rf_receiver_get_first_dword(dword_6F7980) )
      dword_6F69D0 = 0;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
  if ( a1 == 205 )
  {
    if ( unk_6F6CA8 )
    {
      v6 = rf_ui_slider_value_get(flt_6F6CA0) + 0.1000000014901161;
      rf_ui_slider_set_value_clamped(flt_6F6CA0, v6);
      rf_graphics_gamma = rf_ui_slider_value_get(flt_6F6CA0);
      rf_graphics_gamma_percent = (int)(rf_graphics_gamma * 100.0);
      rf_graphics_gamma_set(rf_graphics_gamma);
      return rf_gamesound_play_event(46, 0, 0.0, 1.0);
    }
    else if ( unk_6F75A8 && unk_6F7AC0 )
    {
      return unk_6F7AC0(-1, -1);
    }
    else if ( byte_6F6CF0[0] && unk_6F7030 )
    {
      return unk_6F7030(-1, -1);
    }
    else if ( unk_6F73A0 && unk_6F7370 )
    {
      return unk_6F7370(-1, -1);
    }
    else
    {
      result = byte_6F6E60[0];
      if ( byte_6F6E60[0] && unk_6F6FE8 )
        return unk_6F6FE8(-1, -1);
    }
    return result;
  }
  if ( a1 == 4111 )
  {
    if ( --dword_6F69D0 < 0 )
      dword_6F69D0 = rf_receiver_get_first_dword(dword_6F7980) - 1;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
LABEL_50:
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F7980);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, i) + 28) == a1 )
    {
      v3 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F7980, i);
      (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v3 + 4))(*v3, *v3);
      result = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, i);
      if ( *(_DWORD *)(*(_DWORD *)result + 32) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(dword_6F7980, i);
        (*(void (__cdecl **)(_DWORD))(*(_DWORD *)v4 + 32))(0);
        return rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      return result;
    }
  }
  return result;
}

