// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A1ED0 rf_multiplayer_item_active_bitmap_tick
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No-argument throttle. If wrapped deadline78C24C is unarmed OR elapsed result is any nonzero, broadcasts indexed item bitmap37 then rearms250ms from current wrapped game clock. No
// own mode/authority guard, no check whether any peer received data, no missed-interval catchup. Existing caller is server session tick. Return AL/delegate EAX is incidental, not
// count/success.
char rf_multiplayer_item_active_bitmap_tick()
{
  char result; // al

  if ( !rf_timestamp_is_armed_nonnegative(&dword_78C24C)
    || (result = rf_clock_deadline_has_elapsed_half_period(&dword_78C24C)) != 0 )
  {
    rf_multiplayer_broadcast_item_active_bitmap37();
    return rf_clock_deadline_set_wrapped_offset(&dword_78C24C, 250);
  }
  return result;
}

