// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518090 rf_byte_array_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall12-byte header,low BYTE value,RET4. If count==capacity,grows to2*capacity or16 when capacity0 using518140. Then returns OLD count,postincrements count,and writes one byte at backing+oldCount. Growth tested only for equality,not count>=capacity. No overflow,allocation/pointer/capacity invariant check or NUL termination;one-byte elements,not DWORDs.
size_t __thiscall rf_byte_array_append(size_t *this, char a2)
{
  size_t v3; // [esp+0h] [ebp-Ch]
  size_t v5; // [esp+8h] [ebp-4h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v3 = 2 * *(this + 1);
    else
      v3 = 16;
    rf_byte_array_reallocate_unchecked(this, v3);
  }
  v5 = (*this)++;
  *(_BYTE *)(*(this + 2) + v5) = a2;
  return v5;
}

