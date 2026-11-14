// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593330 rf_vfile_get_size
// UNREALRED VERIFIED [vfile-loose-precedence] Returns the VPP member's declared byte size or the physical loose file length.
int __thiscall rf_vfile_get_size(int this, char *String2, int a3)
{
  int v4; // eax
  int v6; // [esp+4h] [ebp-8h]
  FILE *Stream; // [esp+8h] [ebp-4h]

  if ( String2 && !rf_vfile_resolve_open_source(this, String2, a3) )
    return -4;
  if ( *(_DWORD *)(this + 264) )
    return *(_DWORD *)(*(_DWORD *)(this + 264) + 12);
  if ( *(int *)(this + 272) >= 0 )
    return unk_189CECC[8208 * *(_DWORD *)(this + 272)];
  Stream = fopen((const char *)(this + 5), "rb");
  if ( !Stream )
    return -4;
  v4 = _fileno(Stream);
  v6 = _filelength(v4);
  fclose(Stream);
  return v6;
}

