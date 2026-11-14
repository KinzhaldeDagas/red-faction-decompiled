// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B560 rf_vfile_build_loose_path
// UNREALRED VERIFIED [vfile-loose-precedence] Builds a physical loose-file path from the RF data root, an optional registered search root, and the requested relative filename.
char *__cdecl rf_vfile_build_loose_path(int a1, const char *a2, char *a3)
{
  char v3; // dl
  char *v5; // [esp+50h] [ebp-8h]
  char *v6; // [esp+54h] [ebp-4h]

  v6 = &unk_189CD90;
  v5 = a3;
  do
  {
    v3 = *v6;
    *v5++ = *v6++;
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

