// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005010F0 rf_event_go_undercover_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_go_undercover reverse, vtable0x63E348 slot+8. Call0x4EF4D0 without event arguments. Reversal uses shared undercover state and baseline definition, not an event-local saved snapshot.
int rf_event_go_undercover_reverse()
{
  return rf_undercover_exit_replace_player_entity();
}

