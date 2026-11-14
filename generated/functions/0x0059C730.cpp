// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C730 rf_reliable_udp_close_matching_endpoint
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments endpoint,notify flag. Scans ALL40 records,state DWORD+1658 must be nonzero; compares DWORD host-order IP+1666 and WORD port+1670. For each exact match,calls0x59C4F0 using local index. May close multiple records; includes index0. Does not service peers or validate endpoint. Incidental loop return40,not number closed.
int __cdecl rf_reliable_udp_close_matching_endpoint(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-8h] BYREF
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 40; ++i )
  {
    if ( *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * i)
      && *(_DWORD *)((char *)&unk_1BCAA92 + 1727 * i) == *(_DWORD *)a1
      && *(unsigned __int16 *)((char *)&unk_1BCAA96 + 1727 * i) == *(unsigned __int16 *)(a1 + 4) )
    {
      v3 = i;
      rf_reliable_udp_close_peer(&v3, a2);
    }
    result = i + 1;
  }
  return result;
}

