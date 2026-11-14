// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6DE0 rf_string_pool_attach_buffer
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool,external base pointer,capacity,ownership byte. Stores base+0,ownership+4,capacity+8,used bytes+12=0,returns BASE pointer (not pool). Does NOT initialize string count+16 or free old base. Caller can transfer ownership by nonzero byte; attached contents are not scanned for existing strings. No validation.
int __thiscall rf_string_pool_attach_buffer(_BYTE *this, int a2, int a3, char a4)
{
  *(this + 4) = a4;
  *((_DWORD *)this + 2) = a3;
  *((_DWORD *)this + 3) = 0;
  *(_DWORD *)this = a2;
  return a2;
}

