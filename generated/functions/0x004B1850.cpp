// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1850 rf_tracker_initialize_host_templates_and_pool
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg. InitializedDWORD7B4DB8 nonzero ->return1 immediately without DNS/pool reset. Otherwise set7B49B0=6,registration-last-seconds7B2620=0,registration-active7B2854=0;
// initialize packet templates at7B4798(opWORD4),7B4BB8(opWORD5),7B49B8(opWORD1),7B2648(opWORD3): firstBYTE6 and lengthWORD at+7 exactly10. Clear list-query7B2640 and
// timeout-latch7B4998, but do not memset full global templates. Initialize first256 of260 local text bytes to0 (first from original NUL63B5DD,then255-byte memset). Read registry
// default-root GameTracker into it ignoring status. Nonempty value copied with unbounded NUL loop to global host buffer662D10; original PE host rf.thqmultiplay.net. If Boolean
// command-line record7B4DBC enabled AND its argument-pointer member7B4DCC nonzero, copy argument unbounded into local, then if nonempty copy to global, overriding registry; empty
// override retains prior host. No destination-capacity checks. Try inet_addr; any value exceptFFFFFFFF accepted directly. Otherwise asyncDNS control2(host) must return>0, then
// busy-poll control3 with independent clock(1000) samples. Signed elapsed>=4000ms checked BEFORE nonzero DNS status; on timeout force status-1 and control1 cancellation, even if that
// poll reported success. Negative status->return0; no sleep/message/socket pumping here. Earlier template/host writes remain on failure, initialized stays0. Success store tracker
// host-order IPv4=ntohl(result) at7B2638,portWORD18444(0x480C) at7B263C. Build sockaddr at7B2610: familyWORD2,network-order address,htons18444 port,zero two paddingDWORDs7B2618/1C.
// Clear pending-state7B2624, initialize static endpoint pool, set initialized1,return1. No socket creation, control packet send, registry persistence or runtime/authority gate.
int rf_tracker_initialize_host_templates_and_pool()
{
  char v1; // [esp+3h] [ebp-16Dh]
  char *v2; // [esp+8h] [ebp-168h]
  char *v3; // [esp+Ch] [ebp-164h]
  char v4; // [esp+23h] [ebp-14Dh]
  char *v5; // [esp+28h] [ebp-148h]
  const char *argument; // [esp+2Ch] [ebp-144h]
  char v7; // [esp+33h] [ebp-13Dh]
  char *v8; // [esp+38h] [ebp-138h]
  char *v9; // [esp+3Ch] [ebp-134h]
  int v10; // [esp+50h] [ebp-120h]
  int v11; // [esp+54h] [ebp-11Ch]
  char v12[260]; // [esp+60h] [ebp-110h] BYREF
  u_long netlong; // [esp+168h] [ebp-8h] BYREF
  int v14; // [esp+16Ch] [ebp-4h]

  if ( dword_7B4DB8 )
    return 1;
  unk_7B49B0 = 6;
  unk_7B2620 = 0;
  unk_7B2854 = 0;
  unk_7B479F = 10;
  unk_7B4798 = 6;
  unk_7B4799 = 4;
  unk_7B4BB8 = 6;
  unk_7B4BB9 = 5;
  unk_7B4BBF = 10;
  unk_7B49B8 = 6;
  unk_7B49B9 = 1;
  unk_7B49BF = 10;
  unk_7B2648 = 6;
  unk_7B2649 = 3;
  unk_7B264F = 10;
  unk_7B2640 = 0;
  unk_7B4998 = 0;
  memset(v12, 0, 256);
  rf_registry_read_cstring(nullptr, "GameTracker", v12);
  v14 = &v12[strlen(v12) + 1] - &v12[1];
  if ( v14 > 0 )
  {
    v9 = v12;
    v8 = cp;
    do
    {
      v7 = *v9;
      *v8++ = *v9++;
    }
    while ( v7 );
  }
  if ( rf_command_line_bool_option_is_enabled(byte_7B4DBC) )
  {
    if ( unk_7B4DCC )
    {
      argument = rf_command_line_option_get_argument(byte_7B4DBC);
      v5 = v12;
      do
      {
        v4 = *argument;
        *v5++ = *argument++;
      }
      while ( v4 );
      if ( &v12[strlen(v12) + 1] - &v12[1] > 0 )
      {
        v3 = v12;
        v2 = cp;
        do
        {
          v1 = *v3;
          *v2++ = *v3++;
        }
        while ( v1 );
      }
    }
  }
  netlong = inet_addr(cp);
  if ( netlong != -1 )
    goto LABEL_22;
  if ( rf_network_async_dns_control(&netlong, 2, (int)cp) <= 0 )
    return 0;
  v10 = rf_performance_clock_elapsed_scaled(1000);
  while ( 1 )
  {
    v11 = rf_network_async_dns_control(&netlong, 3, (int)cp);
    if ( rf_performance_clock_elapsed_scaled(1000) - v10 >= 4000 )
      break;
    if ( v11 )
      goto LABEL_20;
  }
  v11 = -1;
  rf_network_async_dns_control(&netlong, 1, (int)cp);
LABEL_20:
  if ( v11 < 0 )
    return 0;
LABEL_22:
  dword_7B2638 = ntohl(netlong);
  unk_7B2610 = 2;
  unk_7B2618 = 0;
  unk_7B261C = 0;
  unk_7B2614 = htonl(dword_7B2638);
  unk_7B2612 = htons(0x480Cu);
  unk_7B263C = 18444;
  dword_7B2624 = 0;
  rf_tracker_initialize_static_endpoint_pool();
  dword_7B4DB8 = 1;
  return 1;
}

