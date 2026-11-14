// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507AA0 rf_embedded_vector12_matrix24_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Thiscall receiver,no stack arguments,returns receiver. Calls no-write vector default at+12 then no-write matrix constructor+24 (three no-write rows). Does not write first12bytes, position/basis, active byte, links, handles or any component; no identity/zero initialization or allocation. Static callbacks62D490/62D4A0 use this for VClip sentinel72 and128 runtime records stride72; other existing engine callers also share it.
char *__thiscall rf_embedded_vector12_matrix24_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 12);
  rf_matrix3_construct(this + 24);
  return this;
}

