// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599DB0 rf_network_async_dns_control
// UNREALRED VERIFIED [network-queues-20261028]: Arguments IPv4 output pointer,mode,borrowed hostname pointer. Mode2 terminates any stored thread handle0x1C0C41C without CloseHandle,clears result0x1BCA310,stores hostname pointer0x1BCA314,clears success/failure/suppress bytes0x1BCA318..31A,creates worker0x599EC0,returns1 EVEN on CreateThread failure. Mode1 terminates stored thread if present,clears handle and returns-2. Mode3: no handle returns-1; success clears handle,writes raw network-order IPv4 output,returns1; failure clears handle,returns-1; pending returns0. Other modes return-2. Completion paths do not CloseHandle or wait. No hostname copy,output null check,locking or result ownership; caller must preserve hostname lifetime.
int __cdecl rf_network_async_dns_control(_DWORD *a1, int a2, int a3)
{
  if ( a2 != 2 )
  {
    if ( a2 == 1 )
    {
      if ( MEMORY[0x1C0C41C] )
      {
        TerminateThread(MEMORY[0x1C0C41C], 0);
        MEMORY[0x1C0C41C] = nullptr;
      }
    }
    else if ( a2 == 3 )
    {
      if ( !MEMORY[0x1C0C41C] )
        return -1;
      if ( unk_1BCA318 )
      {
        MEMORY[0x1C0C41C] = nullptr;
        *a1 = unk_1BCA310;
        return 1;
      }
      else if ( unk_1BCA319 )
      {
        MEMORY[0x1C0C41C] = nullptr;
        return -1;
      }
      else
      {
        return 0;
      }
    }
    return -2;
  }
  if ( MEMORY[0x1C0C41C] )
  {
    TerminateThread(MEMORY[0x1C0C41C], 0);
    MEMORY[0x1C0C41C] = nullptr;
  }
  unk_1BCA310 = 0;
  unk_1BCA314 = a3;
  unk_1BCA318 = 0;
  unk_1BCA319 = 0;
  unk_1BCA31A = 0;
  MEMORY[0x1C0C41C] = CreateThread(nullptr, 0, rf_network_async_dns_worker, nullptr, 0, &unk_1BDB2DC);
  return 1;
}

