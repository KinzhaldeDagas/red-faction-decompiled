// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005628A0 rf_model_handle_get_indexed_bounds_aabb
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 ignores index and copies referenced mesh LOD-table bounds from definition8+6592 via corrected thiscall566B70; static definition bounds, not animated skeletal pose. Tag1 index-1 delegates5B9B40; indexed path follows instance84+100*index+4 mesh pointer then copies LOD min/max. This indexed table differs from144byte table used by sphere getter. Tag3 gets sphere into temporary center/radius, DISCARDS center, writes max=(r,r,r),min=-max, so scene AABB is always cube centered ORIGIN even for nonorigin node center. Unsupported tags leave outputs unchanged; no index/radius/finite validation, return incidental helper bits.
float *__thiscall rf_model_handle_get_indexed_bounds_aabb(float *this, int a2, float *destination, float *vector)
{
  float *result; // eax
  float *lod_table_bounds_min; // eax
  float *lod_table_bounds_max; // eax
  float *v7; // eax
  float v9[3]; // [esp+10h] [ebp-58h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-4Ch] BYREF
  float v11[3]; // [esp+28h] [ebp-40h] BYREF
  float v12[3]; // [esp+34h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-28h] BYREF
  float v14[3]; // [esp+4Ch] [ebp-1Ch] BYREF
  float v15; // [esp+58h] [ebp-10h] BYREF
  float v16[3]; // [esp+5Ch] [ebp-Ch] BYREF

  result = this;
  switch ( *(_DWORD *)this )
  {
    case 2:
      return (float *)rf_model_container_get_reference_mesh_bounds(
                        (void *)(*((_DWORD *)this + 2) + 6592),
                        destination,
                        vector);
    case 1:
      if ( a2 == -1 )
      {
        return (float *)sub_5B9B40(*((_DWORD **)this + 1), destination, vector);
      }
      else
      {
        lod_table_bounds_min = rf_model_mesh144_get_lod_table_bounds_min(
                                 *(_DWORD **)(*(_DWORD *)(*((_DWORD *)this + 1) + 84) + 100 * a2 + 4),
                                 v14);
        rf_vector_copy(destination, copy_result, lod_table_bounds_min);
        lod_table_bounds_max = rf_model_mesh144_get_lod_table_bounds_max(
                                 *(_DWORD **)(*(_DWORD *)(*((_DWORD *)this + 1) + 84) + 100 * a2 + 4),
                                 v12);
        return rf_vector_copy(vector, v11, lod_table_bounds_max);
      }
    case 3:
      rf_vector3_default_construct_noop(v16);
      rf_model_handle_get_indexed_bounds_sphere(this, a2, v16, &v15);
      rf_vector3_set_components_thiscall(vector, 1.0, 1.0, 1.0);
      rf_vector3_scale_in_place_return_self(vector, v15);
      v7 = rf_vector_multiply_scalar(vector, scaled_result, -1.0);
      return rf_vector_copy(destination, v9, v7);
  }
  return result;
}

