// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B20F0 rf_network_control_poll_state012
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs. Inactive global7B4DB8 ->returns1. Active state7B2624==2 clearsstate0 andreturns1;state1 calls4B1CC0 thenreturns0. State0 stores TWO independently sampled clock(1000) readings into7B2850/7B49B4,setsstate1,counter7B2854=0,sends UDP packet at7B2648,length fromWORD7B264F,endpoint7B2638,channel2,andreturns0. Any other state returns0 unchanged. No own timeout/retry logic or check of send/callee result;do not infer a completed connection from return0.
int rf_network_control_poll_state012()
{
  if ( !dword_7B4DB8 )
    return 1;
  if ( dword_7B2624 == 2 )
  {
    dword_7B2624 = 0;
    return 1;
  }
  else if ( dword_7B2624 == 1 )
  {
    rf_tracker_update_send_retries_and_process_one_reply();
    return 0;
  }
  else
  {
    if ( !dword_7B2624 )
    {
      unk_7B2850 = rf_performance_clock_elapsed_scaled(1000);
      unk_7B49B4 = rf_performance_clock_elapsed_scaled(1000);
      dword_7B2624 = 1;
      unk_7B2854 = 0;
      rf_network_send_udp_channel_packet(&unk_7B2648, unk_7B264F, 0, (int)&dword_7B2638, 2);
    }
    return 0;
  }
}

