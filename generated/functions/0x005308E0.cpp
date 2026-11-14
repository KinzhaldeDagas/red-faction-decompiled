// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005308E0 rf_geomod_face_finalize_geometry
// UNREALRED VERIFIED [ordered-boundary-20261028] With a nonnull source face (as both divider outputs use), copies its plane and visits EVERY circular corner to derive count/bounds. Requires >=3 corners and nonzero whole-loop signed area. It never prunes collinear shared vertices or imposes per-anchor-fan triangle validity. Host triangulation must preserve all ordered boundary segments on retained and generated operands; skipping a degenerate first fan triangle can silently erase an intermediate shared corner.
// UNREALRED VERIFIED [combat-native-planes-20261104]: Nonnull source plane is copied as all4float via513B70; neither normal normalization nor distance recomputation occurs. Null source uses ordered Newell sum and vertex-position sum, normalizes Newell, and computes d=-dot(sumPositions,Newell)*inverseLength/cornerCount: a centroid plane, not necessarily the first-vertex plane for nonplanar loops. Final admission requires>=3 corners and nonzero dot(accumulated fan-cross sum,stored normal), irrespective of whether the plane was copied or generated. Collinear early fan triangles do not justify removing shared corners.
char __thiscall rf_geomod_face_finalize_geometry(int this, float *a2, int a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  double v6; // st7
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  int v12; // [esp+10h] [ebp-11Ch]
  int v13; // [esp+14h] [ebp-118h]
  int v14; // [esp+18h] [ebp-114h]
  int v15; // [esp+1Ch] [ebp-110h]
  float v17[3]; // [esp+24h] [ebp-108h] BYREF
  float v18[3]; // [esp+30h] [ebp-FCh] BYREF
  float v19[3]; // [esp+3Ch] [ebp-F0h] BYREF
  float v20[3]; // [esp+48h] [ebp-E4h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-D8h] BYREF
  float v22[3]; // [esp+60h] [ebp-CCh] BYREF
  float v23[3]; // [esp+6Ch] [ebp-C0h] BYREF
  float v24[3]; // [esp+78h] [ebp-B4h] BYREF
  float scaled_result[3]; // [esp+84h] [ebp-A8h] BYREF
  _BYTE v26[16]; // [esp+90h] [ebp-9Ch] BYREF
  float copy_result[3]; // [esp+A0h] [ebp-8Ch] BYREF
  float v28[3]; // [esp+ACh] [ebp-80h] BYREF
  float v29[3]; // [esp+B8h] [ebp-74h] BYREF
  float v30[3]; // [esp+C4h] [ebp-68h] BYREF
  float v31[3]; // [esp+D0h] [ebp-5Ch] BYREF
  int v32; // [esp+DCh] [ebp-50h]
  float *source; // [esp+E0h] [ebp-4Ch]
  int j; // [esp+E4h] [ebp-48h]
  float v35; // [esp+E8h] [ebp-44h]
  int v36; // [esp+ECh] [ebp-40h]
  float scalar; // [esp+F0h] [ebp-3Ch]
  float *v38; // [esp+F4h] [ebp-38h]
  float *v39; // [esp+F8h] [ebp-34h]
  float *v40; // [esp+FCh] [ebp-30h]
  float *v41; // [esp+100h] [ebp-2Ch]
  int i; // [esp+104h] [ebp-28h]
  float destination; // [esp+108h] [ebp-24h] BYREF
  float v44; // [esp+10Ch] [ebp-20h]
  float v45; // [esp+110h] [ebp-1Ch]
  int v46; // [esp+114h] [ebp-18h]
  float v47; // [esp+118h] [ebp-14h]
  float v48[3]; // [esp+11Ch] [ebp-10h] BYREF
  char v49; // [esp+12Bh] [ebp-1h]

  v49 = 1;
  if ( a2 )
  {
    rf_plane_copy((float *)this, a2);
  }
  else
  {
    rf_vector3_default_construct_noop(v48);
    rf_vector3_default_construct_noop(&destination);
    rf_vector3_zero_return_destination(v48);
    rf_vector3_zero_return_destination(&destination);
    v46 = 0;
    for ( i = *(_DWORD *)(this + 64); i; i = v15 )
    {
      v40 = *(float **)i;
      v38 = **(float ***)(i + 20);
      v39 = v40;
      v41 = v38;
      destination = (v40[1] - v38[1]) * (v40[2] + v38[2]) + destination;
      v44 = (v40[2] - v38[2]) * (*v40 + *v38) + v44;
      v45 = (*v40 - *v38) * (v40[1] + v38[1]) + v45;
      rf_vector_accumulate(v48, v40);
      ++v46;
      if ( *(_DWORD *)(i + 20) == *(_DWORD *)(this + 64) )
        v15 = 0;
      else
        v15 = *(_DWORD *)(i + 20);
    }
    v47 = rf_vector3_length(&destination);
    if ( v47 == 0.0 )
    {
      v49 = 0;
      v3 = rf_vector3_set_components_return_destination(v28, 1.0, 0.0, 0.0);
      rf_vector_copy(&destination, copy_result, v3);
      v4 = (float *)rf_plane_construct_from_normal_point(v26, &destination, **(_DWORD **)(this + 64));
      rf_plane_copy((float *)this, v4);
    }
    else
    {
      scalar = 1.0 / rf_vector3_length(&destination);
      v5 = rf_vector_multiply_scalar(&destination, scaled_result, scalar);
      rf_vector_copy((float *)this, v24, v5);
      v6 = rf_vector_dot(v48, &destination);
      *(float *)(this + 12) = -v6 * scalar / (double)v46;
    }
  }
  v36 = 0;
  for ( j = *(_DWORD *)(this + 64); j; j = v14 )
  {
    source = *(float **)j;
    if ( v36 )
    {
      *(float *)(this + 16) = rf_float_minimum_two_values(*source, *(float *)(this + 16));
      *(float *)(this + 20) = rf_float_minimum_two_values(source[1], *(float *)(this + 20));
      *(float *)(this + 24) = rf_float_minimum_two_values(source[2], *(float *)(this + 24));
      *(float *)(this + 28) = rf_float_maximum_two_values(*source, *(float *)(this + 28));
      *(float *)(this + 32) = rf_float_maximum_two_values(source[1], *(float *)(this + 32));
      *(float *)(this + 36) = rf_float_maximum_two_values(source[2], *(float *)(this + 36));
    }
    else
    {
      rf_vector_copy((float *)(this + 16), v23, source);
      rf_vector_copy((float *)(this + 28), v22, source);
    }
    ++v36;
    if ( *(_DWORD *)(j + 20) == *(_DWORD *)(this + 64) )
      v14 = 0;
    else
      v14 = *(_DWORD *)(j + 20);
  }
  rf_vector3_subtract_scalar_in_place((float *)(this + 16), 0.000099999997);
  rf_vector3_add_scalar_in_place((float *)(this + 28), 0.000099999997);
  v35 = 0.0;
  if ( v36 >= 3 )
  {
    rf_vector3_set_components_return_destination(v31, 0.0, 0.0, 0.0);
    v32 = *(_DWORD *)(this + 64);
    if ( *(_DWORD *)(v32 + 20) == *(_DWORD *)(this + 64) )
      v13 = 0;
    else
      v13 = *(_DWORD *)(v32 + 20);
    for ( j = v13; *(_DWORD *)(j + 20) == *(_DWORD *)(this + 64) ? 0 : *(_DWORD *)(j + 20); j = v12 )
    {
      rf_vector3_default_construct_noop(v30);
      rf_vector3_default_construct_noop(v29);
      v7 = rf_vector_subtract(*(const float **)j, out_vector, *(const float **)v32);
      rf_vector_copy(v30, v20, v7);
      v8 = rf_vector_subtract(**(const float ***)(j + 20), v19, *(const float **)v32);
      rf_vector_copy(v29, v18, v8);
      v9 = rf_vector_cross(v30, v17, v29);
      rf_vector_accumulate(v31, v9);
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(this + 64) )
        v12 = 0;
      else
        v12 = *(_DWORD *)(j + 20);
    }
    v35 = rf_vector_dot((float *)this, v31);
  }
  if ( v35 == 0.0 )
    return 0;
  return v49;
}

