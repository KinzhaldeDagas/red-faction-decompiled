// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7660 rf_byte_arena_allocate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall arena header:head0,currentChunkData4,cursor8,chunkCapacity12,remaining16,lastAllocation20,flags24. If remaining>=request unsigned,allocate directly. Otherwise requires flags bit02 and successful new-chunk helper5E7520(return0),then rechecks remaining>=request;failure returnsNULL. Success remembers old cursor,advances by requested bytes,aligns cursor/recomputes remaining via5E76E0,stores lastAllocation20=oldCursor,returns oldCursor. No zero-fill,per-allocation free or request-overflow guard;zero request still updates alignment/lastAllocation. Bitset arena allocator treats returned buffer as borrowed.
int __thiscall rf_byte_arena_allocate(_DWORD *this, unsigned int a2)
{
  int v4; // [esp+4h] [ebp-4h]

  if ( *(this + 4) >= a2 )
    goto LABEL_7;
  if ( ((*(this + 6) >> 1) & 1) == 0 || rf_byte_arena_prepend_chunk(this) )
    return 0;
  if ( *(this + 4) < a2 )
    return 0;
LABEL_7:
  v4 = *(this + 2);
  *(this + 2) = a2 + v4;
  rf_byte_arena_align_cursor_update_remaining(this);
  *(this + 5) = v4;
  return v4;
}

