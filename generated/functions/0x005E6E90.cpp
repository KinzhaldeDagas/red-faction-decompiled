// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6E90 rf_string_pool_release_buffer
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool. If base DWORD+0 nonnull,deletes it ONLY when ownership BYTE+4 nonzero,then zeroes base,ownership,used bytes+12,capacity+8,string count+16. If base already null,returns immediately WITHOUT clearing any other fields. Returns pool pointer; no string destructors or individual allocations.
int __thiscall rf_string_pool_release_buffer(int this)
{
  int result; // eax

  result = this;
  if ( *(_DWORD *)this )
  {
    if ( *(_BYTE *)(this + 4) )
      operator delete(*(void **)this);
    *(_DWORD *)this = 0;
    *(_BYTE *)(this + 4) = 0;
    *(_DWORD *)(this + 12) = 0;
    *(_DWORD *)(this + 8) = 0;
    *(_DWORD *)(this + 16) = 0;
    return this;
  }
  return result;
}

