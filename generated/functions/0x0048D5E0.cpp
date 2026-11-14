// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D5E0 rf_cstring_contains_non_decimal_digit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl Cstring, full EAX Boolean. NULL returns0. Computes length then signed-scans bytes; returns1 at first byte not exactly one of ASCII '0'..'9',else0. Empty string returns0. No
// numeric conversion, octet-range check, whitespace/sign acceptance or locale-dependent digit classification. Helper result means invalid numeric token, not is_numeric true.
int __cdecl rf_cstring_contains_non_decimal_digit(const char *a1)
{
  signed int v2; // kr00_4
  char v3; // [esp+13h] [ebp-9h]
  signed int i; // [esp+18h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = strlen(a1);
  for ( i = 0; i < v2; ++i )
  {
    v3 = a1[i];
    if ( v3 != 48
      && v3 != 49
      && v3 != 50
      && v3 != 51
      && v3 != 52
      && v3 != 53
      && v3 != 54
      && v3 != 55
      && v3 != 56
      && v3 != 57 )
    {
      return 1;
    }
  }
  return 0;
}

