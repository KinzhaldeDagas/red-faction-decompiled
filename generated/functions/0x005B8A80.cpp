// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8A80 rf_v3c_asset_base_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Calls base descriptor reset5B8AC0 and returns this. Does not allocate or initialize extended selected-mesh field+144.
_DWORD *__thiscall rf_v3c_asset_base_construct(_DWORD *this)
{
  rf_v3c_asset_base_reset(this);
  return this;
}

