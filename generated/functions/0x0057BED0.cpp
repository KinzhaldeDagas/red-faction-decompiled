// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057BED0 rf_vfile_register_loose_search_root
// UNREALRED VERIFIED [loose-root-registration] Normalizes one root and extension mask, stores its metadata, and immediately enumerates matching direct files into the loose lookup table.
int __cdecl rf_vfile_register_loose_search_root(char *a1, char *a2, char a3)
{
  char v4; // [esp+7h] [ebp-27Dh]
  char *v5; // [esp+Ch] [ebp-278h]
  char *v6; // [esp+10h] [ebp-274h]
  char v7; // [esp+27h] [ebp-25Dh]
  _WORD *v8; // [esp+28h] [ebp-25Ch]
  char v9; // [esp+3Fh] [ebp-245h]
  char *v10; // [esp+44h] [ebp-240h]
  char *v11; // [esp+48h] [ebp-23Ch]
  char v12; // [esp+4Fh] [ebp-235h]
  char *p_String2; // [esp+54h] [ebp-230h]
  size_t Count; // [esp+5Ch] [ebp-228h]
  char *v16; // [esp+60h] [ebp-224h]
  char Destination[8]; // [esp+64h] [ebp-220h] BYREF
  char *Str; // [esp+6Ch] [ebp-218h]
  int v19; // [esp+70h] [ebp-214h]
  char String2; // [esp+74h] [ebp-210h] BYREF
  _BYTE v21[3]; // [esp+75h] [ebp-20Fh] BYREF
  int v22; // [esp+174h] [ebp-110h]
  int i; // [esp+178h] [ebp-10Ch] BYREF
  char v24; // [esp+17Ch] [ebp-108h] BYREF
  _BYTE v25[3]; // [esp+17Dh] [ebp-107h] BYREF

  v19 = -1;
  p_String2 = &String2;
  do
  {
    v12 = *a1;
    *p_String2++ = *a1++;
  }
  while ( v12 );
  v11 = a2;
  v10 = &v24;
  do
  {
    v9 = *v11;
    *v10++ = *v11++;
  }
  while ( v9 );
  rf_cstring_lowercase_in_place(&String2);
  rf_cstring_lowercase_in_place(&v24);
  if ( &v25[strlen(&v24)] != v25 )
  {
    v8 = (_WORD *)((char *)&i + 3);
    do
    {
      v7 = *((_BYTE *)v8 + 1);
      v8 = (_WORD *)((char *)v8 + 1);
    }
    while ( v7 );
    *v8 = 32;
  }
  rf_path_convert_forward_slashes_to_backslashes_in_place(&String2);
  v22 = &v21[strlen(&String2)] - v21;
  if ( v22 > 0 )
  {
    for ( i = 1; ; ++i )
    {
      if ( i >= 512 )
      {
        if ( v19 < 0 )
          return -1;
        dword_1897490[3 * v19] = (int)rf_string_pool_intern_case_insensitive((char **)&unk_189CE9C, &String2);
        dword_1897494[3 * v19] = (int)rf_string_pool_intern_case_insensitive((char **)&unk_189CE9C, &v24);
        unk_1897498[12 * v19] = a3;
        rf_vfile_enumerate_registered_loose_files(v19);
        return v19;
      }
      if ( !dword_1897490[3 * i] && v19 < 0 )
        v19 = i;
      if ( dword_1897490[3 * i] && !_stricmp((const char *)dword_1897490[3 * i], &String2) )
        break;
    }
    Str = a2;
    while ( Str )
    {
      v16 = strstr(Str, " .");
      if ( v16 )
      {
        Count = v16 - Str;
        strncpy(Destination, Str, v16 - Str);
        Destination[Count] = 0;
        Str = v16 + 1;
      }
      else
      {
        v6 = Str;
        v5 = Destination;
        do
        {
          v4 = *v6;
          *v5++ = *v6++;
        }
        while ( v4 );
        Str = nullptr;
      }
      rf_cstring_find_first_substring_case_insensitive((const char *)dword_1897494[3 * i], Destination);
    }
    return i;
  }
  else
  {
    dword_1897494[0] = rf_string_pool_copy_c_string(&unk_189CE9C, &v24);
    unk_1897498[0] = a3;
    rf_vfile_enumerate_registered_loose_files(0);
    unk_18BCFB0 = 1;
    return 0;
  }
}

