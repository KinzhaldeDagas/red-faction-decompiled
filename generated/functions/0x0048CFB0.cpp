// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048CFB0 rf_banlist_export_text_file
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Builds path in zero-initialized512-byte stack buffer: directory from57B400(mode0),empty directory skips export; adds backslash if absent then literal banlist.txt using immediate stores. Opens text writer with append0/truncate and stdio buffer size4096. Iterates linked records from704C74 until sentinel704C5C using next pointer+24,writes each record string with format %s\n; writer normalizes newline toCRLF. Ignores each write status. Closes/reset handles then scalar deletes writer. No escaping/line validation or path capacity check; pointer arithmetic around v8 in pseudocode is stack-layout artifact. AL return incidental,not verified success boolean.
char rf_banlist_export_text_file()
{
  _DWORD *v0; // eax
  char v2; // [esp+Bh] [ebp-235h]
  _DWORD *v3; // [esp+Ch] [ebp-234h]
  char v4; // [esp+13h] [ebp-22Dh]
  _WORD *v5; // [esp+14h] [ebp-22Ch]
  char *p_FileName; // [esp+24h] [ebp-21Ch]
  void *v8; // [esp+2Ch] [ebp-214h] BYREF
  char FileName; // [esp+30h] [ebp-210h] BYREF
  _BYTE v10[511]; // [esp+31h] [ebp-20Fh] BYREF
  int v11; // [esp+234h] [ebp-Ch]
  int v12; // [esp+238h] [ebp-8h]
  char v13[4]; // [esp+23Ch] [ebp-4h]

  FileName = 0;
  memset(v10, 0, sizeof(v10));
  rf_vfile_copy_loose_directory_cstring_unbounded(0, &FileName);
  p_FileName = &FileName;
  do
    LOBYTE(v0) = *p_FileName;
  while ( *p_FileName++ );
  v11 = p_FileName - v10;
  if ( p_FileName - v10 > 0 )
  {
    if ( *((_BYTE *)&v8 + v11 + 3) != 92 )
    {
      v5 = (_WORD *)((char *)&v8 + 3);
      do
      {
        v4 = *((_BYTE *)v5 + 1);
        v5 = (_WORD *)((char *)v5 + 1);
      }
      while ( v4 );
      *v5 = 92;
    }
    v3 = (void **)((char *)&v8 + 3);
    do
    {
      v2 = *((_BYTE *)v3 + 1);
      v3 = (_DWORD *)((char *)v3 + 1);
    }
    while ( v2 );
    *v3 = 1819173218;
    v3[1] = 779383657;
    v3[2] = &unk_747874;
    v0 = rf_text_file_create_writer(&FileName, 0, 0x1000u);
    v12 = (int)v0;
    if ( v0 )
    {
      for ( *(_DWORD *)v13 = unk_704C74; *(_UNKNOWN **)v13 != &unk_704C5C; *(_DWORD *)v13 = *(_DWORD *)(*(_DWORD *)v13 + 24) )
        rf_text_file_printf((FILE **)v12, "%s\n", *(const char **)v13);
      rf_text_file_close_and_reset_handles(v12);
      LOBYTE(v0) = v12;
      v8 = (void *)v12;
      if ( v12 )
        LOBYTE(v0) = (unsigned __int8)rf_text_file_scalar_deleting_destructor(v8, 1);
    }
  }
  return (char)v0;
}

