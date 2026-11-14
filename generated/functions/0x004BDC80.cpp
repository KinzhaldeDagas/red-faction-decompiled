// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDC80 rf_record40_copy_mixed_fields
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall destination,source pointer stack word,RET4; returns destination. RAW integer MOV copies DWORD0,32,36 without float conversion. Offset4 uses x87 FLD/FSTP float; offsets8 and20 copy vec3 through vector-copy constructor. Total40 bytes, not ten float assignments despite old float-pointer pseudocode. No allocation, zeroing, pointer/overlap validation or inferred meaning for raw metadata words. Corrected void-pointer declaration preserves one-word thiscall ABI.
void *__thiscall rf_record40_copy_mixed_fields(void *this, const void *source)
{
  *(_DWORD *)this = *(_DWORD *)source;
  *((float *)this + 1) = *((float *)source + 1);
  rf_vector3_copy_return_destination((float *)this + 2, (float *)source + 2);
  rf_vector3_copy_return_destination((float *)this + 5, (float *)source + 5);
  *((_DWORD *)this + 8) = *((_DWORD *)source + 8);
  *((_DWORD *)this + 9) = *((_DWORD *)source + 9);
  return this;
}

