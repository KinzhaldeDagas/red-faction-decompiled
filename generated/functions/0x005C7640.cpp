// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7640 rf_clip_vertex48_pool_reset
// UNREALRED VERIFIED [renderer-helpers-20261028]: Sets used count0x1DB2648=0; fills48 pointers at0x1DB2588 with48-byte records at0x1DB2650+48*i. Returns48. Does not clear record payload or flags. Shared allocator0x5C7C60 increments before checking newcount>=48,thus only47 successful allocations after reset.
int rf_clip_vertex48_pool_reset()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_1DB2648 = 0;
  for ( i = 0; i < 48; ++i )
  {
    unk_1DB2588[i] = (int)&unk_1DB2650 + 48 * i;
    result = i + 1;
  }
  return result;
}

