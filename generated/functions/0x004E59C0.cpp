// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E59C0 rf_player_save_configuration_file
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl player. Filename selection same option AL==1/nonempty argument rule as5700, unbounded players_<argument>.cfg or default players.cfg. First fopen r+b. On NULL consult WIN32 GetLastError (not errno); only EXACT2 permits retry w+b using freshly recomputed filename. Existing file: read one33-byte header WITHOUT checking version or ensuring name termination. New file: zero all33 bytes, set BYTE0=0x1B, immediately fwrite header. Compare player RFString+8 with header name+1 case-insensitively; only difference seeks0 and rewrites name/header. For actual name length>=32 use inclusive substring0..30 (31 bytes), otherwise full name; strcpy-like copy preserves header tail beyond new NUL and existing version byte. Temporary RFStrings
// destroyed normally/SEH. Case-only name changes do not rewrite header, though payload snapshot can differ. Seek33 (only negative rejected), snapshot runtime1056 bytes, fwrite one full record, fclose, AL1. Open/read/write/negative-seek failure AL0 with close when open. Ignores close errors; no atomic rename, truncate of old tail, payload/header consistency check or version repair on existing files.
char __cdecl rf_player_save_configuration_file(int a1)
{
  const char *v2; // eax
  char v3; // [esp+Fh] [ebp-709h]
  char *v4; // [esp+14h] [ebp-704h]
  const char *v5; // [esp+18h] [ebp-700h]
  _DWORD *v6; // [esp+1Ch] [ebp-6FCh]
  void *v7; // [esp+24h] [ebp-6F4h]
  char *v9; // [esp+2Ch] [ebp-6ECh]
  char *v11; // [esp+34h] [ebp-6E4h]
  unsigned int v12; // [esp+48h] [ebp-6D0h]
  char *v14; // [esp+60h] [ebp-6B8h]
  char *v16; // [esp+68h] [ebp-6B0h]
  unsigned int v17; // [esp+7Ch] [ebp-69Ch]
  char v18; // [esp+90h] [ebp-688h]
  void *v19[3]; // [esp+98h] [ebp-680h] BYREF
  int v20; // [esp+A4h] [ebp-674h] BYREF
  char v21; // [esp+ABh] [ebp-66Dh] BYREF
  char v22[260]; // [esp+ACh] [ebp-66Ch] BYREF
  DWORD LastError; // [esp+1B0h] [ebp-568h] BYREF
  char FileName[260]; // [esp+1B4h] [ebp-564h] BYREF
  _DWORD Buffer[8]; // [esp+2B8h] [ebp-460h] BYREF
  char v26; // [esp+2D8h] [ebp-440h]
  _BYTE v27[1060]; // [esp+2DCh] [ebp-43Ch] BYREF
  FILE *Stream; // [esp+704h] [ebp-14h]
  char v29; // [esp+70Bh] [ebp-Dh]
  int v30; // [esp+714h] [ebp-4h]

  v18 = 0;
  v29 = 1;
  if ( rf_command_line_bool_option_is_enabled(unk_88E478) == 1 && strlen(unk_88E488) )
  {
    strcpy(FileName, "players_");
    v17 = unk_88E488 + strlen(unk_88E488) + 1;
    v16 = (char *)&LastError + 3;
    while ( *++v16 )
      ;
    qmemcpy(v16, unk_88E488, v17 - unk_88E488);
    v14 = (char *)&LastError + 3;
    while ( *++v14 )
      ;
    strcpy(v14, ".cfg");
    Stream = fopen(FileName, off_63CAD8);
  }
  else
  {
    Stream = fopen("players.cfg", off_63CADC);
  }
  if ( !Stream )
  {
    LastError = GetLastError();
    if ( LastError != 2 )
      return 0;
    v29 = 0;
    if ( rf_command_line_bool_option_is_enabled(unk_88E478) == 1 && strlen(unk_88E488) )
    {
      strcpy(v22, "players_");
      v12 = unk_88E488 + strlen(unk_88E488) + 1;
      v11 = &v21;
      while ( *++v11 )
        ;
      qmemcpy(v11, unk_88E488, v12 - unk_88E488);
      v9 = &v21;
      while ( *++v9 )
        ;
      strcpy(v9, ".cfg");
      Stream = fopen(v22, off_63CB00);
    }
    else
    {
      Stream = fopen("players.cfg", off_63CB04);
    }
    if ( !Stream )
      return 0;
  }
  if ( v29 == 1 )
  {
    if ( !fread(Buffer, 0x21u, 1u, Stream) )
      goto LABEL_29;
  }
  else
  {
    Buffer[0] = 27;
    memset(&Buffer[1], 0, 28);
    v26 = 0;
    if ( !fwrite(Buffer, 0x21u, 1u, Stream) )
      goto LABEL_29;
  }
  v2 = rf_string_object_c_str_or_empty((const void *)(a1 + 8));
  if ( _stricmp(v2, (const char *)Buffer + 1) )
  {
    if ( fseek(Stream, 0, 0) < 0 )
    {
LABEL_29:
      fclose(Stream);
      return 0;
    }
    if ( (int)rf_string_length_from_cstr((const char **)(a1 + 8)) >= 32 )
    {
      v6 = rf_string_substring_inclusive((_DWORD *)(a1 + 8), v19, 0, 30);
      v30 = 0;
      v18 = 1;
      v7 = v6;
    }
    else
    {
      v7 = (void *)(a1 + 8);
    }
    v19[2] = v7;
    rf_string_copy_construct_from_object(&v20, (char **)v7);
    v30 = 2;
    if ( (v18 & 1) != 0 )
      rf_string_destroy_buffer(v19);
    v5 = rf_string_object_c_str_or_empty(&v20);
    v4 = (char *)Buffer + 1;
    do
    {
      v3 = *v5;
      *v4++ = *v5++;
    }
    while ( v3 );
    if ( !fwrite(Buffer, 0x21u, 1u, Stream) )
    {
      fclose(Stream);
      v30 = -1;
      rf_string_destroy_buffer(&v20);
      return 0;
    }
    v30 = -1;
    rf_string_destroy_buffer(&v20);
  }
  if ( fseek(Stream, 33, 0) >= 0 && (rf_player_runtime_state_snapshot(a1, (int)v27), fwrite(v27, 0x420u, 1u, Stream)) )
  {
    fclose(Stream);
    return 1;
  }
  else
  {
    fclose(Stream);
    return 0;
  }
}

