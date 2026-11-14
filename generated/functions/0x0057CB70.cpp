// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057CB70 rf_vfile_collect_root_extension_lists_with_empty_splice_quirk
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl two-DWORD output sentinel and directory-prefix string. Initializes output circular list, loops root ids0..511 but BREAKS at first invalid id57B800, so registration holes suppress later roots. Builds directory57B400 into256-byte scratch and compares first strlen(prefix) bytes case-insensitively; no directory-boundary requirement, empty prefix matches all reached roots. For matching roots parses extension mask as fixed4-byte tokens at offsets0,5,10,... with explicit fifth-byteNUL, builds *token, and calls57C880 with flags4 (keep extension, enumeration order) and no callback. Unconditionally splices returned sublist via its stack-local sentinel: EMPTY child list therefore inserts stack
// sentinel into output and leaves dangling/corrupt links after return; no empty/head-count test. No global sorting, deduplication, extension grammar validation or prior-output cleanup. AL return is incidental comparison/length/validity residue, not count or reliable success.
char __cdecl rf_vfile_collect_root_extension_lists_with_empty_splice_quirk(
        void *out_head,
        const char *directory_prefix)
{
  int v2; // eax
  char *v3; // eax
  size_t v5; // [esp-4h] [ebp-1ACh]
  const char *v6; // [esp+10h] [ebp-198h]
  const char *v7; // [esp+14h] [ebp-194h]
  unsigned int v8; // [esp+14h] [ebp-194h]
  char *v10; // [esp+1Ch] [ebp-18Ch]
  _BYTE *v11; // [esp+30h] [ebp-178h]
  _BYTE *v12; // [esp+40h] [ebp-168h]
  const char *v13; // [esp+50h] [ebp-158h] BYREF
  __int16 v14; // [esp+54h] [ebp-154h] BYREF
  int v15; // [esp+56h] [ebp-152h]
  __int16 v16; // [esp+5Ah] [ebp-14Eh]
  char Destination; // [esp+5Ch] [ebp-14Ch] BYREF
  _BYTE v18[3]; // [esp+5Dh] [ebp-14Bh] BYREF
  char j; // [esp+60h] [ebp-148h]
  signed int v20; // [esp+64h] [ebp-144h]
  char v21[256]; // [esp+68h] [ebp-140h] BYREF
  int i; // [esp+168h] [ebp-40h]
  const char *v23; // [esp+16Ch] [ebp-3Ch] BYREF
  void **v24; // [esp+170h] [ebp-38h]

  *(_DWORD *)out_head = out_head;
  LOBYTE(v2) = (_BYTE)out_head;
  *((_DWORD *)out_head + 1) = out_head;
  for ( i = 0; i < 512; ++i )
  {
    LOBYTE(v2) = rf_vfile_is_valid_search_root_id(i);
    if ( !(_BYTE)v2 )
      break;
    v13 = directory_prefix;
    v13 += strlen(v13);
    v5 = ++v13 - (directory_prefix + 1);
    v3 = rf_vfile_copy_loose_directory_cstring_unbounded(i, v21);
    v2 = _strnicmp(v3, directory_prefix, v5);
    if ( !v2 )
    {
      v20 = 0;
      strncpy(&Destination, (const char *)dword_1897494[3 * i], 4u);
      for ( j = 0; ; j = 0 )
      {
        v12 = &v18[strlen(&Destination)];
        LOBYTE(v2) = (_BYTE)v12 - (unsigned __int8)v18;
        if ( v12 == v18 )
          break;
        v14 = 42;
        v15 = 0;
        v16 = 0;
        v11 = &v18[strlen(&Destination)];
        v10 = (char *)&v13 + 3;
        while ( *++v10 )
          ;
        qmemcpy(v10, &Destination, v11 - &Destination);
        rf_enumerate_files_sorted(&v23, i, (const char *)&v14, 4, nullptr);
        **((_DWORD **)out_head + 1) = v23;
        *((_DWORD *)v23 + 1) = *((_DWORD *)out_head + 1);
        *((_DWORD *)out_head + 1) = v24;
        *v24 = out_head;
        v20 += 5;
        v7 = (const char *)dword_1897494[3 * i];
        v6 = v7 + 1;
        v8 = (unsigned int)&v7[strlen(v7) + 1];
        LOBYTE(v2) = v8 - (_BYTE)v6;
        if ( v20 >= (int)(v8 - (_DWORD)v6) )
          break;
        strncpy(&Destination, (const char *)(v20 + dword_1897494[3 * i]), 4u);
      }
    }
  }
  return v2;
}

