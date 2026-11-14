// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005181D0 rf_byte_array_initialize_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall header,capacity DWORD,RET4. Zeros count/capacity/backing,then calls518140 only when capacity!=0. Does not free old backing before overwriting header;requires fresh/unowned header for leak-free initialization. No payload initialization or allocation rollback.
void __thiscall rf_byte_array_initialize_capacity(size_t *this, size_t a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_byte_array_reallocate_unchecked(this, a2);
}

