// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490370 rf_string_array8_element_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall12-byte array header(count0,capacity4,backing8),stack index,RET4. Returns backing+8*index by raw32-bit address arithmetic. No count/capacity/negative-index/NULL validation
// or element construction; element stride8 is RFString ownership from allocator45E020 and deletion45DF10. Used by level-rotation selection/shuffle.
int __thiscall rf_string_array8_element_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 8 * a2;
}

