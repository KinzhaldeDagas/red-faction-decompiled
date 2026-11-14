// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057BB70 rf_vfile_configure_optical_volume_labels_and_root
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl signed label count, array of label cstrings, optional relative media directory. Stores count189CE98 unchanged; loops signed i<count copying labels unbounded into256-byte slots1898D90+256*i. Does not validate count or truncate/clear unused slots. Sets media root1898C90 to literal z:\ (raw four bytes7A3A5C00, not code pointer), appends optional directory verbatim, appends backslash only when final byte differs. No slash normalization or path-capacity guard. Returns root length BEFORE any appended final backslash, incidental length rather than status. Does not discover media until57BCF0.
unsigned int __cdecl rf_vfile_configure_optical_volume_labels_and_root(
        int label_count,
        const char *const *labels,
        const char *relative_directory)
{
  char v3; // dl
  unsigned int result; // eax
  char *v5; // [esp+4Ch] [ebp-10h]
  const char *v6; // [esp+50h] [ebp-Ch]
  int i; // [esp+58h] [ebp-4h]

  dword_189CE98 = label_count;
  for ( i = 0; i < label_count; ++i )
  {
    v6 = labels[i];
    v5 = &unk_1898D90[256 * i];
    do
    {
      v3 = *v6;
      *v5++ = *v6++;
    }
    while ( v3 );
  }
  dword_1898C90 = (int)&loc_5C3A7A;
  if ( relative_directory )
    strcat((char *)&dword_1898C90, relative_directory);
  result = strlen((const char *)&dword_1898C90);
  if ( byte_1898C8F[result] != 92 )
  {
    result = strlen((const char *)&dword_1898C90);
    *((_BYTE *)&dword_1898C90 + result) = 92;
    *(_BYTE *)(result + 25791633) = 0;
  }
  return result;
}

