// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B980 rf_input_keycode_to_character
// UNREALRED VERIFIED [list-selection-20261029]: Argument16-bit keycode. Global enable0x193B680 must be nonzero and low8 scan code<127,else returns255. Bit0x1000 selects DWORD map0x664160,otherwise map0x663F60,indexed by low8 code. Returns full mapped DWORD;other keycode flags ignored. No queue read,locale conversion or explicit lowercase normalization. Text-list type-ahead clears0x1000 before calling,forcing unshifted map.
int __cdecl rf_input_keycode_to_character(__int16 a1)
{
  if ( !byte_193B680 )
    return 255;
  if ( (unsigned __int8)a1 >= 0x7Fu )
    return 255;
  if ( (a1 & 0x1000) != 0 )
    return dword_664160[(unsigned __int8)a1];
  return dword_663F60[(unsigned __int8)a1];
}

