// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8AA0 rf_v3c_asset_base_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Thiscall no-stack-argument wrapper calling owned-array release5B8BA0. Does not free containing descriptor or reset scalar counts.
int __thiscall rf_v3c_asset_base_destroy(void *this)
{
  return rf_v3c_asset_release_owned_arrays((int)this);
}

