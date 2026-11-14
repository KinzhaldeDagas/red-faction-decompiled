// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059B250 rf_network_shutdown_winsock
// UNREALRED VERIFIED [reliable-connections-20261028]: If startup flag0x1C0C400 set,calls WSACancelBlockingCall; if global socket s!=-1,shutdown(s,SD_SEND=1) then closesocket. Calls WSACleanup and clears startup flag and enabled flag0x1C0C3FC. Ignores all results,does NOT reset stored socket to INVALID_SOCKET,release peer send/receive buffers,clear queues or stop asynchronous DNS thread.
void __cdecl rf_network_shutdown_winsock()
{
  if ( unk_1C0C400 )
  {
    WSACancelBlockingCall();
    if ( s != -1 )
    {
      shutdown(s, 1);
      closesocket(s);
    }
    WSACleanup();
    unk_1C0C400 = 0;
    unk_1C0C3FC = 0;
  }
}

