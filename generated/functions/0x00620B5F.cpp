// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620B5F ___crtsetenv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(char**ownedAssignment,int primary), status0/-1, no own lock. NULLouter
// invalid22/-1; NULL*outer/missing first mb-aware equals/empty name ->errno22/-1 WITHOUT invalid callback; input retained. Empty value is deletion, cannot install empty-value string.
// If narrowenv equals initial snapshot2021364, deep-copy via copy_environ and publish. If no narrowenv: primary&&wideenv converts through wtomb_environ (failureerrno22/-1); otherwise
// deletion returns0 WITHOUT consuming input or OSupdate; insertion malloc4 initialNULL narrow array, plus wide array if absent; partial new globals retained on failure. findenv
// returns index or -length, emptyarray additionally detected. Existing match: free old string first; insertion replaces pointer,clears*outer; deletion shifts pointers through
// terminator, best-effort recalloc shrink (failure ignored). Missing insertion: signed newCount=length+2, native JL rejects newCount<length (NOT <=); reject
// unsignednewCount>=0x3FFFFFFF,recalloc_crt(old,4,newCount), append input+NULL,clear*outer,publish returnedarray. Missing deletion with existing array frees
// input,clears*outer,return0 BEFORE OSupdate. After change if primary!=0,calloc_crt(strlen(input)+2,1),copy,split at original equals offset,SetEnvironmentVariableA(name,value orNULL
// deletion). API failure sets status-1/errno42 with NO rollback/dosmaperr; temporary allocation failure silently SKIPS OSupdate and leaves status0. Finally deletion frees
// input/clears*outer even after OSfailure; insertion input already transferred. No full transaction, wide-array synchronization after ordinary change or rollback of freed old entry.
int __cdecl __crtsetenv(const unsigned __int8 **a1, int a2)
{
  const unsigned __int8 *v3; // esi
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // edi
  char **v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD *v9; // esi
  int v10; // eax
  size_t v11; // edi
  char *v12; // esi
  char *v13; // eax
  unsigned __int8 **v14; // ecx
  size_t v15; // eax
  char *v16; // edi
  size_t v17; // eax
  unsigned __int8 *v18; // eax
  unsigned __int8 *v19; // [esp+4h] [ebp-14h]
  char *v20; // [esp+8h] [ebp-10h]
  int v21; // [esp+Ch] [ebp-Ch]
  BOOL v22; // [esp+10h] [ebp-8h]
  unsigned __int8 *Block; // [esp+14h] [ebp-4h]

  v21 = 0;
  if ( !a1 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  v3 = *a1;
  Block = (unsigned __int8 *)*a1;
  if ( !*a1 )
    goto LABEL_12;
  v4 = _mbschr(v3, 0x3Du);
  v5 = v4;
  v19 = v4;
  if ( !v4 || v3 == v4 )
    goto LABEL_12;
  v22 = v4[1] == 0;
  v6 = (char **)unk_2021360;
  if ( unk_2021360 == (void *)unk_2021364 )
  {
    v6 = copy_environ((const char **)unk_2021360);
    unk_2021360 = v6;
  }
  if ( !v6 )
  {
    if ( a2 && unk_2021368 )
    {
      if ( __wtomb_environ() )
      {
LABEL_12:
        *_errno() = 22;
        return -1;
      }
    }
    else
    {
      if ( v22 )
        return 0;
      v7 = _malloc_crt(4u);
      unk_2021360 = v7;
      if ( !v7 )
        return -1;
      *v7 = 0;
      if ( !unk_2021368 )
      {
        v8 = _malloc_crt(4u);
        unk_2021368 = v8;
        if ( !v8 )
          return -1;
        *v8 = 0;
      }
    }
  }
  v9 = unk_2021360;
  v20 = (char *)unk_2021360;
  if ( !unk_2021360 )
    return -1;
  v10 = findenv(v5 - Block, Block);
  v11 = v10;
  if ( v10 < 0 || !*v9 )
  {
    if ( !v22 )
    {
      if ( v10 < 0 )
        v11 = -v10;
      if ( (int)(v11 + 2) <= (int)v11 )
        return -1;
      if ( v11 + 2 >= 0x3FFFFFFF )
        return -1;
      v13 = (char *)_recalloc_crt(unk_2021360, 4u, v11 + 2);
      if ( !v13 )
        return -1;
      v14 = (unsigned __int8 **)&v13[4 * v11];
      *v14 = Block;
      v14[1] = nullptr;
      *a1 = nullptr;
      goto LABEL_37;
    }
    free(Block);
    *a1 = nullptr;
    return 0;
  }
  v12 = (char *)&v9[v10];
  free(*(void **)v12);
  if ( !v22 )
  {
    *(_DWORD *)v12 = Block;
    *a1 = nullptr;
    goto LABEL_38;
  }
  while ( *(_DWORD *)v12 )
  {
    *(_DWORD *)v12 = *((_DWORD *)v12 + 1);
    ++v11;
    v12 = &v20[4 * v11];
  }
  if ( v11 >= 0x3FFFFFFF )
    goto LABEL_38;
  v13 = (char *)_recalloc_crt(unk_2021360, v11, 4u);
  if ( !v13 )
    goto LABEL_38;
LABEL_37:
  unk_2021360 = v13;
LABEL_38:
  if ( a2 )
  {
    v15 = strlen((const char *)Block);
    v16 = (char *)_calloc_crt(v15 + 2, 1u);
    if ( v16 )
    {
      v17 = strlen((const char *)Block);
      if ( strcpy_s(v16, v17 + 2, (const char *)Block) )
        _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
      v18 = &v19[v16 - (char *)Block];
      *v18 = 0;
      if ( !SetEnvironmentVariableA(v16, !v22 ? (LPCSTR)v18 + 1 : nullptr) )
      {
        v21 = -1;
        *_errno() = 42;
      }
      free(v16);
    }
  }
  if ( v22 )
  {
    free(Block);
    *a1 = nullptr;
  }
  return v21;
}

