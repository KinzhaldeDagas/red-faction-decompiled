// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549F60 rf_byte1_assign_ignoring_middle_argument
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall receiver,unused stackDWORD,byte value. Writes receiver+1=value,returns receiver;first stack argument never read. Does not change byte0 or other flags. Exact original class and byte semantics unproven.
_BYTE *__thiscall rf_byte1_assign_ignoring_middle_argument(_BYTE *this, int a2, char a3)
{
  *(this + 1) = a3;
  return this;
}

