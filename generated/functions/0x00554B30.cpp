// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554B30 rf_face_scale_vertices_about_corner_centroid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Computes arithmetic mean of corner vertex XYZ, then overwrites each referenced vertex position as center+scale*(position-center). Shared or repeated vertex pointers are modified directly; repeated references can be scaled repeatedly. Finalizes geometry and regenerates UVs, ignoring finalize status. Empty face still executes reciprocal/divide arithmetic with corner count0; no scale clamp.
void __stdcall rf_face_scale_vertices_about_corner_centroid(_DWORD *a1, float scalar)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v6; // [esp+8h] [ebp-6Ch]
  int v7; // [esp+Ch] [ebp-68h]
  int v8; // [esp+10h] [ebp-64h]
  float v9[3]; // [esp+18h] [ebp-5Ch] BYREF
  float sum_result[3]; // [esp+24h] [ebp-50h] BYREF
  float scaled_result[3]; // [esp+30h] [ebp-44h] BYREF
  float out_vector[3]; // [esp+3Ch] [ebp-38h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-2Ch] BYREF
  int v14[3]; // [esp+54h] [ebp-20h] BYREF
  int i; // [esp+60h] [ebp-14h]
  float rhs[3]; // [esp+64h] [ebp-10h] BYREF
  int v17; // [esp+70h] [ebp-4h]

  rf_vector3_default_construct_noop(rhs);
  rf_vector3_zero_return_destination(rhs);
  for ( i = a1[16]; i; i = v8 )
  {
    rf_vector_accumulate(rhs, *(float **)i);
    if ( *(_DWORD *)(i + 20) == a1[16] )
      v8 = 0;
    else
      v8 = *(_DWORD *)(i + 20);
  }
  v17 = rf_geomod_face_corner_count(a1);
  v6 = (float)v17;
  v2 = rf_vector_divide(rhs, (float *)v14, v6);
  rf_vector_copy(rhs, copy_result, v2);
  for ( i = a1[16]; i; i = v7 )
  {
    v3 = rf_vector_subtract(*(const float **)i, out_vector, rhs);
    v4 = rf_vector_multiply_scalar(v3, scaled_result, scalar);
    v5 = rf_vector_add(v4, sum_result, rhs);
    rf_vector_copy(*(float **)i, v9, v5);
    if ( *(_DWORD *)(i + 20) == a1[16] )
      v7 = 0;
    else
      v7 = *(_DWORD *)(i + 20);
  }
  rf_geomod_face_finalize_geometry((int)a1, nullptr, 0);
  rf_geomod_generated_uv_project((int)a1);
}

