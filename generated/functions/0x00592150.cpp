// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592150 rf_command_line_get_unconsumed_argument_by_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl zero-based ordinal among tokens whose consumed byte1BA1D4C+8*i is0, scanning count1BA1EDC. Returns corresponding stored cstring pointer1BA1D48+8*i or NULL if no such ordinal. Decrements ordinal only on unconsumed entries; does not mark returned token, remove it or allocate. Negative ordinal has no normal match; no explicit bounds check.
char *__cdecl rf_command_line_get_unconsumed_argument_by_index(int ordinal)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_1BA1EDC; ++i )
  {
    if ( !byte_1BA1D4C[8 * i] )
    {
      if ( !ordinal )
        return (char *)dword_1BA1D48[2 * i];
      --ordinal;
    }
  }
  return nullptr;
}

