// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6F50 rf_net_statistics_sample_mean
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): Thiscall ECX statistics, no stack arguments. Signed countDWORD+1412<=0 returns0. Otherwise signed32 accumulator sums DWORD samples at+1404+4*i for
// i0..<fresh count (count re-read each test), then divides signed accumulator by signed count via x87 FILD/FIDIV and truncates to integer. No upper-count/overflow guard or smoothing.
// Native count lies immediately after the first two sample slots; do not infer a larger safe array from arbitrary positive count.
int __thiscall rf_net_statistics_sample_mean(int *this)
{
  int i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  if ( *(this + 353) <= 0 )
    return 0;
  v3 = 0;
  for ( i = 0; i < *(this + 353); ++i )
    v3 += *(this + i + 351);
  return (int)((double)v3 / (double)*(this + 353));
}

