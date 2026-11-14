// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F3320 rf_savegame_initialize_path_and_ponr
// UNREALRED VERIFIED [save-validation-20261028]: Copies string0x189CD90 into configured save-directory buffer pointed to by0x88E7D0; appends savegame and backslash+NUL. Clears byte0x890400, clears level-state cache and returns PONR table parser result. Copies have no destination-capacity checks in this body.
char rf_savegame_initialize_path_and_ponr()
{
  char v0; // cl
  CHAR *v2; // [esp+1Ch] [ebp-8h]
  char *v3; // [esp+20h] [ebp-4h]

  v3 = &unk_189CD90;
  v2 = MEMORY[0x88E7D0];
  do
  {
    v0 = *v3;
    *v2++ = *v3++;
  }
  while ( v0 );
  strcat(MEMORY[0x88E7D0], "savegame");
  *(_WORD *)&MEMORY[0x88E7D0][strlen(MEMORY[0x88E7D0])] = 92;
  unk_890400 = 0;
  rf_level_state_cache_clear();
  return rf_savegame_parse_ponr_table();
}

