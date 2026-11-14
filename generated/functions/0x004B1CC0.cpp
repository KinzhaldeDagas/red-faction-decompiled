// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1CC0 rf_tracker_update_send_retries_and_process_one_reply
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg; inactive7B4DB8 ->no work. Poll shared UDP input queues, sample integer elapsed SECONDS(clock scale1) and MILLISECONDS(scale1000). If registration-active7B2854
// and signed seconds-last7B2620 >100 and pending-control7B2624==0, send template7B4798 using unsigned WORD length+7. Else if registration-active and not ACKed7B2644 and signed
// milliseconds-last7B2848 >5000, send same. On either send clear ACK flag and replace both timestamps regardless send outcome; second branch may retry even nonzero pending state. If
// list-query7B2640 active and signed abs32(seconds-last7B284C)>=10, set one-shot timeout-latch7B4998=1 and clear list-query; native two's-complement ABS leaves INT_MIN negative. If
// pending-control nonzero AND UNSIGNED milliseconds-last7B2850>5000, update timestamp then send7B2648 with WORD7B264F, no retry limit/error handling. Process at most ONE channel2
// queued packet after sends/timeouts. Call receive-channel-pop(buffer,509,0,sourceOut,2); verified callee IGNORES capacity509. Reject returned-1; decrement local WORD at packet+7
// modulo65536 and require returned payload length==that value. No minimum header size, prefixBYTE6 validation, sender endpoint comparison, sequence matching or per-operation payload
// bounds here. Operation is WORD+1:0 sets ACK flag1 and pending-state0;6 parses payload+9 only if list-query still active, then resamples seconds into7B284C; ALWAYS ACK received raw
// DWORD+3 for op6 even inactive. Operation7 clears list-query and ALWAYS ACKs raw sequence. Other opcodes ignored. SourceOut not consulted. Transport adds channel prefix on outgoing
// calls; this body preserves native length comparison without assuming protocol repair. No queue draining, wait or initialization success result.
void rf_tracker_update_send_retries_and_process_one_reply()
{
  int v0; // [esp+4h] [ebp-21Ch]
  char v1; // [esp+8h] [ebp-218h] BYREF
  __int16 v2; // [esp+9h] [ebp-217h]
  int v3; // [esp+Bh] [ebp-215h]
  __int16 v4; // [esp+Fh] [ebp-211h]
  char v5[503]; // [esp+11h] [ebp-20Fh] BYREF
  int v6; // [esp+20Ch] [ebp-14h] BYREF
  int v7; // [esp+214h] [ebp-Ch]
  int v8; // [esp+218h] [ebp-8h]
  size_t Size; // [esp+21Ch] [ebp-4h]

  if ( dword_7B4DB8 )
  {
    rf_network_poll_udp_into_receive_queues();
    v7 = rf_performance_clock_elapsed_scaled(1);
    v8 = rf_performance_clock_elapsed_scaled(1000);
    if ( unk_7B2854 && v7 - unk_7B2620 > 100 && !dword_7B2624 || unk_7B2854 && !unk_7B2644 && v8 - unk_7B2848 > 5000 )
    {
      Size = unk_7B479F;
      rf_network_send_udp_channel_packet(&unk_7B4798, unk_7B479F, 0, (int)&dword_7B2638, 2);
      unk_7B2644 = 0;
      unk_7B2620 = v7;
      unk_7B2848 = v8;
    }
    if ( unk_7B2640 && (int)abs32(v7 - unk_7B284C) >= 10 )
    {
      unk_7B4998 = 1;
      unk_7B2640 = 0;
    }
    if ( dword_7B2624 && (unsigned int)(v8 - unk_7B2850) > 0x1388 )
    {
      Size = unk_7B264F;
      unk_7B2850 = v8;
      rf_network_send_udp_channel_packet(&unk_7B2648, unk_7B264F, 0, (int)&dword_7B2638, 2);
    }
    if ( rf_network_receive_channel_has_sequence_range(2u) )
    {
      v0 = rf_network_receive_channel_pop(&v1, 509, 0, &v6, 2u);
      if ( v0 != -1 && v0 == (unsigned __int16)--v4 )
      {
        if ( v2 )
        {
          if ( v2 == 6 )
          {
            if ( unk_7B2640 )
            {
              rf_tracker_append_endpoint_reply_records(v5);
              unk_7B284C = rf_performance_clock_elapsed_scaled(1);
            }
            rf_tracker_send_sequence_acknowledgment(v3);
          }
          else if ( v2 == 7 )
          {
            unk_7B2640 = 0;
            rf_tracker_send_sequence_acknowledgment(v3);
          }
        }
        else
        {
          unk_7B2644 = 1;
          dword_7B2624 = 0;
        }
      }
    }
  }
}

