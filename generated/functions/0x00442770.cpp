// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442770 rf_level_finalize_trigger_and_mover_links
// UNREALRED VERIFIED [mission-mover-world-20261013] World finalization stops global sound voices, commits flag8 triggers, then calls mover child binding0x48AC40. Only afterward applies L20S2 trigger18344 reverse-disable special case and a final helper. Binding is a post-creation ownership pass; it does not instantiate geometry from editor member placements.
// UNREALRED VERIFIED [mission-startup-20261020] New-level finalization commits startup flag8 triggers BEFORE binding mover children. Mover runtime owners already exist. Then applies L20S2.rfl trigger18344 reverse-disable. Do not run startup after initial child composition or replay it on graphics refresh/entity re-registration. This is separate from saved-game restoration/global sound cleanup.
void __thiscall rf_level_finalize_trigger_and_mover_links(void *this)
{
  int v1; // [esp+0h] [ebp-4h]

  rf_gamesound_stop_all_voice_slots();
  if ( dword_66158C >= 0 )
  {
    rf_gamesound_stop_voice_handle(dword_66158C);
    dword_66158C = -1;
  }
  if ( rf_local_fpgun_player )
    *(_DWORD *)(rf_local_fpgun_player + 16) &= ~0x400u;
  rf_trigger_commit_flag8_triggers();
  rf_mover_bind_authored_children();
  if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L20S2.rfl") )
  {
    v1 = rf_trigger_find_by_level_id32(18344);
    if ( v1 )
      rf_trigger_set_reverse_disabled(v1);
  }
  rf_ai_resume_updates();
}

