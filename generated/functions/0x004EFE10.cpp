// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFE10 rf_register_loose_search_roots_recursive
// UNREALRED VERIFIED [loose-root-registration] Recursively walks child directories (excluding ps2), registering each directory with the supplied extension mask and alternate-media flag zero.
void __cdecl rf_register_loose_search_roots_recursive(char *Path, char *a2, char *a3, int a4)
{
  char v4; // [esp+3h] [ebp-2B9h]
  char *v5; // [esp+8h] [ebp-2B4h]
  char *v6; // [esp+Ch] [ebp-2B0h]
  char v7; // [esp+27h] [ebp-295h]
  char *v8; // [esp+2Ch] [ebp-290h]
  char *name; // [esp+30h] [ebp-28Ch]
  char *DstBuf; // [esp+88h] [ebp-234h]
  char v11[256]; // [esp+8Ch] [ebp-230h] BYREF
  struct _finddata64i32_t FindData; // [esp+18Ch] [ebp-130h] BYREF
  intptr_t FindHandle; // [esp+2B8h] [ebp-4h]

  if ( a4 )
  {
    _chdir(Path);
    _chdir(a2);
  }
  DstBuf = (char *)operator new(0x104u);
  if ( !_getcwd(DstBuf, 260) )
    exit(1);
  _chdir(DstBuf);
  rf_vfile_register_loose_search_root(&DstBuf[strlen(Path) + 1], a3, 0);
  v11[0] = 0;
  FindHandle = _findfirst64i32("*.*", &FindData);
  if ( FindHandle != -1 )
  {
    while ( (!strcmp(FindData.name, ".") || !strcmp(FindData.name, "..")) && strcmp(v11, FindData.name) )
    {
      name = FindData.name;
      v8 = v11;
      do
      {
        v7 = *name;
        *v8++ = *name++;
      }
      while ( v7 );
      _findnext64i32(FindHandle, &FindData);
    }
    while ( strcmp(v11, FindData.name) )
    {
      if ( (FindData.attrib & 0x10) != 0 && _stricmp(FindData.name, "ps2") )
      {
        _chdir(FindData.name);
        rf_register_loose_search_roots_recursive(Path, a2, (int)a3, 0);
      }
      v6 = FindData.name;
      v5 = v11;
      do
      {
        v4 = *v6;
        *v5++ = *v6++;
      }
      while ( v4 );
      _findnext64i32(FindHandle, &FindData);
    }
  }
  if ( !a4 )
    _chdir("..");
  operator delete(DstBuf);
}

