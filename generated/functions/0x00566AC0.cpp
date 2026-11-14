// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566AC0 rf_model_container_get_reference_mesh_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX model-container record plus(outCenter,outRadius), RET8. Follows reference mesh pointer at144, copies referenced mesh144 LOD-table translation through getter, then reads radius via566AA0. No current pose/scale transform, bounds recomputation or validity checks. Saved return void.
void __thiscall rf_model_container_get_reference_mesh_sphere(_DWORD *this, float *destination, float *a3)
{
  float *lod_table_translation; // eax
  float copy_result[3]; // [esp+4h] [ebp-18h] BYREF
  float v6[3]; // [esp+10h] [ebp-Ch] BYREF

  lod_table_translation = rf_model_mesh144_get_lod_table_translation((_DWORD *)*(this + 36), v6);
  rf_vector_copy(destination, copy_result, lod_table_translation);
  *a3 = rf_mesh144_get_lod_table_radius((_DWORD *)*(this + 36));
}

