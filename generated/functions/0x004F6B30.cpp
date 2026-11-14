// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6B30 rf_quickload_request_level_transition
// UNREALRED VERIFIED [save-validation-20261028]: Constructs configured save-directory + quicksav.svl in260-byte local. Header validator supplies level name; only on success constructs level/path strings, calls0x4798E0 and requests immediate panel5. Does not restore snapshot synchronously or clear pending flag here.
void rf_quickload_request_level_transition()
{
  char *v0; // edi
  int v1; // eax
  int v2; // eax
  int v3[2]; // [esp-10h] [ebp-188h] BYREF
  int v4[7]; // [esp-8h] [ebp-180h] BYREF
  char *v6; // [esp+18h] [ebp-160h]
  CHAR v7; // [esp+1Fh] [ebp-159h]
  char *v8; // [esp+20h] [ebp-158h]
  char *v9; // [esp+24h] [ebp-154h]
  CHAR *v10; // [esp+28h] [ebp-150h]
  int *v11; // [esp+2Ch] [ebp-14Ch]
  void *v12; // [esp+30h] [ebp-148h]
  char *v13[2]; // [esp+34h] [ebp-144h] BYREF
  char *v14; // [esp+3Ch] [ebp-13Ch] BYREF
  char v15; // [esp+43h] [ebp-135h] BYREF
  char FileName[260]; // [esp+44h] [ebp-134h] BYREF
  char Source[32]; // [esp+148h] [ebp-30h] BYREF
  int v18; // [esp+174h] [ebp-4h]

  v10 = MEMORY[0x88E7D0];
  v9 = FileName;
  v8 = FileName;
  do
  {
    v7 = *v10;
    *v9 = v7;
    ++v10;
    ++v9;
  }
  while ( v7 );
  v6 = &v15;
  while ( *++v6 )
    ;
  v0 = v6;
  *(_DWORD *)v6 = 1667855729;
  strcpy(v0 + 4, "ksav.svl");
  if ( rf_savegame_validate_headers_and_read_info(FileName, Source, nullptr, nullptr) )
  {
    rf_string_construct_from_cstr(v13, Source);
    v18 = 0;
    rf_string_construct_from_cstr(&v14, FileName);
    LOBYTE(v18) = 1;
    v12 = v4;
    rf_string_copy_construct_from_object(v4, &v14);
    v4[6] = v1;
    v4[5] = v1;
    LOBYTE(v18) = 2;
    v11 = v3;
    rf_string_copy_construct_from_object(v3, v13);
    v4[4] = v2;
    LOBYTE(v18) = 1;
    rf_level_transition_assign_level_and_save_strings(v3[0], (char *)v3[1], v4[0], (char *)v4[1]);
    rf_ui_request_panel_immediate(5, 0);
    LOBYTE(v18) = 0;
    rf_string_destroy_buffer(&v14);
    v18 = -1;
    rf_string_destroy_buffer(v13);
  }
}

