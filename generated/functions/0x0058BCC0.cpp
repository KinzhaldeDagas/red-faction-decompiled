// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BCC0 rf_input_keycode_is_modifier_scan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered cdecl keycode predicate. Masks low8 bits and returns true for scans29,41,42,54,56,157,184 only. Thus ignores encoded modifier flags and always recognizes scan41 regardless modifier-enable policy. No initialized guard, remap or state-array read. The decompiler signed-char cases-99/-72 are byte values157/184; original switch uses AND0xFF then jump table.
bool __cdecl rf_input_keycode_is_modifier_scan(int keycode)
{
  bool result; // al

  switch ( (char)keycode )
  {
    case 29:
    case 41:
    case 42:
    case 54:
    case 56:
    case -99:
    case -72:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

