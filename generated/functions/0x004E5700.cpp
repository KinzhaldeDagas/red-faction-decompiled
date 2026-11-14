// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E5700 rf_player_load_configuration_file
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl player. Only option record88E478 getter AL EXACT1 AND nonempty CString pointer88E488 select players_<argument>.cfg; otherwise players.cfg. Unbounded concatenation into260-byte filename; no profile/path validation. fopen rb, failure AL0. Require fread one33-byte header and header BYTE0 EXACT0x1B; name bytes1..32 not consulted. Wrong version closes and unlinks literal players.cfg EVEN WHEN a profile file was opened; returns0, ignores unlink result. Seek offset33 from start, rejecting only negative fseek result; read one1056-byte payload, then runtime-state restore(player,payload), apply render options5650, fclose, AL1. Any earlier short read/negative seek closes and returns0. No payload integrity/name termination validation or
// EOF/trailing-byte check; fclose result ignored.
char __cdecl rf_player_load_configuration_file(int a1)
{
  char *v3; // [esp+Ch] [ebp-580h]
  char *v5; // [esp+14h] [ebp-578h]
  unsigned int v6; // [esp+28h] [ebp-564h]
  unsigned int v7; // [esp+38h] [ebp-554h] BYREF
  char FileName[260]; // [esp+3Ch] [ebp-550h] BYREF
  _BYTE Buffer[36]; // [esp+140h] [ebp-44Ch] BYREF
  _BYTE v10[1056]; // [esp+164h] [ebp-428h] BYREF
  FILE *Stream; // [esp+588h] [ebp-4h]

  if ( rf_command_line_bool_option_is_enabled(unk_88E478) != 1
    || (v7 = unk_88E488 + strlen(unk_88E488) + 1, v7 == unk_88E488 + 1) )
  {
    Stream = fopen("players.cfg", "rb");
  }
  else
  {
    strcpy(FileName, "players_");
    v6 = unk_88E488 + strlen(unk_88E488) + 1;
    v5 = (char *)&v7 + 3;
    while ( *++v5 )
      ;
    qmemcpy(v5, unk_88E488, v6 - unk_88E488);
    v3 = (char *)&v7 + 3;
    while ( *++v3 )
      ;
    strcpy(v3, ".cfg");
    Stream = fopen(FileName, "rb");
  }
  if ( !Stream )
    return 0;
  if ( !fread(Buffer, 0x21u, 1u, Stream) )
    goto LABEL_17;
  if ( Buffer[0] != 27 )
  {
    fclose(Stream);
    _unlink("players.cfg");
    return 0;
  }
  if ( fseek(Stream, 33, 0) >= 0 && fread(v10, 0x420u, 1u, Stream) )
  {
    rf_player_runtime_state_restore(a1, (int)v10);
    rf_player_apply_loaded_render_options(a1);
    fclose(Stream);
    return 1;
  }
  else
  {
LABEL_17:
    fclose(Stream);
    return 0;
  }
}

