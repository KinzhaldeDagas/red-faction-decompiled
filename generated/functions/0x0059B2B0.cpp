// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059B2B0 rf_network_initialize_winsock_and_udp
// UNREALRED VERIFIED [reliable-connections-20261028]: WORD port. Seeds global connection-speed text0x1C0C690 with None,calls0x59E2E0(NULL,ConnectionSpeed,text),maps case-insensitive recognized values to0..3,then UNCONDITIONALLY overwrites speed0x1C0C2F4=3. Consequently subsequent branch for speed2/RAS detection is unreachable in this body. WSAStartup(0x0101); failure returns sprintf character count,not a consistent error code. Success sets startup flag0x1C0C400,registers0x59B250 with atexit,calls UDP bind initializer0x599F80 ignoring result,initializes all3 channel queues at0x1BDB3D0 stride66828,resets statistics. Returns statistics deadline pointer. No already-initialized guard,UDP failure propagation or rollback.
_DWORD *__cdecl rf_network_initialize_winsock_and_udp(u_short a1)
{
  char Buffer[260]; // [esp+4h] [ebp-2A8h] BYREF
  int v3; // [esp+108h] [ebp-1A4h]
  int i; // [esp+10Ch] [ebp-1A0h]
  __int16 v5; // [esp+110h] [ebp-19Ch]
  struct WSAData WSAData; // [esp+114h] [ebp-198h] BYREF

  strcpy(byte_1C0C690, "None");
  rf_registry_read_cstring(nullptr, "ConnectionSpeed", byte_1C0C690);
  if ( !_stricmp(byte_1C0C690, "none") )
  {
    unk_1C0C2F4 = 0;
  }
  else if ( !_stricmp(byte_1C0C690, "slow") )
  {
    unk_1C0C2F4 = 1;
  }
  else if ( !_stricmp(byte_1C0C690, off_642940) )
  {
    unk_1C0C2F4 = 2;
  }
  else if ( !_stricmp(byte_1C0C690, "fast") )
  {
    unk_1C0C2F4 = 3;
  }
  else
  {
    unk_1C0C2F4 = 0;
  }
  unk_1C0C2F4 = 3;
  if ( unk_1C0C2F4 == 2 )
    unk_1C0C3F8 = rf_network_query_last_ras_ipv4() != 0;
  v5 = 257;
  v3 = WSAStartup(0x101u, &WSAData);
  if ( v3 )
    return (_DWORD *)sprintf(Buffer, "There was an error initializing networking! Error=%d\n", v3);
  unk_1C0C400 = 1;
  atexit(rf_network_shutdown_winsock);
  rf_network_open_bound_udp_socket(a1);
  for ( i = 0; i < 3; ++i )
    rf_network_receive_queue_initialize(&unk_1BDB3D0[16707 * i]);
  return rf_network_statistics_reset_all_buckets();
}

