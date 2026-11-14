// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588880 rf_v3c_asset148_release_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Thiscall wrapper forwarding to base owned-array release5B8BA0. Does not itself reset descriptor counts/name or selected-mesh pointer+144.
int __thiscall rf_v3c_asset148_release_arrays(void *this)
{
  return rf_v3c_asset_release_owned_arrays((int)this);
}

