// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CCF0 rf_inline_record48_element_unchecked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall receiver, one raw index, RET4. EAX=receiver+4+48*index using low32-bit multiply and address
// arithmetic. Returns element address without reading count/backing memory, bounds/sign checking, allocation, mutation or dereference. Negative/wrapped indices retain native pointer
// arithmetic.
int __thiscall rf_inline_record48_element_unchecked(void *this, int a2)
{
  return (int)this + 48 * a2 + 4;
}

