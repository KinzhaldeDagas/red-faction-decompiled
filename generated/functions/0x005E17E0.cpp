// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E17E0 rf_d3d8_texture_cache_increment_resident_ages
// UNREALRED VERIFIED [image-headers-20261028]: Walks all entries; signed tilecount+4>0 increments16-bit age+6 with wrap. Does not alter references,locks or dirty flags. Local resident counter unused; returned EAX is loop index/slot count for positive count, not resident count, and not established when loop skipped.
int rf_d3d8_texture_cache_increment_resident_ages()
{
  int result; // eax
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = 0; i < dword_663F14; ++i )
  {
    if ( *(__int16 *)(unk_1E01548 + 16 * i + 4) > 0 )
    {
      ++*(_WORD *)(unk_1E01548 + 16 * i + 6);
      ++v2;
    }
    result = i + 1;
  }
  return result;
}

