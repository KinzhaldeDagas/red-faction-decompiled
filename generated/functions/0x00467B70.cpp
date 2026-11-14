// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467B70 rf_options_menu_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Read absoluteXY;hit-test EXACT5 pointers6F6008. Hit+left press:changed focus6F5FFC store/sound40,activate hit index467950 (fixed switch,not a control
// callback). Hit/no press:only paneInput6F6000==0 admits hover;nonzero relativeXY OR buttonXspeed6F601C nonzero/UNORDERED NaN permits changed focus/sound40. No hit no main focus
// work. Then ALWAYS route pointer by CURRENT pane661FF4:0 Game46CB80,1 Video46B3A0,2 Audio46D810,3 Controls4697A0,same absoluteXY,TWO args;NO paneInput gate at this final routing. A
// disabled/hiding current pane can still receive pointer updates until animation commits another pane. Driver owns mainInput/suppression gate.
void rf_options_menu_update_pointer()
{
  int v0; // [esp+Ch] [ebp-14h] BYREF
  int v1; // [esp+10h] [ebp-10h] BYREF
  int physical_x; // [esp+14h] [ebp-Ch] BYREF
  int physical_y; // [esp+18h] [ebp-8h] BYREF
  int v4; // [esp+1Ch] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  v4 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F6008, 5);
  if ( v4 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( dword_6F5FFC != v4 )
      {
        dword_6F5FFC = v4;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
      rf_options_menu_activate_item(v4);
    }
    else if ( !byte_6F6000[0] )
    {
      rf_mouse_get_relative_deltas(&v1, &v0, &unk_193A03C);
      if ( (v1 || v0 || unk_6F601C != 0.0) && dword_6F5FFC != v4 )
      {
        dword_6F5FFC = v4;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
    }
  }
  switch ( dword_661FF4 )
  {
    case 0:
      rf_gameplay_update_pointer(physical_x, physical_y);
      break;
    case 1:
      rf_performance_update_pointer(physical_x, physical_y);
      break;
    case 2:
      rf_audio_update_pointer(physical_x, physical_y);
      break;
    case 3:
      rf_controls_update_pointer(physical_x, physical_y);
      break;
    default:
      return;
  }
}

