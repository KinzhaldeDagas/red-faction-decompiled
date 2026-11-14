// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059B970 rf_network_get_local_endpoint
// UNREALRED VERIFIED [reliable-connections-20261028]: Output pointer. If RAS-preference flag0x1C0C3F8 set,tries0x599950; zero/fallback uses local hostname then FIRST gethostbyname address. Default address0 on failure. Applies htonl to raw network-order address (byte swap on this target) before storing DWORD+0,thus stores the engine host-order IPv4 convention. Stores host-order bound-port WORD0x1C0C404 at+4 and returns that WORD. Does not initialize endpoint padding bytes+6/+7,validate output or scan multiple addresses.
__int16 __cdecl rf_network_get_local_endpoint(int a1)
{
  __int16 result; // ax
  char name[260]; // [esp+0h] [ebp-120h] BYREF
  int v3; // [esp+104h] [ebp-1Ch]
  u_long hostlong; // [esp+10Ch] [ebp-14h]
  struct hostent *v5; // [esp+11Ch] [ebp-4h]

  hostlong = 0;
  if ( unk_1C0C3F8 )
    hostlong = rf_network_query_last_ras_ipv4();
  if ( !unk_1C0C3F8 || !hostlong )
  {
    v3 = gethostname(name, 255);
    if ( v3 != -1 )
    {
      v5 = gethostbyname(name);
      if ( v5 )
        hostlong = **(_DWORD **)v5->h_addr_list;
    }
  }
  *(_DWORD *)a1 = htonl(hostlong);
  result = unk_1C0C404;
  *(_WORD *)(a1 + 4) = unk_1C0C404;
  return result;
}

