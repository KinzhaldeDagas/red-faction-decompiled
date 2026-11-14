// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6E20 rf_string_pool_allocate_owned
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool,capacity bytes. Sets ownership BYTE+4=1,capacity DWORD+8=requested,used bytes+12=0,string count+16=0,allocates operator new(capacity) and stores base pointer+0. Returns pool pointer. Does not free prior allocation,test allocation result,zero buffer or enforce capacity during subsequent copies.
_BYTE *__thiscall rf_string_pool_allocate_owned(_BYTE *this, size_t Size)
{
  void *v4; // [esp+4h] [ebp-4h]

  *(this + 4) = 1;
  *((_DWORD *)this + 2) = Size;
  *((_DWORD *)this + 3) = 0;
  *((_DWORD *)this + 4) = 0;
  v4 = operator new(Size);
  *(_DWORD *)this = v4;
  return this;
}

