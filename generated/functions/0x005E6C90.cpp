// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6C90 rf_crc32_build_reflected_table_and_reset
// UNREALRED VERIFIED [event-registry-crc-20261028]: Builds256-entry global table0x1E41588 using8 reflected steps per byte with polynomial0xEDB88320; sets table-ready byte0x1E41988=1 and resets caller CRC dword to0. No initial all-ones state or final complement. Uses caller state as table-generation scratch.
unsigned int *__thiscall rf_crc32_build_reflected_table_and_reset(unsigned int *this)
{
  unsigned int v1; // ecx
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 256; ++i )
  {
    *this = i;
    for ( j = 8; j > 0; --j )
    {
      if ( (*this & 1) != 0 )
        v1 = (*this >> 1) ^ 0xEDB88320;
      else
        v1 = *this >> 1;
      *this = v1;
    }
    unk_1E41588[i] = *this;
  }
  unk_1E41988 = 1;
  *this = 0;
  return this;
}

