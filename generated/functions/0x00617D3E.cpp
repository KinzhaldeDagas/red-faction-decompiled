// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617D3E ___crtGetEnvironmentStringsA
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, malloc_crt-owned ANSI environment
// block/NULL. Cached mode2021DB0:0 unknown,1 Unicode,2 ANSI; other nonzero ->NULL. Unknown calls GetEnvironmentStringsW: success caches1 and uses block; failure with LastError120
// caches2, other failure leaves mode0 and uses ANSI fallback for this call. Mode1 failure obtaining W block returnsNULL, no ANSI fallback. Scan NUL-separated W block to final
// terminator, include that final WCHAR; WideCharToMultiByte(CP_ACP0,flags0,explicit total units,NULL,0,NULL,NULL), malloc requiredbytes, second conversion; conversion0 frees
// allocation/NULL. Always FreeEnvironmentStringsW after obtained W block. ANSI fallback GetEnvironmentStrings, scan entries to final NUL including it, malloc exact bytes,
// memcpy,FreeEnvironmentStringsA; alloc failure also frees OS block. Returns independently allocated block; no own errno mapping, lock or preservation of OS allocation. For initially
// empty OS block scan length is ONE terminator only, not forced two.
CHAR *__crtGetEnvironmentStringsA()
{
  int v0; // eax
  CHAR *v1; // ebx
  WCHAR *EnvironmentStringsW; // edi
  WCHAR *i; // eax
  size_t v5; // eax
  CHAR *v6; // eax
  LPCH EnvironmentStrings; // eax
  CHAR *v8; // esi
  void *v9; // eax
  void *v10; // edi
  int cchWideChar; // [esp+Ch] [ebp-Ch]
  int cbMultiByte; // [esp+10h] [ebp-8h]
  size_t cbMultiBytea; // [esp+10h] [ebp-8h]
  CHAR *Block; // [esp+14h] [ebp-4h]

  v0 = unk_2021DB0;
  v1 = nullptr;
  EnvironmentStringsW = nullptr;
  if ( !unk_2021DB0 )
  {
    EnvironmentStringsW = GetEnvironmentStringsW();
    if ( EnvironmentStringsW )
    {
      unk_2021DB0 = 1;
      goto LABEL_8;
    }
    if ( GetLastError() == 120 )
    {
      v0 = 2;
      unk_2021DB0 = 2;
    }
    else
    {
      v0 = unk_2021DB0;
    }
  }
  if ( v0 == 1 )
  {
LABEL_8:
    if ( !EnvironmentStringsW )
    {
      EnvironmentStringsW = GetEnvironmentStringsW();
      if ( !EnvironmentStringsW )
        return nullptr;
    }
    for ( i = EnvironmentStringsW; *i; ++i )
    {
      do
        ++i;
      while ( *i );
    }
    cchWideChar = i - EnvironmentStringsW + 1;
    v5 = WideCharToMultiByte(0, 0, EnvironmentStringsW, cchWideChar, nullptr, 0, nullptr, nullptr);
    cbMultiByte = v5;
    if ( v5 )
    {
      v6 = (CHAR *)_malloc_crt(v5);
      Block = v6;
      if ( v6 )
      {
        if ( !WideCharToMultiByte(0, 0, EnvironmentStringsW, cchWideChar, v6, cbMultiByte, nullptr, nullptr) )
        {
          free(Block);
          Block = nullptr;
        }
        v1 = Block;
      }
    }
    FreeEnvironmentStringsW(EnvironmentStringsW);
    return v1;
  }
  if ( v0 != 2 && v0 )
    return nullptr;
  EnvironmentStrings = GetEnvironmentStrings();
  v8 = EnvironmentStrings;
  if ( !EnvironmentStrings )
    return nullptr;
  for ( ; *EnvironmentStrings; ++EnvironmentStrings )
  {
    do
      ++EnvironmentStrings;
    while ( *EnvironmentStrings );
  }
  cbMultiBytea = EnvironmentStrings - v8 + 1;
  v9 = _malloc_crt(cbMultiBytea);
  v10 = v9;
  if ( !v9 )
  {
    FreeEnvironmentStringsA(v8);
    return nullptr;
  }
  memcpy(v9, v8, cbMultiBytea);
  FreeEnvironmentStringsA(v8);
  return (CHAR *)v10;
}

