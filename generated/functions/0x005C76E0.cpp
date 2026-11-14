// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C76E0 rf_clip_vertex48_pool_release
// UNREALRED VERIFIED [renderer-helpers-20261028]: Decrements used count0x1DB2648,stores caller pointer at0x1DB2588[newcount],returns count. No underflow,membership or double-release checks; no heap free or payload clearing.
int __cdecl rf_clip_vertex48_pool_release(int a1)
{
  int result; // eax

  result = --unk_1DB2648;
  unk_1DB2588[unk_1DB2648] = a1;
  return result;
}

