// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C8B0 rf_reliable_udp_set_minimum_resend_delay
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments unsigned peer index,signed milliseconds. For index<40 and milliseconds>=333,writes DWORD minimum resend delay at record+1723. Does not change already scheduled slot timestamps or clamp current RTT estimate. Ignores smaller values; no state/upper limit check. Incidental return not a reliable success code.
int __cdecl rf_reliable_udp_set_minimum_resend_delay(unsigned int a1, int a2)
{
  int result; // eax

  if ( a1 < 0x28 )
  {
    result = a2;
    if ( a2 >= 333 )
      *(_DWORD *)((char *)&unk_1BCAACB + 1727 * a1) = a2;
  }
  return result;
}

