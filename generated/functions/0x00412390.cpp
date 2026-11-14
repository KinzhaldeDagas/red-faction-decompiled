// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412390 rf_camera_randomize_sample_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No stack arguments. Draws rand() once, obtains signed divisor DWORD[666AD0] via486DE0, then CDQ/IDIV computes signed
// quotient/remainder. Stores EDX remainder into shared666A98 and returns EAX quotient incidentally, NOT selected sample index. No empty/zero/negative count guard; divide-by-zero is
// not replaced with a fallback. Does not set a slot state, read sample points or write camera pose.
int rf_camera_randomize_sample_index()
{
  int v0; // esi
  int first_dword; // eax
  int v3; // et2

  v0 = rand();
  first_dword = rf_receiver_get_first_dword(dword_666AD0);
  v3 = v0 % first_dword;
  dword_666A98 = v3;
  return v0 / first_dword;
}

