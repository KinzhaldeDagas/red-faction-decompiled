// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FBA0 rf_ui_caret_blink_tick
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): If shared deadline6F911C is unarmed OR elapsed, stores logical NOT of raw caret BYTE6F9118 (zero->1, any nonzero->0) and rearms400ms. Otherwise leaves caret/timer unchanged.
// No own initialization, edit-focus gate or display update. Return is incidental delegate/register residue.
char rf_ui_caret_blink_tick()
{
  char result; // al

  if ( !rf_timestamp_is_armed_nonnegative(&dword_6F911C)
    || (result = rf_clock_deadline_has_elapsed_half_period(&dword_6F911C)) != 0 )
  {
    byte_6F9118[0] = byte_6F9118[0] == 0;
    return rf_clock_deadline_set_wrapped_offset(&dword_6F911C, 400);
  }
  return result;
}

