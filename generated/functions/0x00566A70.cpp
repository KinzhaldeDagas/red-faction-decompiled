// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566A70 rf_model_mesh144_get_lod_table_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Thiscall mesh144,output vector. Copies three floats from pointer at mesh+140,offset+28 into output,returns output. This is LOD-table header translation,not mesh record inline coordinates. No NULL/count/selected-LOD guard.
float *__thiscall rf_model_mesh144_get_lod_table_translation(_DWORD *this, float *a2)
{
  rf_vector3_copy_return_destination(a2, (float *)(*(this + 35) + 28));
  return a2;
}

