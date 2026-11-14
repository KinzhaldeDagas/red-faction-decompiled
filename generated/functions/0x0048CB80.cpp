// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048CB80 rf_console_team_select
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl console handler. With execution flag1809818 nonzero,NULL local player returns immediately before help. Initializes local unsigned team byte0xFF,reads
// argument(mask2,0),ignores status. Nonempty argument performs case-insensitive SUBSTRING search for literal 'red' (original bytes63949C),then 'blue'; red wins if both. Red
// maps0,blue1; unrecognized nonempty returns before help. Empty argument leaves0xFF.
// IMPORTANT native MOVZX ECX,teamByte then CMP ECX,0xFFFFFFFF at48CC1B..22 can NEVER equal: intended unset guard is dead. Empty argument therefore continues with team255,unlike
// pseudocode's misleading unsigned-byte vs-1 check. Calls49ACC0 local suicide/death-request helper BEFORE changing/sending team. If mode!=1 OR authority ANY nonzero,writes local
// player BYTE48=team. Client(mode1,authority0) instead calls4B0F10(network player id at[player+4608]+20,team). Server(mode1,authority EXACT1) calls4B1060(id,team); other nonzero
// authority values write locally without broadcast. No network-stateNULL guard or local team-range validation after dead unset check.
// After non-returning execution path OR execution disabled,help flag1809814 prints localized Usage and literal '     team red','     team blue'. Does not require exact team token or
// restrict to team game mode in this body.
void rf_console_team_select()
{
  unsigned __int8 v0; // [esp+17h] [ebp-1h]

  if ( dword_1809818 )
  {
    if ( !rf_local_fpgun_player )
      return;
    v0 = -1;
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 != (char *)&unk_1809821 )
    {
      if ( rf_cstring_find_first_substring_case_insensitive(&MEMORY[0x1809820], (const char *)&off_63949C) )
      {
        v0 = 0;
      }
      else
      {
        if ( !rf_cstring_find_first_substring_case_insensitive(&MEMORY[0x1809820], "blue") )
          return;
        v0 = 1;
      }
    }
    if ( v0 != -1 )
    {
      sub_49ACC0();
      if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
        *(_BYTE *)(rf_local_fpgun_player + 48) = v0;
      if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
        rf_multiplayer_send_team_change_to_local_transport23(
          *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20),
          v0);
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
        rf_server_broadcast_team_change_packet23(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20), v0);
    }
  }
  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines(dword_88E210, nullptr);
    rf_console_output_append_text_lines("     team red", nullptr);
    rf_console_output_append_text_lines("     team blue", nullptr);
  }
}

