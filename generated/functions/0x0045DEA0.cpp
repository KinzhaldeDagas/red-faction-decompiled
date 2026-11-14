// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DEA0 rf_two_rfstring_array16_element_address_unchecked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Thiscall arrayECX,indexDWORD stack,RET4. Return array.dataDWORD8 + (index<<4) with native32-bit wrap;no
// count/capacity/index sign/bounds,NULL or allocation guard. Returns ADDRESS of inline16-byte record,not pointer loaded from element. Level consumers use two RFString fields0/8.
// Existing integer return prototype preserved.
int __thiscall rf_two_rfstring_array16_element_address_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 16 * a2;
}

