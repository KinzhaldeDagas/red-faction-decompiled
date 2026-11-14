// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F69F0 rf_quick_actions_process_pending
// UNREALRED VERIFIED [save-validation-20261028]: Save byte0x894D29 takes priority: executes quicksave then clears that byte. Otherwise load byte0x894D2A invokes quickload request then is cleared. If both pending, load remains for a later pump. Flags clear after their calls.
void rf_quick_actions_process_pending()
{
  if ( unk_894D29 )
  {
    rf_quicksave_execute();
    unk_894D29 = 0;
  }
  else if ( unk_894D2A )
  {
    rf_quickload_request_level_transition();
    unk_894D2A = 0;
  }
}

