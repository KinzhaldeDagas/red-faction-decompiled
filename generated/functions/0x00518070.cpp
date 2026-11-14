// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518070 rf_byte_array_construct_capacity_wrapper
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall byte-array header,capacity DWORD,RET4. Delegates5181D0 and returns receiver. Header is count0,capacity4,backing8;capacity is BYTES. No element construction or old-storage destruction in wrapper.
size_t *__thiscall rf_byte_array_construct_capacity_wrapper(size_t *this, size_t a2)
{
  rf_byte_array_initialize_capacity(this, a2);
  return this;
}

