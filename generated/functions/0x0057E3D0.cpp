// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E3D0 rf_pointer_prefix_construct_null
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Writes only firstDWORD0,returns receiver. Leaves bytes at+4/+8 and remainder untouched;no allocation or calls. No direct xrefs in current database;exact original class unproven. Adjacent bitset code uses a pointer-first layout,but do not claim this initializes count/ownership.
_DWORD *__thiscall rf_pointer_prefix_construct_null(_DWORD *this)
{
  *this = 0;
  return this;
}

