// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7C60 rf_clip_vertex48_pool_allocate_checked
// UNREALRED VERIFIED [extended-clip-20261028]: Reads pointer0x1DB2588[used0x1DB2648] BEFORE incrementing used. If new signed count>=48,returns0 without setting flags; otherwise sets record byte+25 exactly4 and returns pointer. Starting used0 therefore permits47 successful allocations; rejection still consumes count and repeated calls can read beyond pointer array. Does not clear other payload. Intersection helper0x5C7740 checks returned null.
int rf_clip_vertex48_pool_allocate_checked()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = unk_1DB2588[dword_1DB2648++];
  if ( dword_1DB2648 >= 48 )
    return 0;
  *(_BYTE *)(v1 + 25) = 4;
  return v1;
}

