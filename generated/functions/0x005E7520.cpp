// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7520 rf_byte_arena_prepend_chunk
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Allocates chunkCapacity12+8 bytes using32-bit size arithmetic. NULL returns1;otherwise firstDWORD of new block=old head0,head0=new block,currentChunkData4=new block+4,then reset-chunk helper5E7630,returns0. No old-chunk free,capacity growth or payload zero-fill. New block links backward;operator-new exceptions not caught here.
int __thiscall rf_byte_arena_prepend_chunk(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  v3 = operator new(*(this + 3) + 8);
  if ( !v3 )
    return 1;
  *v3 = *this;
  *this = v3;
  *(this + 1) = *this + 4;
  rf_byte_arena_reset_current_chunk_cursor(this);
  return 0;
}

