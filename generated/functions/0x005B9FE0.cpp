// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9FE0 rf_v3c_asset_base_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Calls base descriptor destructor5B8AA0 to release owned arrays. If flag byte bit1 set, operator delete receiver; returns original pointer bits even after free. Other flags ignored. No vector-array cookie behavior or extended selected-mesh+144 handling.
void *__thiscall rf_v3c_asset_base_scalar_deleting_destructor(void *this, char a2)
{
  rf_v3c_asset_base_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

