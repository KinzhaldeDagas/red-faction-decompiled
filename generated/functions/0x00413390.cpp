// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413390 rf_matrix_array36_element_address_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header plus stack index,RET4. Returns DWORDbase8+36*index,32-bit wrapping pointer arithmetic;no bounds/count/NULL/sign/overflow validation,storage access through result or mutation.
int __thiscall rf_matrix_array36_element_address_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 36 * a2;
}

