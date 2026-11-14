// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD390 rf_dword_construct_invalid_minus_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Thiscall receiver4-byte slot: stores0xFFFFFFFF then returns receiver. No other fields touched,no allocation. Prior Replicator constructor class/name was false SDK match;used for local packed-state word in recovered face renderer before it is overwritten. Generic invalid-DWORD constructor name avoids asserting one original C++ class for every caller.
unsigned int *__thiscall rf_dword_construct_invalid_minus_one(unsigned int *this)
{
  *this = -1;
  return this;
}

