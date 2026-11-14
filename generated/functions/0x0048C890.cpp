// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C890 rf_console_rcon_request
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl console handler. Execution flagDWORD1809818 nonzero requires multiplayer mode EXACT1,authority0; otherwise returns before help branch. Calls argument reader(mask2,0),ignores
// status,and measures argument Cstring1809820. Unsigned length<=16,including empty, invokes password packet builder48C070. Larger input formats localized error88E29C with16 to
// local260-byte buffer, prints and returns before usage. No independent parse-state or networking result check.
// When execution disabled OR valid send path completes, help flag1809814 nonzero prints localized Usage88E210 and '     rcon_request <%s>' with localized Password88DB3C,using
// local40-byte sprintf buffer without capacity. Does not install/change server password or grant authority itself. Return EAX incidental/last helper.
int rf_console_rcon_request()
{
  int result; // eax
  char v1[40]; // [esp+1Ch] [ebp-130h] BYREF
  char Buffer[260]; // [esp+44h] [ebp-108h] BYREF

  if ( !dword_1809818 )
  {
LABEL_8:
    if ( dword_1809814 )
    {
      rf_console_output_append_text_lines(dword_88E210, nullptr);
      sprintf(v1, "     rcon_request <%s>", unk_88DB3C);
      return rf_console_output_append_text_lines(v1, nullptr);
    }
    return result;
  }
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( (unsigned int)(&MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 - (char *)&unk_1809821) > 0x10 )
    {
      sprintf(Buffer, unk_88E29C, 16);
      return rf_console_output_append_text_lines(Buffer, nullptr);
    }
    result = rf_rcon_request_password_packet(&MEMORY[0x1809820]);
    goto LABEL_8;
  }
  return result;
}

