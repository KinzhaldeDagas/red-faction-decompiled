// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595290 rf_progress_update_poll_network_and_callback
// UNREALRED VERIFIED [system-progress-20261028]: Arguments valueA,valueB. If reentrancy counter0x1BC2150 nonzero,deadline0x664794 signed negative,or callback0x1BC214C null,returns0 without pumping. Otherwise increments invocation count0x1BC2154,samples elapsed milliseconds,ALWAYS calls0x59B090 to poll network. Dispatch if signed now>deadline OR(count>lastCount+155 AND positive control0x664798). Only on dispatch and poll flag0x1BC2148,drains entire input event queue; any dequeued value1 sets sticky abort0x1BC2149=1. Stores lastCount, increments reentrancy counter around callback(count,valueB,valueA), then deadline=sampledNow+100. Returns sticky abort byte even without dispatch. Does not preserve other drained input events or use callback return value; time comparison is strict and signed.
char __cdecl rf_progress_update_poll_network_and_callback(int a1, int a2)
{
  int v3; // [esp+0h] [ebp-4h]

  if ( unk_1BC2150 )
    return 0;
  if ( dword_664794 < 0 )
    return 0;
  if ( !unk_1BC214C )
    return 0;
  ++dword_1BC2154;
  v3 = rf_performance_clock_elapsed_scaled(1000);
  rf_network_poll_udp_into_receive_queues();
  if ( v3 > dword_664794 || dword_1BC2154 > unk_1BC2158 + 155 && dword_664798 > 0 )
  {
    if ( unk_1BC2148 )
    {
      while ( rf_input_event_queue_not_empty() )
      {
        if ( rf_input_dequeue_event() == 1 )
          unk_1BC2149 = 1;
      }
    }
    unk_1BC2158 = dword_1BC2154;
    ++unk_1BC2150;
    unk_1BC214C(dword_1BC2154, a2, a1);
    --unk_1BC2150;
    dword_664794 = v3 + 100;
  }
  return unk_1BC2149;
}

