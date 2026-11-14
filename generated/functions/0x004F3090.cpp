// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F3090 rf_savegame_request_startup_load
// UNREALRED VERIFIED [save-validation-20261028]: When global0x1809818 is set, calls0x56F950(2,0); if startup save-name0x1809820 is nonempty, concatenates configured save directory and name into260-byte local. Validates headers and obtains level name, then calls0x4798E0 with constructed level/path strings and requests immediate panel5.
void rf_savegame_request_startup_load()
{
  int v0; // eax
  int v1; // eax
  int v2[2]; // [esp-10h] [ebp-1B0h] BYREF
  int v3[8]; // [esp-8h] [ebp-1A8h] BYREF
  char *v5; // [esp+1Ch] [ebp-184h]
  unsigned int v6; // [esp+20h] [ebp-180h]
  char *v7; // [esp+24h] [ebp-17Ch]
  char *v8; // [esp+2Ch] [ebp-174h]
  char *v9; // [esp+30h] [ebp-170h]
  CHAR v10; // [esp+37h] [ebp-169h]
  char *v11; // [esp+38h] [ebp-168h]
  char *v12; // [esp+3Ch] [ebp-164h]
  CHAR *v13; // [esp+40h] [ebp-160h]
  int v14; // [esp+44h] [ebp-15Ch]
  void *v15; // [esp+4Ch] [ebp-154h]
  char *v16; // [esp+50h] [ebp-150h]
  int *v17; // [esp+54h] [ebp-14Ch]
  void *v18; // [esp+58h] [ebp-148h]
  char *v19[2]; // [esp+5Ch] [ebp-144h] BYREF
  char *v20; // [esp+64h] [ebp-13Ch] BYREF
  char v21; // [esp+6Bh] [ebp-135h] BYREF
  char FileName[260]; // [esp+6Ch] [ebp-134h] BYREF
  char Source[32]; // [esp+170h] [ebp-30h] BYREF
  int v24; // [esp+19Ch] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    v15 = &unk_1809821;
    v16 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1;
    v14 = v16 - (char *)&unk_1809821;
    if ( v16 != (char *)&unk_1809821 )
    {
      v13 = MEMORY[0x88E7D0];
      v12 = FileName;
      v11 = FileName;
      do
      {
        v10 = *v13;
        *v12 = v10;
        ++v13;
        ++v12;
      }
      while ( v10 );
      v8 = &MEMORY[0x1809820];
      v9 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1;
      v7 = &MEMORY[0x1809820];
      v6 = v9 - &MEMORY[0x1809820];
      v5 = &v21;
      while ( *++v5 )
        ;
      qmemcpy(v5, v7, v6);
      if ( rf_savegame_validate_headers_and_read_info(FileName, Source, nullptr, nullptr) )
      {
        rf_string_construct_from_cstr(v19, Source);
        v24 = 0;
        rf_string_construct_from_cstr(&v20, FileName);
        LOBYTE(v24) = 1;
        v18 = v3;
        rf_string_copy_construct_from_object(v3, &v20);
        v3[7] = v0;
        v3[6] = v0;
        LOBYTE(v24) = 2;
        v17 = v2;
        rf_string_copy_construct_from_object(v2, v19);
        v3[5] = v1;
        LOBYTE(v24) = 1;
        rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
        rf_ui_request_panel_immediate(5, 0);
        LOBYTE(v24) = 0;
        rf_string_destroy_buffer(&v20);
        v24 = -1;
        rf_string_destroy_buffer(v19);
      }
    }
  }
}

