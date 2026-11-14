// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F39E0 rf_ui_inputbox_keycode_to_character_with_keypad
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): One stack argument;callee pops4,ECX unused. Remaps raw codes71,72,73,75,76,77,79,80,81,82 to top-row codes8,9,10,5,6,7,2,3,4,11 respectively,then calls existing rf_input_keycode_to_character. Others forward unchanged. Remaps only exact values:modifier-combined keypad codes are not stripped here. Returns conversion result.
int __stdcall rf_ui_inputbox_keycode_to_character_with_keypad(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 'G':
      result = rf_input_keycode_to_character(8);
      break;
    case 'H':
      result = rf_input_keycode_to_character(9);
      break;
    case 'I':
      result = rf_input_keycode_to_character(10);
      break;
    case 'K':
      result = rf_input_keycode_to_character(5);
      break;
    case 'L':
      result = rf_input_keycode_to_character(6);
      break;
    case 'M':
      result = rf_input_keycode_to_character(7);
      break;
    case 'O':
      result = rf_input_keycode_to_character(2);
      break;
    case 'P':
      result = rf_input_keycode_to_character(3);
      break;
    case 'Q':
      result = rf_input_keycode_to_character(4);
      break;
    case 'R':
      result = rf_input_keycode_to_character(11);
      break;
    default:
      result = rf_input_keycode_to_character(a1);
      break;
  }
  return result;
}

