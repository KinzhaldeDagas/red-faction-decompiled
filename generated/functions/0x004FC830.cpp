// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC830 rf_event_countdown_end_apply
// UNREALRED VERIFIED [hud-late-pass] Countdown_End event handler clears the shared mission countdown to zero.
void rf_event_countdown_end_apply()
{
  rf_mission_countdown_remaining_seconds = 0.0;
}

