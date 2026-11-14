// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8D70 rf_v3c_asset_get_mesh_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Returns descriptor DWORD+72 unchanged as integer. Used as144-byte mesh array count by static collision wrapper;does not check allocation pointer+76,loaded mesh count+80 or positive range. Replaces generic library name;no mutation.
int __thiscall rf_v3c_asset_get_mesh_count(_DWORD *this)
{
  return *(this + 18);
}

