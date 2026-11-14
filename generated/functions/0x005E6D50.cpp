// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6D50 rf_crc32_update_reflected_raw
// UNREALRED VERIFIED [event-registry-crc-20261028]: If table-ready byte0x1E41988 is clear, builds table and RESETS caller state to0. For each byte computes state=table[(state XOR byte)&255] XOR (state>>8); returns raw state with no final XOR. Existing initialized caller state is carried across calls. Length uses decrement-until-zero with no negative-length guard. This zero-seeded/non-complemented variant differs from conventional published CRC-32 values.
unsigned int __thiscall rf_crc32_update_reflected_raw(unsigned int *this, _BYTE *a2, int a3)
{
  int v6; // [esp+4h] [ebp-8h]

  if ( !unk_1E41988 )
    rf_crc32_build_reflected_table_and_reset(this);
  while ( a3-- )
  {
    v6 = unk_1E41588[(unsigned __int8)(*(_BYTE *)this ^ *a2++)];
    *this = v6 ^ (unsigned int)&unk_FFFFFF & (*this >> 8);
  }
  return *this;
}

