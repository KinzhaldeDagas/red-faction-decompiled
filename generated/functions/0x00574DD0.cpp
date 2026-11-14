// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574DD0 rf_bitmap_name_hash_rotate6_lower_abs
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Null string returns unsigned-1. Otherwise starts signed accumulator0; for each byte rotates left6 and XORs sign-extended char result of tolower((char)byte), then returns abs32(accumulator). Empty string returns0. ASCII case-insensitive behavior; signed non-ASCII input is passed directly to tolower, no unsigned-byte normalization. INT_MIN absolute can remain negative/0x80000000. No canonical path or extension normalization.
unsigned int __cdecl rf_bitmap_name_hash_rotate6_lower_abs(_BYTE *a1)
{
  int v2; // [esp+4h] [ebp-8h]
  _BYTE *i; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return -1;
  v2 = 0;
  for ( i = a1; *i; ++i )
    v2 = __ROL4__(v2, 6) ^ (char)tolower((char)*i);
  return abs32(v2);
}

