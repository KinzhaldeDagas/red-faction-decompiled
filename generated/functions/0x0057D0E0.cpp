// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D0E0 rf_path_change_directory_with_drive_status
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl path. Unbounded-copies into260-byte local and lowercases, saves current numeric drive. Finds FIRST colon anywhere; if present uses byte before colon minus96 as drive number (no letter/location validation and colon at start reads before buffer). Failed _chdrive returns1; successful drive selection uses suffix after colon as path, otherwise whole string. Empty path substituted literal backslash-dot6415C0. Successful _chdir returns0 and leaves process drive/directory changed. Failed _chdir calls drive adapter to restore saved drive (ignores restoration result), returns2; does not restore previous per-drive directory explicitly. No NULL, length or character-set validation.
int __cdecl rf_path_change_directory_with_drive_status(char *a1)
{
  char v2; // [esp+3h] [ebp-12Dh]
  char *v3; // [esp+8h] [ebp-128h]
  char v5[4]; // [esp+14h] [ebp-11Ch] BYREF
  char *Path; // [esp+1Ch] [ebp-114h]
  int v8; // [esp+20h] [ebp-110h]
  char *first_character; // [esp+24h] [ebp-10Ch]
  char String[260]; // [esp+28h] [ebp-108h] BYREF

  v3 = String;
  do
  {
    v2 = *a1;
    *v3++ = *a1++;
  }
  while ( v2 );
  _strlwr(String);
  v8 = _getdrive();
  first_character = rf_cstring_find_first_character(String, 58);
  if ( first_character )
  {
    if ( !rf_path_change_drive_bool(*(first_character - 1) - 96) )
      return 1;
    Path = first_character + 1;
  }
  else
  {
    Path = String;
  }
  strcpy(v5, "\\.");
  if ( !*Path )
    Path = v5;
  if ( !_chdir(Path) )
    return 0;
  rf_path_change_drive_bool(v8);
  return 2;
}

