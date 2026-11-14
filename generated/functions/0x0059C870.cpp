// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C870 rf_reliable_udp_seed_rtt_before_ten_samples
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments unsigned index,value. For index<40 AND unsigned RTT sample count at record+1715<10,writes raw DWORD value to estimate+1719. No state check,value validation or service call. Incidental EAX not success status; invalid index can leave it uninitialized. Service replaces estimate after enough samples.
unsigned int __cdecl rf_reliable_udp_seed_rtt_before_ten_samples(unsigned int a1, int a2)
{
  unsigned int result; // eax

  if ( a1 < 0x28 )
  {
    result = 1727 * a1;
    if ( *(_DWORD *)((char *)&unk_1BCAAC3 + 1727 * a1) < 0xAu )
      *(_DWORD *)((char *)&unk_1BCAAC7 + 1727 * a1) = a2;
  }
  return result;
}

