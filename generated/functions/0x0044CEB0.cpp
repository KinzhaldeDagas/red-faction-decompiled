// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CEB0 rf_hud_persona_reset_presentation
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Sets active persona index to -1, current opacity to 0, and disarms both global voice-start/end-cue timers. Does not clear target opacity, stop per-persona voices, or reset the history ring in this body.
_DWORD *rf_hud_persona_reset_presentation()
{
  rf_hud_persona_active_index = -1;
  rf_hud_persona_opacity = 0.0;
  rf_replicator_reset(&rf_hud_persona_voice_start_timer);
  return rf_replicator_reset(&rf_hud_persona_end_cue_timer);
}

