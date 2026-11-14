// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004691E0 rf_controls_handle_key_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl keyDWORD POINTER,not keyvalue. Capture6F62B4==EXACT1 AND *key>0:raw EXACT1 ends capture;allother positive raw keys masked&FFF then accept4683C0;finally
// *key=0 even rejected/polled/no event. No rawpositive key normalization before EXACT1 check. Otherwise native switch:1 disables/hides OPTIONS pane467FA0 (does not clear capture or
// *key);15 focus++/wrap count,100F focus--/wrapcount-1,always sound42/no disabled skip.28 nonnull focused callback32 gets TWO(-1,-1),then sound43;NO BYTE9 guard.203/205 only
// sliderBYTE8(6F6738) nonzero:read sensitivity,subtract/add original double0.10000000149011612,roundfloat,set clamped slider,readback to player228,sound47/46 even unchanged
// atlimit.200/208 only listBYTE8(6F62C8) nonzero:decrement selected/clamp0 or increment/clamp(actionCount-1),ensurevisible,sound46/47;empty count can produce-1. Other keys scan
// focus-list:FIRST matching DWORD28 invokes virtual+4 ECX/noargs then callback32 TWO(-1,-1) WITHOUT NULL or BYTE9 check,then sound43/return;does not explicitly update focus index.
// Callback cleanup4 reuses second sentinel for sound gain;not one-arg ABI. Original selector/jump tables verified;no keyptr/player/focus bounds or own paneInput check.
void __cdecl rf_controls_handle_key_pointer(int *a1)
{
  int v1; // eax
  _DWORD *v2; // eax
  int v3; // eax
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  int v6; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  if ( unk_6F62B4 == 1 && *a1 > 0 )
  {
    if ( *a1 == 1 )
      rf_controls_binding_capture_end();
    else
      rf_controls_accept_binding_input(*a1 & 0xFFF);
    *a1 = 0;
  }
  else
  {
    v6 = *a1;
    if ( *a1 > 203 )
    {
      switch ( v6 )
      {
        case 205:
          if ( unk_6F6738 )
          {
            v5 = rf_ui_slider_value_get(unk_6F6730) + 0.1000000014901161;
            rf_ui_slider_set_value_clamped(unk_6F6730, v5);
            *(float *)(rf_local_fpgun_player + 228) = rf_ui_slider_value_get(unk_6F6730);
            rf_gamesound_play_event(46, 0, 0.0, 1.0);
          }
          break;
        case 208:
          if ( unk_6F62C8 )
          {
            if ( ++dword_6F62BC >= dword_6F62AC )
              dword_6F62BC = dword_6F62AC - 1;
            rf_controls_ensure_selected_action_visible();
            rf_gamesound_play_event(47, 0, 0.0, 1.0);
          }
          break;
        case 4111:
          if ( --dword_6F62B0 < 0 )
            dword_6F62B0 = rf_receiver_get_first_dword(unk_6F6940) - 1;
LABEL_20:
          rf_gamesound_play_event(42, 0, 0.0, 1.0);
          break;
        default:
LABEL_40:
          for ( i = 0; i < rf_receiver_get_first_dword(unk_6F6940); ++i )
          {
            if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, i) + 28) == *a1 )
            {
              v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, i);
              (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
              v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F6940, i);
              (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 32))(-1);
              rf_gamesound_play_event(43, 0, 0.0, 1.0);
              return;
            }
          }
          break;
      }
    }
    else if ( v6 == 203 )
    {
      if ( unk_6F6738 )
      {
        v4 = rf_ui_slider_value_get(unk_6F6730) - 0.1000000014901161;
        rf_ui_slider_set_value_clamped(unk_6F6730, v4);
        *(float *)(rf_local_fpgun_player + 228) = rf_ui_slider_value_get(unk_6F6730);
        rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
    }
    else
    {
      switch ( v6 )
      {
        case 1:
          rf_options_menu_disable_pane_input_and_hide();
          break;
        case 15:
          ++dword_6F62B0;
          if ( dword_6F62B0 >= rf_receiver_get_first_dword(unk_6F6940) )
            dword_6F62B0 = 0;
          goto LABEL_20;
        case 28:
          if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F6940, dword_6F62B0) + 32) )
          {
            v1 = rf_inline_dword_array4_element_address_unchecked(unk_6F6940, dword_6F62B0);
            (*(void (__cdecl **)(int))(*(_DWORD *)v1 + 32))(-1);
            rf_gamesound_play_event(43, 0, 0.0, 1.0);
          }
          break;
        case 200:
          if ( unk_6F62C8 )
          {
            if ( --dword_6F62BC < 0 )
              dword_6F62BC = 0;
            rf_controls_ensure_selected_action_visible();
            rf_gamesound_play_event(46, 0, 0.0, 1.0);
          }
          break;
        default:
          goto LABEL_40;
      }
    }
  }
}

