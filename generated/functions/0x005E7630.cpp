// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7630 rf_byte_arena_reset_current_chunk_cursor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): If currentChunkData4 nonNULL,sets cursor8=currentChunkData4,then aligns/recomputes remaining via5E76E0. If data pointerNULL,no writes. No block free/zero-fill or lastAllocation20 reset. Existing pointer return is mixed/incidental:NULL-data path EAX receiver,nonnull path EAX remaining-byte integer from helper;not a consistent pointer result.
_DWORD *__thiscall rf_byte_arena_reset_current_chunk_cursor(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 1) )
  {
    *(this + 2) = *(this + 1);
    return (_DWORD *)rf_byte_arena_align_cursor_update_remaining(this);
  }
  return result;
}

