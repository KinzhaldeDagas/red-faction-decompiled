// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E76E0 rf_byte_arena_align_cursor_update_remaining
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall aligns cursor8 upward to4-byte boundary using cursor&3. remaining=max_signed(chunkCapacity12-(cursor8-currentChunkData4),0),stores16,returns remaining integer. Pointer/size arithmetic32-bit;no ownership/end-pointer validation,chunk allocation or payload clearing.
int __thiscall rf_byte_arena_align_cursor_update_remaining(_DWORD *this)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-4h]

  if ( (*(this + 2) & 3) != 0 )
    *(this + 2) += 4 - (*(this + 2) & 3);
  v2 = *(this + 3) - (*(this + 2) - *(this + 1));
  result = v2 < 0 ? 0 : v2;
  *(this + 4) = result;
  return result;
}

