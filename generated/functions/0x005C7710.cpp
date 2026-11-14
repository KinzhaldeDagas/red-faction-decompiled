// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7710 rf_clip_extended_vertex_pool_release
// UNREALRED VERIFIED [extended-clip-20261028]: Decrements used count0x1DB264C,stores caller vertex in available-pointer stack0x1DB24C8 at new count,and returns that count. Does not clear vertex flags,payload or free heap memory. No underflow,pool membership or double-release guard; does not enforce release order.
int __cdecl rf_clip_extended_vertex_pool_release(int a1)
{
  int result; // eax

  result = --unk_1DB264C;
  unk_1DB24C8[unk_1DB264C] = a1;
  return result;
}

