// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6A30 rf_quicksave_execute
// UNREALRED VERIFIED [save-validation-20261028]: Builds configured save-directory + quicksav.svl in260-byte local using uncapped copies, calls rf_savegame_write_file_for_player with local player, sets notification float0x894D30=1.0 regardless of write result, returns write result.
char rf_quicksave_execute()
{
  char result; // al
  char *v2; // [esp+8h] [ebp-11Ch]
  CHAR v3; // [esp+Fh] [ebp-115h]
  CHAR *v4; // [esp+14h] [ebp-110h]
  CHAR *v5; // [esp+18h] [ebp-10Ch] BYREF
  CHAR FileName[260]; // [esp+1Ch] [ebp-108h] BYREF

  v5 = MEMORY[0x88E7D0];
  v4 = FileName;
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  v2 = (char *)&v5 + 3;
  while ( *++v2 )
    ;
  strcpy(v2, "quicksav.svl");
  result = rf_savegame_write_file_for_player(FileName, rf_local_fpgun_player);
  unk_894D30 = 1.0;
  return result;
}

