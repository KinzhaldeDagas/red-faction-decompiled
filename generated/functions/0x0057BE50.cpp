// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057BE50 rf_path_convert_forward_slashes_to_backslashes_in_place
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl mutable NUL-terminated path. Computes original strlen then visits each byte: slash or backslash becomes backslash, all other bytes untouched. No duplicate-slash collapse, dot resolution, case folding or trailing-separator removal. AL return is low8 bits of original length (empty0), not pointer/success; no input NULL guard.
char __cdecl rf_path_convert_forward_slashes_to_backslashes_in_place(char *a1)
{
  char result; // al
  char *v3; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]

  v3 = a1;
  do
    result = *v3;
  while ( *v3++ );
  for ( i = 0; i < v3 - (a1 + 1); ++i )
  {
    if ( a1[i] == 47 || a1[i] == 92 )
      a1[i] = 92;
    result = i + 1;
  }
  return result;
}

