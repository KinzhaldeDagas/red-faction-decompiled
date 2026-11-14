// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566B10 rf_model_mesh144_get_lod_table_bounds_min
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Copies vector from mesh.LODtable(+140)+44 to output,returns output. No radius expansion,normalization or selected-LOD-specific recomputation. Used by static collision broadphase;no pointer validity checks.
float *__thiscall rf_model_mesh144_get_lod_table_bounds_min(_DWORD *this, float *a2)
{
  rf_vector3_copy_return_destination(a2, (float *)(*(this + 35) + 44));
  return a2;
}

