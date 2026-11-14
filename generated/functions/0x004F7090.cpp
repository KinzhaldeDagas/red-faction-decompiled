// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7090 rf_level_snapshot_bounds_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Invoke no-op default vector constructors at level snapshot+40/+52 only. Does not zero snapshot bounds or initialize record counts/name/size fields.
int __thiscall rf_level_snapshot_bounds_construct(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 40));
  rf_vector3_default_construct_noop((void *)(this + 52));
  return this;
}

