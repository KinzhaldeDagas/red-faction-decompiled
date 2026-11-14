// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA6F0 rf_developer_toggle_target_hidden
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Execute nonzero resolves debug target handle87C31C; nonNULL target with inactive predicate any nonzero calls reactivate-from-respawn, otherwise marks hidden/inactive. Independent help prints hide/unhide description. Does not merely toggle a render bit locally; delegates broader object-state helpers. No incoming references in current database.
void rf_developer_toggle_target_hidden()
{
  _DWORD *v0; // [esp+0h] [ebp-4h]

  if ( dword_1809818 )
  {
    v0 = (_DWORD *)rf_object_resolve_handle(dword_87C31C);
    if ( v0 )
    {
      if ( rf_object_has_respawn_inactive_flag((int)v0) )
        rf_object_reactivate_from_respawn(v0);
      else
        rf_object_mark_hidden_inactive((int)v0);
    }
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Hide current target (unhide if already hidden)\n", nullptr);
}

