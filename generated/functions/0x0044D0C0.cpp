// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D0C0 rf_hud_persona_update_audio
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Separate HUD-update audio pump (called at 0x44A9C8). With active index != -1, expired shared voice-start timer plays selected record sound +0x20 through 0x568000 with channel-group index 2, start offset 0 and float gain approximately 0.9; stores returned handle at +0x1C and disarms timer. Independently, expired shared end-cue timer plays event 4 with group 0/offset 0/gain 1, then disarms that timer. This body does not repeat the persona visibility predicate.
void rf_hud_persona_update_audio()
{
  char *v0; // [esp+8h] [ebp-4h]

  if ( rf_hud_persona_active_index != -1 )
  {
    v0 = &rf_hud_persona_records[296 * rf_hud_persona_active_index];
    if ( rf_replicator_has_elapsed(&rf_hud_persona_voice_start_timer) )
    {
      *((_DWORD *)v0 + 7) = sub_568000(*((_DWORD *)v0 + 8), 2, 0.0, 0.89999998);
      rf_replicator_reset(&rf_hud_persona_voice_start_timer);
    }
    if ( rf_replicator_has_elapsed(&rf_hud_persona_end_cue_timer) )
    {
      sub_568000(4, 0, 0.0, 1.0);
      rf_replicator_reset(&rf_hud_persona_end_cue_timer);
    }
  }
}

