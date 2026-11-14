// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470A40 rf_ui_edit_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall FULL-DWORD key, RET4. Converts via keycode_to_character, SIGN-EXTENDS resulting char into CRT isprint; printable except percent37 and
// backslash92 is forwarded to append470910 and returns its AL. Otherwise switches original unmasked key:14 backspace removes final inline byte if nonempty and returnsAL1 even empty;
// keypad71/72/73 ->7/8/9,75/76/77 ->4/5/6,79/80/81 ->1/2/3,82->0,83->period, via append helper. DefaultAL0. No explicit Enter/Escape handler, focus/enable gate, caret reset or
// normalized consumed-key writeback. Native selector470BC8 and13-way jump table470B94 verified against original PE.
char __thiscall rf_ui_edit_handle_key(const char *this, int a2)
{
  char result; // al
  const char *v3; // [esp+Ch] [ebp-14h]
  char v5; // [esp+1Bh] [ebp-5h]

  v5 = rf_input_keycode_to_character(a2);
  if ( isprint(v5) && v5 != 37 && v5 != 92 )
    return rf_ui_edit_append_character((int)this, v5);
  switch ( a2 )
  {
    case 14:
      v3 = this + strlen(this + 64) + 65;
      if ( v3 - (this + 65) > 0 )
        *((_BYTE *)v3 - 2) = 0;
      result = 1;
      break;
    case 71:
      result = rf_ui_edit_append_character((int)this, 55);
      break;
    case 72:
      result = rf_ui_edit_append_character((int)this, 56);
      break;
    case 73:
      result = rf_ui_edit_append_character((int)this, 57);
      break;
    case 75:
      result = rf_ui_edit_append_character((int)this, 52);
      break;
    case 76:
      result = rf_ui_edit_append_character((int)this, 53);
      break;
    case 77:
      result = rf_ui_edit_append_character((int)this, 54);
      break;
    case 79:
      result = rf_ui_edit_append_character((int)this, 49);
      break;
    case 80:
      result = rf_ui_edit_append_character((int)this, 50);
      break;
    case 81:
      result = rf_ui_edit_append_character((int)this, 51);
      break;
    case 82:
      result = rf_ui_edit_append_character((int)this, 48);
      break;
    case 83:
      result = rf_ui_edit_append_character((int)this, 46);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

