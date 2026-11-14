// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599840 rf_network_receive_queue_pop
// UNREALRED VERIFIED [network-queues-20261028]: Arguments queue,destination,length output,8-byte endpoint output. Queue has96 records stride696; sequence+0=-1 unused,length+4,endpoint+8/+12,payload+16; trailing next sequence+66816,oldest+66820,newest+66824. Returns0 if oldest=-1 or SIGNED oldest>newest,or no record matches oldest. Success copies entire stored payload without destination capacity argument,outputs length/endpoint,marks sequence=-1,increments oldest,returns1. Does not reset oldest when queue becomes empty,skip missing sequence IDs,handle wrap or lock. Failure leaves outputs unchanged.
int __cdecl rf_network_receive_queue_pop(int a1, void *a2, _DWORD *a3, _DWORD *a4)
{
  int i; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  v6 = 0;
  if ( *(_DWORD *)(a1 + 66820) == -1 || *(_DWORD *)(a1 + 66820) > *(_DWORD *)(a1 + 66824) )
    return 0;
  for ( i = 0; i < 96; ++i )
  {
    if ( *(_DWORD *)(a1 + 696 * i) == *(_DWORD *)(a1 + 66820) )
    {
      v6 = 1;
      break;
    }
  }
  if ( !v6 )
    return 0;
  memcpy(a2, (const void *)(a1 + 696 * i + 16), *(_DWORD *)(a1 + 696 * i + 4));
  *a3 = *(_DWORD *)(a1 + 696 * i + 4);
  *a4 = *(_DWORD *)(a1 + 696 * i + 8);
  a4[1] = *(_DWORD *)(a1 + 696 * i + 12);
  *(_DWORD *)(a1 + 696 * i) = -1;
  ++*(_DWORD *)(a1 + 66820);
  return 1;
}

