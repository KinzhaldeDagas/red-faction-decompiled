// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B6B0 rf_vfile_build_optical_media_path_unbounded
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl root id, optional filename, destination. Unbounded-copies optical-media root1898C90 (configured by57BB70 and drive letter selected by57BCF0). Nonzero id appends registered root1897490+12*id and then one backslash, even if registered root already ends in one. Nonnull filename appended verbatim; returns destination. No capacity, slash normalization, id validity or media-presence check here. Layout mirrors loose-path57B560 but with optical root prefix.
char *__cdecl rf_vfile_build_optical_media_path_unbounded(int a1, const char *a2, char *a3)
{
  char v3; // dl
  char *v5; // [esp+50h] [ebp-8h]
  int *v6; // [esp+54h] [ebp-4h]

  v6 = &dword_1898C90;
  v5 = a3;
  do
  {
    v3 = *(_BYTE *)v6;
    *v5 = *(_BYTE *)v6;
    v6 = (int *)((char *)v6 + 1);
    ++v5;
  }
  while ( v3 );
  if ( a1 )
  {
    qmemcpy(
      &a3[strlen(a3)],
      (const void *)dword_1897490[3 * a1],
      dword_1897490[3 * a1] + strlen((const char *)dword_1897490[3 * a1]) + 1 - dword_1897490[3 * a1]);
    *(_WORD *)&a3[strlen(a3)] = 92;
  }
  if ( a2 )
    strcat(a3, a2);
  return a3;
}

