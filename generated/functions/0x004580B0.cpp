// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004580B0 rf_record272_array_element_address_unchecked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall(receiver,raw index), RET4. Returns raw DWORD backing[receiver+8]+272*index with32-bit multiply/add wrap. Does not read element/count/capacity,
// validate negative/overflow/null index, or mutate anything; no element ownership transfer.
int __thiscall rf_record272_array_element_address_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 272 * a2;
}

