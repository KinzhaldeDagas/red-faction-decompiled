// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ECCC0 rf_fpgun_find_type_by_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Scans signed count87C6D8 of52-byte records87C798. Case-insensitive comparison of input C string with record RFString+0; returns first matching index or-1. No separate range cap, normalization or duplicate resolution.
int __cdecl rf_fpgun_find_type_by_name(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_87C6D8; ++i )
  {
    if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&byte_87C798[52 * i]) )
      return i;
  }
  return -1;
}

