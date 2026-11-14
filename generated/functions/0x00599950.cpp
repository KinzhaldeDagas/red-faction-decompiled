// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599950 rf_network_query_last_ras_ipv4
// UNREALRED VERIFIED [network-queues-20261028]: Loads rasapi32.dll,resolves RasEnumConnectionsA,RasGetConnectStatusA,RasGetProjectionInfoA into globals0x1C0C410..418. Any missing API,enumeration error/no connections,status error or projection error returns0 after FreeLibrary. Uses legacy raw sizes:18000-byte enumeration buffer,720-byte RASCONN records,288-byte status,48-byte PPP-IP projection. Iterates every connection,queries RASP_PppIp and formats diagnostics into unused260-byte local. On all-success path frees DLL,converts LAST connection IP string with inet_addr and returns its network-order IPv4,or0 for INADDR_NONE. Does not filter status state,return first address or resize enumeration buffer. Function-pointer globals remain after unloading DLL. Modern IDA RAS struct names overlap unrelated stack locals; raw sizes/call operands establish actual legacy layouts.
unsigned int rf_network_query_last_ras_ipv4()
{
  struct tagRASCONNSTATUSA v1; // [esp+0h] [ebp-48D0h] BYREF
  _BYTE v2[17739]; // [esp+239h] [ebp-4697h] BYREF
  DWORD v3; // [esp+4784h] [ebp-14Ch] BYREF
  char Buffer[260]; // [esp+4788h] [ebp-148h] BYREF
  HMODULE hModule; // [esp+488Ch] [ebp-44h]
  int v6; // [esp+4890h] [ebp-40h] BYREF
  char cp[40]; // [esp+4898h] [ebp-38h] BYREF
  DWORD v8; // [esp+48C4h] [ebp-Ch]
  DWORD i; // [esp+48C8h] [ebp-8h]
  DWORD v10; // [esp+48CCh] [ebp-4h] BYREF

  *(_QWORD *)&v1.localEndPoint.ipv6.u.Word[2] = 0;
  hModule = LoadLibraryA("rasapi32.dll");
  if ( !hModule )
    return 0;
  MEMORY[0x1C0C410] = (DWORD (__stdcall *)(struct tagRASCONNA *, LPDWORD, LPDWORD))GetProcAddress(
                                                                                     hModule,
                                                                                     "RasEnumConnectionsA");
  if ( MEMORY[0x1C0C410]
    && (MEMORY[0x1C0C414] = (DWORD (__stdcall *)(HRASCONN, struct tagRASCONNSTATUSA *))GetProcAddress(
                                                                                         hModule,
                                                                                         "RasGetConnectStatusA")) != nullptr
    && (MEMORY[0x1C0C418] = (DWORD (__stdcall *)(HRASCONN, enum tagRASPROJECTION, LPVOID, LPDWORD))GetProcAddress(
                                                                                                     hModule,
                                                                                                     "RasGetProjectionInfoA")) != nullptr )
  {
    v3 = 18000;
    *(_DWORD *)&v1.localEndPoint.ipv6.u.Word[6] = 720;
    v8 = MEMORY[0x1C0C410]((struct tagRASCONNA *)&v1.localEndPoint.ipv6.u.Word[6], &v3, &v10);
    if ( v8 || !v10 )
    {
      FreeLibrary(hModule);
      return 0;
    }
    else
    {
      sprintf(Buffer, "Found %d connections\n", v10);
      for ( i = 0; i < v10; ++i )
      {
        sprintf(Buffer, "Connection %d:\n", i);
        sprintf(Buffer, "Entry Name: %s\n", (const char *)&v1.remoteEndPoint.ipv4 + 720 * i);
        sprintf(Buffer, "Device Type: %s\n", &v2[720 * i]);
        sprintf(Buffer, "Device Name: %s\n", &v2[720 * i + 17]);
        v1.dwSize = 288;
        v8 = MEMORY[0x1C0C414](*((HRASCONN *)&v1.remoteEndPoint.dwType + 180 * i), &v1);
        if ( v8
          || (v1.localEndPoint.ipv4.S_un.S_addr = 48,
              v6 = 48,
              (v8 = MEMORY[0x1C0C418](
                      *((HRASCONN *)&v1.remoteEndPoint.dwType + 180 * i),
                      RASP_PppIp,
                      &v6,
                      &v1.localEndPoint.ipv4.S_un.S_addr)) != 0) )
        {
          FreeLibrary(hModule);
          return 0;
        }
        sprintf(Buffer, "\tIP Address: %s\n", cp);
      }
      *(_DWORD *)&v1.localEndPoint.ipv6.u.Word[2] = 1;
      FreeLibrary(hModule);
      *(_DWORD *)&v1.localEndPoint.ipv6.u.Word[4] = inet_addr(cp);
      if ( *(_DWORD *)&v1.localEndPoint.ipv6.u.Word[4] == -1 )
        return 0;
      else
        return *(_DWORD *)&v1.localEndPoint.ipv6.u.Word[4];
    }
  }
  else
  {
    FreeLibrary(hModule);
    return 0;
  }
}

