// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7690 rf_clip_extended_vertex_pool_reset
// UNREALRED VERIFIED [extended-clip-20261028]: Sets used count0x1DB264C=0 and initializes48 available pointers at0x1DB24C8 to132-byte records beginning0x1DB2F50. Returns48. Does not clear record payload or outcodes; reset invalidates outstanding scratch ownership logically without heap operations.
int rf_clip_extended_vertex_pool_reset()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_1DB264C = 0;
  for ( i = 0; i < 48; ++i )
  {
    unk_1DB24C8[i] = (int)&unk_1DB2F50 + 132 * i;
    result = i + 1;
  }
  return result;
}

