// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E910 rf_dword_array_construct_zero_capacity_51e910
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall no stack args:delegates dynamic DWORD-array constructor with capacity0,returns receiver. Initializes ordinary empty12-byte header through helper,no element objects or owner registration. Used for primitive row arrays and solid+768;does not allocate caller object or initialize surrounding fields.
void *__thiscall rf_dword_array_construct_zero_capacity_51e910(void *this)
{
  rf_dword_array_construct_capacity(this, 0);
  return this;
}

