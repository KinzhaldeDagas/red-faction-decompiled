// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA940 rf_developer_set_selected_weapon_ammo
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Execute nonzero requires global entity681E38 nonNULL and selected weapon676 !=EXACTLY-1; missing entity/weapon returns before help. Reads required integer mask8,optional flag0. Parsed integer180981C>=0 writes entity reserve DWORD684+4*weapon-record DWORD36 (1360-byte stride); negative input leaves reserve unchanged. No selected-weapon/ammo-class bounds check, cap, inventory grant or infinite-ammo flag. Help prints Usage: set_ammo <N> when reached. Incidental EAX return; no incoming references in current database.
int rf_developer_set_selected_weapon_ammo()
{
  int result; // eax

  if ( !dword_1809818 )
  {
LABEL_6:
    if ( dword_1809814 )
      return rf_console_output_append_text_lines("Usage: set_ammo <N>\n", nullptr);
    return result;
  }
  if ( dword_681E38 )
  {
    result = dword_681E38;
    if ( *(_DWORD *)(dword_681E38 + 676) != -1 )
    {
      result = rf_console_read_argument_validate_type_mask(8, 0);
      if ( dword_180981C >= 0 )
      {
        result = dword_681E38;
        *(_DWORD *)(dword_681E38 + 4 * dword_912024[340 * *(_DWORD *)(dword_681E38 + 676)] + 684) = dword_180981C;
      }
      goto LABEL_6;
    }
  }
  return result;
}

