// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046D310 rf_audio_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl FULL keyDWORD.1 hide OPTIONS pane/sound43.15 focus6F8464++/wrap focus-list6F88F4 count;100F decrement/negative wrapcount-1,always42,NO
// disabled skip/empty-count guard.203/205:choose FIRST slider with BYTE8 nonzero in order effects6F8790,music6F8548,messages6F8590. Readvalue minus/plus original
// double0.10000000149011612,roundfloat BEFORE clamped set,read back clamped slider,call channel_gain_set(channel0/1/2,FLOAT);then sound47/46 even unchanged atlimit. Setter channel
// word cleanup4 leaves FLOAT arg slot reused as sound gain1.0;not wrong setter ABI. No selected slider ->no adjustment/sound. NO special Enter28 branch;all other
// keys,including28,scan focus-list DWORD28 hotkeys. FIRST match virtual+4 ECX/noargs;nonnull callback32 TWO(0,0),sound43,stop;NO BYTE9 check or explicit focus-index assignment.
// Hotkey cleanup4 reuses leftover coordinate as gain. No own mainInput/paneInput/channel/saved-config validation or persistence;parent driver owns admission.
int __cdecl rf_audio_handle_key(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  int v3; // eax
  float v4; // [esp+4h] [ebp-28h]
  float v5; // [esp+4h] [ebp-28h]
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+4h] [ebp-28h]
  float v8; // [esp+4h] [ebp-28h]
  float v9; // [esp+4h] [ebp-28h]
  float v10; // [esp+Ch] [ebp-20h]
  float v11; // [esp+10h] [ebp-1Ch]
  float v12; // [esp+14h] [ebp-18h]
  float v13; // [esp+18h] [ebp-14h]
  float v14; // [esp+1Ch] [ebp-10h]
  float v15; // [esp+20h] [ebp-Ch]
  int i; // [esp+28h] [ebp-4h]

  if ( a1 <= 203 )
  {
    if ( a1 == 203 )
    {
      result = byte_6F8790[0];
      if ( byte_6F8790[0] )
      {
        v12 = rf_ui_slider_value_get(unk_6F8788) - 0.1000000014901161;
        rf_ui_slider_set_value_clamped(unk_6F8788, v12);
        v7 = rf_ui_slider_value_get(unk_6F8788);
        rf_sound_channel_group_set_gain(0, v7);
        return rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
      else if ( unk_6F8548 )
      {
        v11 = rf_ui_slider_value_get(unk_6F8540) - 0.1000000014901161;
        rf_ui_slider_set_value_clamped(unk_6F8540, v11);
        v8 = rf_ui_slider_value_get(unk_6F8540);
        rf_sound_channel_group_set_gain(1u, v8);
        return rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
      else if ( unk_6F8590 )
      {
        v10 = rf_ui_slider_value_get(unk_6F8588) - 0.1000000014901161;
        rf_ui_slider_set_value_clamped(unk_6F8588, v10);
        v9 = rf_ui_slider_value_get(unk_6F8588);
        rf_sound_channel_group_set_gain(2u, v9);
        return rf_gamesound_play_event(47, 0, 0.0, 1.0);
      }
      return result;
    }
    if ( a1 == 1 )
    {
      rf_options_menu_disable_pane_input_and_hide();
      return rf_gamesound_play_event(43, 0, 0.0, 1.0);
    }
    if ( a1 != 15 )
      goto LABEL_30;
    ++dword_6F8464;
    if ( dword_6F8464 >= rf_receiver_get_first_dword(dword_6F88F4) )
      dword_6F8464 = 0;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
  if ( a1 == 205 )
  {
    result = byte_6F8790[0];
    if ( byte_6F8790[0] )
    {
      v15 = rf_ui_slider_value_get(unk_6F8788) + 0.1000000014901161;
      rf_ui_slider_set_value_clamped(unk_6F8788, v15);
      v4 = rf_ui_slider_value_get(unk_6F8788);
      rf_sound_channel_group_set_gain(0, v4);
      return rf_gamesound_play_event(46, 0, 0.0, 1.0);
    }
    else if ( unk_6F8548 )
    {
      v14 = rf_ui_slider_value_get(unk_6F8540) + 0.1000000014901161;
      rf_ui_slider_set_value_clamped(unk_6F8540, v14);
      v5 = rf_ui_slider_value_get(unk_6F8540);
      rf_sound_channel_group_set_gain(1u, v5);
      return rf_gamesound_play_event(46, 0, 0.0, 1.0);
    }
    else if ( unk_6F8590 )
    {
      v13 = rf_ui_slider_value_get(unk_6F8588) + 0.1000000014901161;
      rf_ui_slider_set_value_clamped(unk_6F8588, v13);
      v6 = rf_ui_slider_value_get(unk_6F8588);
      rf_sound_channel_group_set_gain(2u, v6);
      return rf_gamesound_play_event(46, 0, 0.0, 1.0);
    }
    return result;
  }
  if ( a1 == 4111 )
  {
    if ( --dword_6F8464 < 0 )
      dword_6F8464 = rf_receiver_get_first_dword(dword_6F88F4) - 1;
    return rf_gamesound_play_event(42, 0, 0.0, 1.0);
  }
LABEL_30:
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(dword_6F88F4);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F88F4, i) + 28) == a1 )
    {
      v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F88F4, i);
      (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
      result = rf_inline_dword_array4_element_address_unchecked(dword_6F88F4, i);
      if ( *(_DWORD *)(*(_DWORD *)result + 32) )
      {
        v3 = rf_inline_dword_array4_element_address_unchecked(dword_6F88F4, i);
        (*(void (__cdecl **)(_DWORD))(*(_DWORD *)v3 + 32))(0);
        return rf_gamesound_play_event(43, 0, 0.0, 1.0);
      }
      return result;
    }
  }
  return result;
}

