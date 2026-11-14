// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005822D0 rf_vector_prefix_at4_construct_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Calls no-op vector-prefix constructor491340 on receiver+4,returns receiver. No bytes initialized,including firstDWORD. Referenced by static initializer callbacks62E4C3/62E523;exact original aggregate class/total size unproven. Not a matrix/plane identity initializer.
int __thiscall rf_vector_prefix_at4_construct_noop(int this)
{
  rf_vector_prefix_construct_noop((void *)(this + 4));
  return this;
}

