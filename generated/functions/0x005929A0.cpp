// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005929A0 rf_vfile_resolve_open_source
// UNREALRED VERIFIED [vfile-loose-precedence] Unified VFile source resolver. Relative requests try a registered loose file first, then a VPP member, then alternate media roots.
// UNREALRED VERIFIED [streaming-contract-20260829] Special paths take the direct physical-path branch and return there; only relative requests reach registered-loose and VPP resolution.
char __thiscall rf_vfile_resolve_open_source(int this, char *String2, int a3)
{
  char v4; // [esp+7h] [ebp-69h]
  _BYTE *v5; // [esp+Ch] [ebp-64h]
  char *v6; // [esp+10h] [ebp-60h]
  char *v8; // [esp+18h] [ebp-58h]
  char v9; // [esp+1Fh] [ebp-51h]
  char *v10; // [esp+24h] [ebp-4Ch]
  char *v11; // [esp+28h] [ebp-48h]
  char v12; // [esp+2Fh] [ebp-41h]
  _BYTE *v13; // [esp+34h] [ebp-3Ch]
  char *v14; // [esp+38h] [ebp-38h]
  char v15; // [esp+3Fh] [ebp-31h]
  _BYTE *v16; // [esp+44h] [ebp-2Ch]
  char *v17; // [esp+48h] [ebp-28h]
  char registered_loose_file; // [esp+53h] [ebp-1Dh] BYREF
  char v20[16]; // [esp+54h] [ebp-1Ch] BYREF
  int i; // [esp+68h] [ebp-8h]
  char *last_char_wrapper; // [esp+6Ch] [ebp-4h]

  if ( !String2 || !*String2 )
    return 0;
  *(_DWORD *)(this + 264) = 0;
  *(_BYTE *)(this + 4) = 0;
  *(_BYTE *)(this + 268) = 0;
  if ( rf_vfile_is_special_path(String2) )
  {
    v17 = String2;
    v16 = (_BYTE *)(this + 5);
    do
    {
      v15 = *v17;
      *v16++ = *v17++;
    }
    while ( v15 );
    *(_DWORD *)this = -1;
    if ( rf_vfile_find_optical_volume_and_update_root_drive((int)&unk_98967E) >= 0
      && !_strnicmp((const char *)dword_1898C90, String2, 2u) )
    {
      *(_BYTE *)(this + 268) = 1;
    }
    if ( rf_vfile_try_direct_path((void *)this, (const char *)(this + 5), -1) )
    {
      *(_BYTE *)(this + 4) = 1;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v14 = String2;
    v13 = (_BYTE *)(this + 5);
    do
    {
      v12 = *v14;
      *v13++ = *v14++;
    }
    while ( v12 );
    _strlwr((char *)(this + 5));
    v20[0] = 0;
    last_char_wrapper = rf_cstring_find_last_char_wrapper((char *)(this + 5), 46);
    if ( last_char_wrapper )
    {
      v11 = last_char_wrapper;
      v10 = v20;
      do
      {
        v9 = *v11;
        *v10++ = *v11++;
      }
      while ( v9 );
      v8 = &registered_loose_file;
      while ( *++v8 )
        ;
      *(_WORD *)v8 = 32;
    }
    registered_loose_file = rf_vfile_find_registered_loose_file(String2, (_DWORD *)this);
    if ( registered_loose_file )
    {
      rf_vfile_build_loose_path(*(_DWORD *)this, String2, (char *)(this + 5));
      *(_BYTE *)(this + 4) = 1;
      return 1;
    }
    else if ( rf_vfile_find_vpp_member_and_store_pointer(String2, (_DWORD *)(this + 264)) )
    {
      v6 = String2;
      v5 = (_BYTE *)(this + 5);
      do
      {
        v4 = *v6;
        *v5++ = *v6++;
      }
      while ( v4 );
      *(_BYTE *)(this + 4) = 1;
      return 1;
    }
    else
    {
      for ( i = 0; i < 512; ++i )
      {
        if ( rf_vfile_is_valid_search_root_id(i)
          && rf_cstring_find_first_substring_case_insensitive((const char *)dword_1897494[3 * i], v20)
          && unk_1897498[12 * i]
          && rf_vfile_try_configured_optical_path((char *)this, String2, i) )
        {
          *(_BYTE *)(this + 4) = 1;
          return 1;
        }
      }
      for ( i = 0; i < 512; ++i )
      {
        if ( rf_vfile_is_valid_search_root_id(i)
          && rf_cstring_find_first_substring_case_insensitive((const char *)dword_1897494[3 * i], v20) )
        {
          *(_DWORD *)this = i;
          break;
        }
      }
      if ( i >= 512 )
        *(_DWORD *)this = 0;
      rf_vfile_build_loose_path(*(_DWORD *)this, String2, (char *)(this + 5));
      *(_BYTE *)(this + 268) = 0;
      return 0;
    }
  }
}

