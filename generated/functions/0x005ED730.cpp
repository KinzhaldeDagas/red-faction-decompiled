// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED730 rf_acm_close_stream
// UNREALRED VERIFIED [wave-codec-20261028]: Calls acmStreamClose(handle,0),returns0 on API success,else-1. Does not check readiness,null caller handle,reset codec or close driver.
int __cdecl rf_acm_close_stream(HACMSTREAM has)
{
  if ( acmStreamClose(has, 0) )
    return -1;
  else
    return 0;
}

