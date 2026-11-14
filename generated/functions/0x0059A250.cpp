// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059A250 rf_qsort_compare_float32_ascending
// UNREALRED VERIFIED [network-queues-20261028]: qsort comparator dereferences arguments as FLOAT32,not signed integers. Equal returns0,second<first returns1,second>first returns-1,unordered comparisons fall through0. Reliable service sorts ten raw DWORD RTT samples using this comparator,so it interprets their bits as floats. No pointer or NaN validation.
int __cdecl rf_qsort_compare_float32_ascending(float *a1, float *a2)
{
  if ( *a2 == *a1 )
    return 0;
  if ( *a2 < (double)*a1 )
    return 1;
  if ( *a2 <= (double)*a1 )
    return 0;
  return -1;
}

