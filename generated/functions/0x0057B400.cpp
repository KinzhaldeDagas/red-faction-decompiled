// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B400 rf_vfile_copy_loose_directory_cstring_unbounded
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl root id and destination. Unbounded-copies data root189CD90; nonzero id concatenates registered root at1897490+12*id WITHOUT extra separator. Id0 sets destination[strlen(destination)-1]=0, unconditionally deleting final byte (underflows destination when root empty). Returns destination base. No capacity, id, NULL or special-id checks.
char *__cdecl rf_vfile_copy_loose_directory_cstring_unbounded(int a1, char *a2)
{
  char v2; // dl
  char *v4; // [esp+3Ch] [ebp-8h]
  char *v5; // [esp+40h] [ebp-4h]

  v5 = &unk_189CD90;
  v4 = a2;
  do
  {
    v2 = *v5;
    *v4++ = *v5++;
  }
  while ( v2 );
  if ( a1 )
    qmemcpy(
      &a2[strlen(a2)],
      (const void *)dword_1897490[3 * a1],
      dword_1897490[3 * a1] + strlen((const char *)dword_1897490[3 * a1]) + 1 - dword_1897490[3 * a1]);
  else
    a2[strlen(a2) - 1] = 0;
  return a2;
}

