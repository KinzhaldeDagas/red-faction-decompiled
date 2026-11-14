// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00465670 rf_browser_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Cdecl FULL keyDWORD,initially untyped ABI retained;driver supplies input gate. Original byte-selector/jump tables verified:1 Back(-1,-1)/sound43;15
// focus++/wrap0 against focus-list6F5C60 count/sound42;100F focus--/negative wrapcount-1/sound42. Neither focus traversal skips disabled controls or guards empty count.28:focused
// callbackDWORD32 nonNULL AND BYTE9 nonzero ->TWO(-1,-1),then sound43. Native ADD ESP4 cleans first sentinel;remaining sentinel reused for sound gain1.0,not a one-argument
// callback.203/205:filter-group BYTE6F54B0 nonzero and previous/next callback5358/5800 nonNULL ->TWO(-1,-1),no own sound.200/208:list BYTE6F57BC nonzero,displayselection>0
// or<visibleCount-1,and CURRENT mapped raw row>=0/<liveCount ->decrement/increment displayselection then load NEW rawselected661F9C WITHOUT validating new mapping. Current display
// index lacks full bounds checks (down allows negative,up lacks upper);always ensure selected visible4655D0 even if move rejected. Other keys scan ENTIRE focus list:each matching
// hotkeyDWORD28 sets focus BEFORE callback/state9 checks;nonnull enabled callbacks getTWO(-1,-1)/sound43. No break after match,so duplicate hotkeys may invoke several controls. No
// key normalization or direct query/send.
void __cdecl rf_browser_handle_key(int a1)
{
  int v1; // eax
  int v2; // eax
  int i; // [esp+Ch] [ebp-4h]

  if ( a1 > 203 )
  {
    switch ( a1 )
    {
      case 205:
        if ( unk_6F54B0 && unk_6F5800 )
          unk_6F5800(-1, -1);
        break;
      case 208:
        if ( unk_6F57BC
          && dword_6F52E0 < (int)(MEMORY[0x6F5088] - 1)
          && *((int *)MEMORY[0x6F52D4] + dword_6F52E0) >= 0
          && *((_DWORD *)MEMORY[0x6F52D4] + dword_6F52E0) < dword_6F51A8 )
        {
          ++dword_6F52E0;
          dword_661F9C = *((_DWORD *)MEMORY[0x6F52D4] + dword_6F52E0);
        }
LABEL_32:
        rf_browser_ensure_selected_row_visible();
        break;
      case 4111:
        if ( --dword_6F519C < 0 )
          dword_6F519C = rf_receiver_get_first_dword(unk_6F5C60) - 1;
LABEL_15:
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
        break;
      default:
LABEL_39:
        for ( i = 0; i < rf_receiver_get_first_dword(unk_6F5C60); ++i )
        {
          if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, i) + 28) == a1 )
          {
            dword_6F519C = i;
            if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, i) + 32) )
            {
              if ( *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, i) + 9) )
              {
                v2 = rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, dword_6F519C);
                (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(-1);
                rf_gamesound_play_event(43, 0, 0.0, 1.0);
              }
            }
          }
        }
        break;
    }
  }
  else if ( a1 == 203 )
  {
    if ( unk_6F54B0 && unk_6F5358 )
      unk_6F5358(-1, -1);
  }
  else
  {
    switch ( a1 )
    {
      case 1:
        rf_browser_request_back();
        rf_gamesound_play_event(43, 0, 0.0, 1.0);
        break;
      case 15:
        ++dword_6F519C;
        if ( dword_6F519C >= rf_receiver_get_first_dword(unk_6F5C60) )
          dword_6F519C = 0;
        goto LABEL_15;
      case 28:
        if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, dword_6F519C) + 32)
          && *(_BYTE *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, dword_6F519C) + 9) )
        {
          v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F5C60, dword_6F519C);
          (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(-1);
          rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        break;
      case 200:
        if ( unk_6F57BC
          && dword_6F52E0 > 0
          && *((int *)MEMORY[0x6F52D4] + dword_6F52E0) >= 0
          && *((_DWORD *)MEMORY[0x6F52D4] + dword_6F52E0) < dword_6F51A8 )
        {
          --dword_6F52E0;
          dword_661F9C = *((_DWORD *)MEMORY[0x6F52D4] + dword_6F52E0);
        }
        goto LABEL_32;
      default:
        goto LABEL_39;
    }
  }
}

