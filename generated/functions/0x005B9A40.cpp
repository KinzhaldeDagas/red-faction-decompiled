// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9A40 rf_mesh_collection_aggregate_bounds_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX mesh collection,count72,records76 stride144. Center is arithmetic mean of every LOD-table translation, then radius=max(length(center-recordCenter)+recordRadius). Initializes center0/radius0 but UNCONDITIONALLY divides center by count, so empty collection performs reciprocal0 and can output NaN center. Radius stays0 for empty loop. Not minimum enclosing sphere; no per-mesh transform, count/finite checks or allocation. EAX final count bookkeeping.
int __thiscall rf_mesh_collection_aggregate_bounds_sphere(_DWORD *this, float *lhs, float *a3)
{
  float *lod_table_translation; // eax
  int result; // eax
  float *v5; // eax
  float *v6; // eax
  float v7; // [esp+8h] [ebp-3Ch]
  double v8; // [esp+Ch] [ebp-38h]
  float v9; // [esp+14h] [ebp-30h]
  float out_vector[3]; // [esp+1Ch] [ebp-28h] BYREF
  float v12[3]; // [esp+28h] [ebp-1Ch] BYREF
  float v13[3]; // [esp+34h] [ebp-10h] BYREF
  int i; // [esp+40h] [ebp-4h]

  rf_vector3_zero_return_destination(lhs);
  *a3 = 0.0;
  for ( i = 0; i < *(this + 18); ++i )
  {
    lod_table_translation = rf_model_mesh144_get_lod_table_translation((_DWORD *)(*(this + 19) + 144 * i), v13);
    rf_vector_accumulate(lhs, lod_table_translation);
  }
  v9 = 1.0 / (double)(int)*(this + 18);
  rf_vector3_scale_in_place_return_self(lhs, v9);
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(this + 18) )
      break;
    v5 = rf_model_mesh144_get_lod_table_translation((_DWORD *)(*(this + 19) + 144 * i), v12);
    v6 = rf_vector_subtract(lhs, out_vector, v5);
    v8 = rf_vector3_length(v6);
    v7 = rf_mesh144_get_lod_table_radius((_DWORD *)(*(this + 19) + 144 * i)) + v8;
    *a3 = rf_float_maximum_two_values(*a3, v7);
  }
  return result;
}

