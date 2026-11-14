// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574350 rf_bitmap_handle_to_slot_index
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Unsigned handle decoder. With mask 0x40000000 set, returns (handle & 0xBFFFFFFF) % 3000; otherwise handle % global slot count 0x663F14. Does not validate generation, sign, occupancy or full stored handle. Zero ordinary slot count divides by zero. Other high bits remain part of modulo input.
unsigned int __cdecl rf_bitmap_handle_to_slot_index(unsigned int a1)
{
  if ( (a1 & 0x40000000) != 0 )
    return (a1 & 0xBFFFFFFF) % 0xBB8;
  else
    return a1 % dword_663F14;
}

