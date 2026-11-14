// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600310 rf_jpeg_jdiv_round_up
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jutils.c:jdiv_round_up matched): Cdecltwo32-bitsignedlongs(a,b),returns(a+b-1)/b withsignedtruncationtowardzero. Intendedpositiveargumentsandb>0;nooverflow/zero/negativeguard. Notgeneralmathematicalceildivisionforarbitrarysignedinputs.
int __cdecl rf_jpeg_jdiv_round_up(int a1, int a2)
{
  return (a1 + a2 - 1) / a2;
}

