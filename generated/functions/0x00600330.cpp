// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600330 rf_jpeg_jround_up
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jutils.c:jround_up matched): Cdeclsignedlong(a,b),computest=a+b-1,returnst-t%b. Roundspositiveauptomultiplepositiveb;32-bitsignedarithmetic,notbitmaskalignment. No zero,negativeoroverflowguard.
int __cdecl rf_jpeg_jround_up(int a1, int a2)
{
  return a1 + a2 - 1 - (a1 + a2 - 1) % a2;
}

