// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA010 rf_v3c_asset_set_flag1
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): ORs bit0 into descriptor DWORD+140 and returns receiver; no allocation or buffer validation. Retained-by-cache semantics verified here:5B9E00 keeps records with this flag set; marking does not increment a reference count.
_DWORD *__thiscall rf_v3c_asset_set_flag1(_DWORD *this)
{
  *(this + 35) |= 1u;
  return this;
}

