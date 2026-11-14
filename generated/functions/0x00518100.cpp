// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518100 rf_byte_array_element_address_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall header,signed index,RET4;returns backing DWORD8+index as BYTE POINTER,without dereference or bounds/count test. Corrected old int return and header pointer;32-bit address arithmetic wraps. No scaling by4 or string semantics.
unsigned __int8 *__thiscall rf_byte_array_element_address_unchecked(void *header, int index)
{
  return (unsigned __int8 *)(index + *((_DWORD *)header + 2));
}

