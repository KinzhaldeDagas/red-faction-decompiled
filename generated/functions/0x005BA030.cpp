// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA030 rf_v3c_asset_test_flag1
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Returns descriptor DWORD+140 AND1 as integer0/1. Does not read mesh arrays or mutate state; no NULL guard. Paired with setter5BA010.
int __thiscall rf_v3c_asset_test_flag1(_DWORD *this)
{
  return *(this + 35) & 1;
}

