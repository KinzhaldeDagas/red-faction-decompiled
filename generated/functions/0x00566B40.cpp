// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566B40 rf_model_mesh144_get_lod_table_bounds_max
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Copies vector from mesh.LODtable(+140)+56 to output,returns output. No radius expansion or selected-LOD-specific recomputation. No NULL or min<=max validation.
float *__thiscall rf_model_mesh144_get_lod_table_bounds_max(_DWORD *this, float *a2)
{
  rf_vector3_copy_return_destination(a2, (float *)(*(this + 35) + 56));
  return a2;
}

