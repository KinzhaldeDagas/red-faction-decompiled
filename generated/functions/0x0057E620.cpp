// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E620 rf_bitset_release_owned_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): If backing pointer0 nonNULL AND owned byte8 nonzero,operator-delete backing and set pointer0=NULL. Otherwise leaves pointer unchanged,including borrowed backing. Always returns receiver. Stored byteCount4 and owned flag8 never reset. No bit clearing/member destructor.
int __thiscall rf_bitset_release_owned_buffer(int this)
{
  int result; // eax

  result = this;
  if ( *(_DWORD *)this )
  {
    if ( *(_BYTE *)(this + 8) )
    {
      operator delete(*(void **)this);
      *(_DWORD *)this = 0;
      return this;
    }
  }
  return result;
}

