// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F35B0 rf_savegame_validate_headers_and_read_info
// UNREALRED VERIFIED [save-validation-20261028]: Arguments: filename, optional level-name output, optional float output, optional title output. Reads83544-byte header; requires size83544, tag0x10009, signed selected index<=4 and nonzero count. No explicit selected>=0, selected<count, or count<=4 test. For each signed loop index<count, seeks83544+100128*i and reads only64 bytes; requires block size100128 and case-insensitive name membership in header names; selected block must also match corresponding slot. Does not validate full snapshot payload. Level/title are uncapped C-string copies written before block validation, so failure may leave outputs changed. Success copies float at header+192, selected level name at+12+32*index, title at+140; returns1, otherwise0.
char __cdecl rf_savegame_validate_headers_and_read_info(char *FileName, _BYTE *a2, float *a3, _BYTE *a4)
{
  char v5; // [esp+7h] [ebp-C5h]
  _BYTE *v6; // [esp+Ch] [ebp-C0h]
  char *v7; // [esp+10h] [ebp-BCh]
  char v8; // [esp+17h] [ebp-B5h]
  _BYTE *v9; // [esp+1Ch] [ebp-B0h]
  char *v10; // [esp+20h] [ebp-ACh]
  char v11; // [esp+27h] [ebp-A5h]
  _BYTE *v12; // [esp+2Ch] [ebp-A0h]
  char *v13; // [esp+30h] [ebp-9Ch]
  char *v14; // [esp+34h] [ebp-98h]
  char *v15; // [esp+54h] [ebp-78h]
  int j; // [esp+5Ch] [ebp-70h]
  char v17; // [esp+63h] [ebp-69h]
  int Offset; // [esp+64h] [ebp-68h]
  char String2[32]; // [esp+68h] [ebp-64h] BYREF
  int v20; // [esp+88h] [ebp-44h]
  void *v21; // [esp+B0h] [ebp-1Ch] BYREF
  void *Buffer; // [esp+B4h] [ebp-18h]
  int i; // [esp+B8h] [ebp-14h]
  FILE *Stream; // [esp+BCh] [ebp-10h]
  int v25; // [esp+C8h] [ebp-4h]

  if ( !FileName || !strlen(FileName) )
    return 0;
  v15 = (char *)operator new(0x14658u);
  v25 = 0;
  if ( v15 )
    v14 = rf_savegame_header_construct_subobjects(v15);
  else
    v14 = nullptr;
  v25 = -1;
  rf_scene_key_set_first_dword(&v21, (int)v14);
  v25 = 1;
  Buffer = (void *)rf_receiver_get_first_dword(&v21);
  Stream = fopen(FileName, "rb");
  if ( Stream )
  {
    if ( fread(Buffer, 0x14658u, 1u, Stream)
      && *(_DWORD *)Buffer == 83544
      && *((_DWORD *)Buffer + 1) == 65545
      && *((int *)Buffer + 47) <= 4
      && *((_DWORD *)Buffer + 2) )
    {
      if ( a2 )
      {
        v13 = (char *)Buffer + 32 * *((_DWORD *)Buffer + 47) + 12;
        v12 = a2;
        do
        {
          v11 = *v13;
          *v12++ = *v13++;
        }
        while ( v11 );
      }
      if ( a4 )
      {
        v10 = (char *)Buffer + 140;
        v9 = a4;
        do
        {
          v8 = *v10;
          *v9++ = *v10++;
        }
        while ( v8 );
      }
      for ( i = 0; i < *((_DWORD *)Buffer + 2); ++i )
      {
        Offset = 100128 * i + 83544;
        rf_level_snapshot_bounds_construct((int)String2);
        v17 = 0;
        if ( fseek(Stream, Offset, 0) < 0 || !fread(String2, 0x40u, 1u, Stream) || v20 != 100128 )
          goto LABEL_34;
        for ( j = 0; j < *((_DWORD *)Buffer + 2); ++j )
        {
          if ( !_stricmp((const char *)Buffer + 32 * j + 12, String2) )
          {
            v17 = 1;
            break;
          }
        }
        if ( !v17 || i == *((_DWORD *)Buffer + 47) && _stricmp(String2, (const char *)Buffer + 32 * i + 12) )
        {
LABEL_34:
          fclose(Stream);
          v25 = -1;
          rf_snapshot_owned_buffer_delete(&v21);
          return 0;
        }
      }
      if ( a3 )
        *a3 = *((float *)Buffer + 48);
      fclose(Stream);
      if ( a2 )
      {
        v7 = (char *)Buffer + 32 * *((_DWORD *)Buffer + 47) + 12;
        v6 = a2;
        do
        {
          v5 = *v7;
          *v6++ = *v7++;
        }
        while ( v5 );
      }
      v25 = -1;
      rf_snapshot_owned_buffer_delete(&v21);
      return 1;
    }
    else
    {
      fclose(Stream);
      v25 = -1;
      rf_snapshot_owned_buffer_delete(&v21);
      return 0;
    }
  }
  else
  {
    v25 = -1;
    rf_snapshot_owned_buffer_delete(&v21);
    return 0;
  }
}

