// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D5E0 rf_array24_get_element_address_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Thiscall collection receiver plus signed index DWORD on stack, RET4. Returns raw address DWORD(receiver+8)+24*index using32-bit arithmetic. Does not read count/capacity, validate index/base/receiver or dereference returned element. Collision callers use receiver=shape+252, count at receiver0, sphere center at element0 and radius12;24-byte stride is larger than16-byte center/radius payload. Generic arithmetic accessor, not an allocation or ownership transfer.
int __thiscall rf_array24_get_element_address_unchecked(_DWORD *this, int a2)
{
  return *(this + 2) + 24 * a2;
}

