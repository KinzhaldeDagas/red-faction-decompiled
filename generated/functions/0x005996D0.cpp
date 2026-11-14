// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005996D0 rf_network_receive_queue_initialize
// UNREALRED VERIFIED [network-queues-20261028]: Queue pointer. Zeroes exactly66816bytes (96 records stride696),sets all record sequence DWORD+0=-1,next sequence+66816=0,oldest+66820=-1,newest+66824=-1. Returns queue pointer. Caller supplies66828bytes. No allocation,locking or destruction of previous contents.
void *__cdecl rf_network_receive_queue_initialize(void *a1)
{
  int i; // [esp+0h] [ebp-4h]

  memset(a1, 0, 0x10500u);
  for ( i = 0; i < 96; ++i )
    *((_DWORD *)a1 + 174 * i) = -1;
  *((_DWORD *)a1 + 16704) = 0;
  *((_DWORD *)a1 + 16705) = -1;
  *((_DWORD *)a1 + 16706) = -1;
  return a1;
}

