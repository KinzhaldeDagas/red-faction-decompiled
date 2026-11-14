// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A0E0 rf_v3c_asset148_destroy_base
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Calls base descriptor destructor5B8AA0, which releases owned arrays. Does not separately clear extended selected-mesh pointer+144 or free containing record.
void __thiscall rf_v3c_asset148_destroy_base(void *this)
{
  rf_v3c_asset_base_destroy(this);
}

