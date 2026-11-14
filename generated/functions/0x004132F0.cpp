// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004132F0 rf_vector_array12_element_address_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header plus signed/raw stack index,RET4. Returns DWORD[receiver+8]+12*index using32-bit address arithmetic;no count/capacity/NULL/negative-index check,allocation or dereference of returned element. Receiver header unchanged.
int __thiscall rf_vector_array12_element_address_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 12 * a2;
}

