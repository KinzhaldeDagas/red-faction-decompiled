// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C81F0 rf_clip_extended_vertex_pool_allocate
// UNREALRED VERIFIED [extended-clip-20261028]: Reads available pointer0x1DB24C8[used0x1DB264C],increments used,and assigns vertex byte+25 exactly4,marking temporary and clearing other flag bits. Returns vertex pointer. No48-record capacity or null guard; coordinates,outcode and attributes remain stale until filled.
int rf_clip_extended_vertex_pool_allocate()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = unk_1DB24C8[unk_1DB264C++];
  *(_BYTE *)(v1 + 25) = 4;
  return v1;
}

