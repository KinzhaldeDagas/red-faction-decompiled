// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A0C0 rf_v3c_asset148_construct_base
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Calls base V3C descriptor constructor5B8A80 on this. Base reset touches first byte and DWORDs68..140; extended selected-mesh pointer+144 is NOT initialized here. Character header reset separately clears that pointer via588860.
void __thiscall rf_v3c_asset148_construct_base(_DWORD *this)
{
  rf_v3c_asset_base_construct(this);
}

