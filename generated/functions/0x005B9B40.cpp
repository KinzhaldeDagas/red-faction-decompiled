// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9B40 sub_5B9B40
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: Static whole-model AABB initializes minimum=(FLT_MAX,...) and maximum=(FLT_MIN positive 1.1754944e-38,...), then unions raw LOD-table min/max of ALLmeshrecords. Therefore all-negative source maxima leave the positive minimum-normal float floor. Selecteddrop439220 reads spawnedmodel maximumX through564EC0/5628A0/tag1->this; no capsule, renderbounds or normalized dimensions substitution.
_DWORD *__thiscall sub_5B9B40(_DWORD *this, float *destination, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  _DWORD *result; // eax
  float *lod_table_bounds_min; // eax
  float *lod_table_bounds_max; // eax
  float v9[3]; // [esp+10h] [ebp-7Ch] BYREF
  float v10[3]; // [esp+1Ch] [ebp-70h] BYREF
  float v11[3]; // [esp+28h] [ebp-64h] BYREF
  float v12[3]; // [esp+34h] [ebp-58h] BYREF
  float v13[3]; // [esp+40h] [ebp-4Ch] BYREF
  float v14[3]; // [esp+4Ch] [ebp-40h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-34h] BYREF
  float v16[3]; // [esp+64h] [ebp-28h] BYREF
  int i; // [esp+70h] [ebp-1Ch]
  float v18[3]; // [esp+74h] [ebp-18h] BYREF
  float v19[3]; // [esp+80h] [ebp-Ch] BYREF

  v3 = rf_vector3_set_components_return_destination(v16, 3.4028235e38, 3.4028235e38, 3.4028235e38);
  rf_vector_copy(destination, copy_result, v3);
  v4 = rf_vector3_set_components_return_destination(v14, 1.1754944e-38, 1.1754944e-38, 1.1754944e-38);
  rf_vector_copy(a3, v13, v4);
  rf_vector3_default_construct_noop(v18);
  rf_vector3_default_construct_noop(v19);
  for ( i = 0; ; ++i )
  {
    result = this;
    if ( i >= *(this + 18) )
      break;
    lod_table_bounds_min = rf_model_mesh144_get_lod_table_bounds_min((_DWORD *)(*(this + 19) + 144 * i), v12);
    rf_vector_copy(v18, v11, lod_table_bounds_min);
    lod_table_bounds_max = rf_model_mesh144_get_lod_table_bounds_max((_DWORD *)(*(this + 19) + 144 * i), v10);
    rf_vector_copy(v19, v9, lod_table_bounds_max);
    rf_aabb_union_componentwise_in_place(destination, a3, v18, v19);
  }
  return result;
}

