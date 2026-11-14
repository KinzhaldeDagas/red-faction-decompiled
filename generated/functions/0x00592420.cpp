// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592420 rf_vfile_destruct_close_if_open
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Thiscall VFile receiver. If SIGNED stream-slot DWORD+272>=0 calls rf_vfile_close_stdio_or_vpp and returns that helper EAX; otherwise returns receiver in EAX. Does not free receiver object storage. Compiler SEH cleanup and ordinary stack-object callers use this destructor adapter; no type/pointer/slot upper-bound check in wrapper.
int *__thiscall rf_vfile_destruct_close_if_open(int *this)
{
  int *result; // eax

  result = this;
  if ( *(this + 68) >= 0 )
    return (int *)rf_vfile_close_stdio_or_vpp(this);
  return result;
}

