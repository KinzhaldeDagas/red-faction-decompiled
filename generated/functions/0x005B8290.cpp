// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8290 rf_model_mesh144_destroy_lod_table
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): If mesh DWORD+140 is non-NULL, calls rf_model_geometry_destroy_lod_table. Does not NULL the pointer or free containing144-byte mesh record. Used by scalar/vector deleting destructor589DD0.
void __thiscall rf_model_mesh144_destroy_lod_table(_DWORD *this)
{
  if ( *(this + 35) )
    rf_model_geometry_destroy_lod_table((_DWORD *)*(this + 35));
}

