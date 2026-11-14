// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C7B0 rf_network_compare_endpoints
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments endpointA,endpointB,compare-port byte. Returns0 if IPv4 DWORDs equal and either compare-port byte0 or WORD ports+4 equal; otherwise-1. Ignores padding,does not order addresses or convert byte order. No pointer validation.
int __cdecl rf_network_compare_endpoints(int a1, int a2, char a3)
{
  if ( *(_DWORD *)a1 == *(_DWORD *)a2 && (!a3 || *(unsigned __int16 *)(a1 + 4) == *(unsigned __int16 *)(a2 + 4)) )
    return 0;
  else
    return -1;
}

