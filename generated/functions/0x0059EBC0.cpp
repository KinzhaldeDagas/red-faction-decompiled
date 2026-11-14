// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059EBC0 rf_vpackfile_calc_file_name_checksum
// UNREALRED VERIFIED [vpp-streaming] Computes the case-folded VPP filename checksum using ROL32(hash, 5) XOR tolower(byte), then absolute value.
// UNREALRED VERIFIED [streaming-contract-20260829] Consumes a NUL-terminated member name byte-by-byte; a valid fixed-width VPP filename must therefore contain NUL within its 60-byte field.
unsigned int __cdecl rf_vpackfile_calc_file_name_checksum(_BYTE *a1)
{
  int v2; // [esp+4h] [ebp-8h]
  _BYTE *i; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return -1;
  v2 = 0;
  for ( i = a1; *i; ++i )
    v2 = __ROL4__(v2, 5) ^ (char)tolower((char)*i);
  return abs32(v2);
}

