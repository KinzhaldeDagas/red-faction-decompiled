// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA580 rf_developer_toggle_invulnerability
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Execute1809818 nonzero AND global entity681E38 nonNULL reads optional mask9 argument. Parsed type flags1809308 mask8 present: parsed integer180981C nonzero sets entity DWORD124 mask4, zero clears; otherwise XOR toggles mask4. Prints invulnerable/mortal message from resulting bit. Independent help1809814 prints help even when action skipped. EAX is output/helper residue, not uniform status. No own multiplayer/authority guard; no incoming references in current database.
int rf_developer_toggle_invulnerability()
{
  unsigned int v0; // edx
  int result; // eax

  if ( dword_1809818 && dword_681E38 )
  {
    rf_console_read_argument_validate_type_mask(9, 0);
    if ( (dword_1809308 & 8) != 0 )
    {
      if ( dword_180981C )
        v0 = *(_DWORD *)(dword_681E38 + 124) | 4;
      else
        v0 = *(_DWORD *)(dword_681E38 + 124) & 0xFFFFFFFB;
      *(_DWORD *)(dword_681E38 + 124) = v0;
    }
    else
    {
      *(_DWORD *)(dword_681E38 + 124) ^= 4u;
    }
    if ( (*(_DWORD *)(dword_681E38 + 124) & 4) != 0 )
      result = rf_console_output_append_text_lines("You are invulnerable\n", nullptr);
    else
      result = rf_console_output_append_text_lines("You are mortal again\n", nullptr);
  }
  if ( dword_1809814 )
    return rf_console_output_append_text_lines("Make self invulnerable\n", nullptr);
  return result;
}

