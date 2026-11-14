// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566B70 rf_model_container_get_reference_mesh_bounds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Corrected stale stdcall2args to ECX model-container record plus(outMin,outMax), RET8. Follows reference mesh pointer at144 (index36), obtains that mesh144 record LOD-table min/max through existing getters and copies them to outputs. No animation, aggregate traversal, index/null guard, or ownership changes. EAX final vector-copy bits.
int __thiscall rf_model_container_get_reference_mesh_bounds(void *this, float *destination, float *a3)
{
  float *lod_table_bounds_min; // eax
  float *lod_table_bounds_max; // eax
  float v7[3]; // [esp+4h] [ebp-30h] BYREF
  float v8[3]; // [esp+10h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-18h] BYREF
  float v10[3]; // [esp+28h] [ebp-Ch] BYREF

  lod_table_bounds_min = rf_model_mesh144_get_lod_table_bounds_min(*((_DWORD **)this + 36), v10);
  rf_vector_copy(destination, copy_result, lod_table_bounds_min);
  lod_table_bounds_max = rf_model_mesh144_get_lod_table_bounds_max(*((_DWORD **)this + 36), v8);
  return (int)rf_vector_copy(a3, v7, lod_table_bounds_max);
}

