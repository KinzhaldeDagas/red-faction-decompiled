// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7120 rf_string_pool_construct_empty
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall zeroes base+0,ownership BYTE+4,capacity+8,used bytes+12,string count+16,returns this. Does not free a previous base; object member padding+5..7 unchanged.
_BYTE *__thiscall rf_string_pool_construct_empty(_BYTE *this)
{
  *(this + 4) = 0;
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 2) = 0;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 4) = 0;
  return this;
}

