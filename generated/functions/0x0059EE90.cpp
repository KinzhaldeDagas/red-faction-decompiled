// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059EE90 rf_vpackfile_add
// UNREALRED VERIFIED [vpp-streaming] Mounts one archive. A case-insensitive archive-name match returns success without reloading, so the first same-named pack wins; at most 256 packs are mounted.
int __cdecl rf_vpackfile_add(char *Source, const char *a2)
{
  FILE *Stream; // [esp+28h] [ebp-414h]
  int v4; // [esp+2Ch] [ebp-410h]
  int i; // [esp+30h] [ebp-40Ch]
  char Buffer; // [esp+34h] [ebp-408h] BYREF
  _BYTE v7[3]; // [esp+35h] [ebp-407h] BYREF
  char *Destination; // [esp+438h] [ebp-4h]

  v4 = 0;
  for ( i = 0; i < rf_vpackfile_count; ++i )
  {
    if ( !_stricmp(Source, &rf_vpackfiles[176 * i]) )
      return 1;
  }
  if ( a2 )
    sprintf(&Buffer, "%s%s%s", &unk_189CD90, a2, Source);
  else
    sprintf(&Buffer, "%s%s", &unk_189CD90, Source);
  Stream = fopen(&Buffer, "rb");
  if ( Stream )
  {
    v4 = 1;
    fclose(Stream);
  }
  if ( !v4 )
    return 0;
  if ( rf_vpackfile_count >= 256 )
    return 0;
  if ( !Source || strlen(Source) > 0x1F || (unsigned int)(&v7[strlen(&Buffer)] - v7) > 0x7F )
    return 0;
  Destination = &rf_vpackfiles[176 * rf_vpackfile_count++];
  strncpy(Destination, Source, 0x1Fu);
  strncpy(Destination + 32, &Buffer, 0x7Fu);
  *((_DWORD *)Destination + 40) = 0;
  *((_DWORD *)Destination + 41) = 0;
  *((_DWORD *)Destination + 42) = 0;
  return rf_vpackfile_load_internal((int)Destination);
}

