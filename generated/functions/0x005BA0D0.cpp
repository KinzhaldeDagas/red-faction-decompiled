// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA0D0 rf_animation_clip_pool_get_or_create
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Copies requested name unbounded to60-byte local, removes LAST dot suffix, scans800 records at1D6DA28,stride124. Nonempty record names copied into another60-byte local, last suffix removed, compared _stricmp. First match returns existing record; otherwise remembers first name-empty slot. New slot: clears40 trigger bytes+64..103, size+104=0,raw pointer+120=0,registration count+112=0,instance reference count+116=0,ownership byte+108=0; copies ORIGINAL requested name unbounded, clears first byte of both trigger names. No guard for all800 occupied: dereferences NULL free-slot pointer. Empty requested name leaves slot apparently free; no file I/O or raw validation here. Registry strips last extension while raw-file loader strips first
// dot.
char *__cdecl rf_animation_clip_pool_get_or_create(char *a1)
{
  char v1; // al
  char v2; // al
  _DWORD *v4; // ecx
  char v5; // cl
  char *v6; // [esp+8h] [ebp-B8h]
  char *v7; // [esp+Ch] [ebp-B4h]
  char *v8; // [esp+18h] [ebp-A8h]
  char *v9; // [esp+1Ch] [ebp-A4h]
  char *v10; // [esp+28h] [ebp-98h]
  char *v11; // [esp+2Ch] [ebp-94h]
  int i; // [esp+30h] [ebp-90h]
  char String1[60]; // [esp+34h] [ebp-8Ch] BYREF
  char *v14; // [esp+70h] [ebp-50h]
  char String2[60]; // [esp+74h] [ebp-4Ch] BYREF
  char *last_char_wrapper; // [esp+B4h] [ebp-Ch]
  char *v17; // [esp+B8h] [ebp-8h]
  int v18; // [esp+BCh] [ebp-4h]

  v14 = nullptr;
  v11 = a1;
  v10 = String2;
  do
  {
    v1 = *v11;
    *v10++ = *v11++;
  }
  while ( v1 );
  last_char_wrapper = rf_cstring_find_last_char_wrapper(String2, 46);
  if ( last_char_wrapper )
    *last_char_wrapper = 0;
  v18 = 0;
  v17 = (char *)&unk_1D6DA28;
  while ( v18 < 800 )
  {
    if ( *v17 )
    {
      v9 = v17;
      v8 = String1;
      do
      {
        v2 = *v9;
        *v8++ = *v9++;
      }
      while ( v2 );
      last_char_wrapper = rf_cstring_find_last_char_wrapper(String1, 46);
      if ( last_char_wrapper )
        *last_char_wrapper = 0;
      if ( !_stricmp(String1, String2) )
        return v17;
    }
    else if ( !v14 )
    {
      v14 = v17;
    }
    ++v18;
    v17 += 124;
  }
  v17 = v14;
  v4 = v14 + 64;
  *((_DWORD *)v14 + 16) = 0;
  v4[1] = 0;
  v4[2] = 0;
  v4[3] = 0;
  v4[4] = 0;
  v4[5] = 0;
  v4[6] = 0;
  v4[7] = 0;
  v4[8] = 0;
  v4[9] = 0;
  *((_DWORD *)v17 + 30) = 0;
  *((_DWORD *)v17 + 26) = 0;
  *((_DWORD *)v17 + 28) = 0;
  *((_DWORD *)v17 + 29) = 0;
  v17[108] = 0;
  v7 = a1;
  v6 = v17;
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  for ( i = 0; i < 2; ++i )
    v17[20 * i + 64] = 0;
  return v17;
}

