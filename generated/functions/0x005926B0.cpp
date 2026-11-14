// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005926B0 rf_vfile_lowercase_lookup_name
// UNREALRED VERIFIED [vfile-loose-precedence] Canonicalizes a loose-file lookup key by ASCII-lowercasing the complete request.
int __cdecl rf_vfile_lowercase_lookup_name(_BYTE *a1, char *a2)
{
  int result; // eax
  char v3; // [esp+3h] [ebp-1h]

  do
  {
    v3 = *a2++;
    if ( v3 >= 65 && v3 <= 90 )
      v3 += 32;
    *a1++ = v3;
    result = v3;
  }
  while ( v3 );
  return result;
}

