// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591C40 rf_command_line_match_registered_options
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl. Walks circular option list1BA1EE0, compares every option name pointer+8 case-insensitively against every8-byte argv record at1BA1D48 (count1BA1EDC). For each match sets option byte+20=1 then calls591CC0; no early break or consumed-flag check. Repeated options therefore process repeatedly and can leak replaced argument allocations. Matched flag remains true even when required argument absent/invalid. Does not tokenize command line, reset option state or validate unknown options. EAX loop residue, not match count.
_DWORD *rf_command_line_match_registered_options()
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+0h] [ebp-8h]
  int j; // [esp+4h] [ebp-4h]

  result = dword_1BA1EE0;
  for ( i = dword_1BA1EE0; i != &dword_1BA1EE0; i = (_DWORD *)*i )
  {
    for ( j = 0; j < dword_1BA1EDC; ++j )
    {
      if ( !_stricmp((const char *)i[2], (const char *)dword_1BA1D48[2 * j]) )
      {
        *((_BYTE *)i + 20) = 1;
        rf_command_line_capture_option_following_argument((int)i, j);
      }
      result = (_DWORD *)(j + 1);
    }
  }
  return result;
}

