// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048CA10 rf_console_rcon_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl console handler. Nonzero execution flag1809818 requires multiplayer1,authority0; otherwise skips help and returns. If raw command remainder pointer1809810 nonnull, computes
// strlen into signed int, permits inclusive0..256 and calls command packet builder48C4C0. Out-of-range returns before help. After send, repeatedly calls argument reader(-1,0) until
// parser flagsDWORD1809308 mask0x1 set; no network-response wait or timeout in this loop. Null remainder goes directly to help branch.
// Execution disabled or accepted/null-remainder execution then prints optional help1809814: localized Usage and sprintf '     rcon kick <%s>' / '     rcon level <%s>' with localized
// labels88E144/88E298 into local40-byte buffer. No local command authorization/result processing; packet helper only builds/queues. Return register incidental.
int rf_console_rcon_command()
{
  int result; // eax
  char Buffer[40]; // [esp+1Ch] [ebp-30h] BYREF
  int v2; // [esp+48h] [ebp-4h]

  if ( !dword_1809818 )
    goto LABEL_12;
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    if ( unk_1809810 )
    {
      result = strlen((const char *)unk_1809810);
      v2 = result;
      if ( result < 0 || v2 > 256 )
        return result;
      rf_rcon_command_packet((const char *)unk_1809810);
      while ( 1 )
      {
        result = dword_1809308 & 1;
        if ( (dword_1809308 & 1) != 0 )
          break;
        rf_console_read_argument_validate_type_mask(-1, 0);
      }
    }
LABEL_12:
    if ( dword_1809814 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      sprintf(Buffer, "     rcon kick <%s>", unk_88E144);
      rf_console_output_append_text_lines(Buffer, nullptr);
      sprintf(Buffer, "     rcon level <%s>", dword_88E298);
      return rf_console_output_append_text_lines(Buffer, nullptr);
    }
  }
  return result;
}

