// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005526C0 rf_face_interpolate_incident_normals_in_fan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Cdecl face,queryXYZ,outputNormal3f. Selects face projection axes,collects corner vertex pointers into fixed local array without capacity check,then tests fan triangles(0,k-1,k),k starting2 in a DO loop. Computes barycentric coefficients in projected2D;alternate formula when abs(first edge U)<~1e-4,but no general determinant/divisor guard. First triangle with coefficients>=0 and sum<=1 wins;no plane-distance/concavity test. Fewer than3 corners still attempts initial triangle,invalid inputs not rejected safely. On hit,for three winning vertices sums normals(first3floats) of EVERY incident face in vertex+32 pointer array,equal weight/no flag/material/smoothing-angle filter;normalizes sum through559300
// (zero/NaN sum falls backunitX). Barycentrically interpolates these three normals to output,DOES NOT normalize final interpolation. Returns true;no containing fan triangle returns false and leaves output unchanged. Fixed25 normal-vector slots,no polygon vertex-count guard.
bool __cdecl rf_face_interpolate_incident_normals_in_fan(int a1, int a2, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v7; // [esp+Ch] [ebp-268h]
  float *v8; // [esp+14h] [ebp-260h]
  _DWORD *v9; // [esp+18h] [ebp-25Ch]
  bool v10; // [esp+1Ch] [ebp-258h]
  bool v11; // [esp+20h] [ebp-254h]
  _DWORD *v12; // [esp+24h] [ebp-250h]
  float v13[3]; // [esp+28h] [ebp-24Ch] BYREF
  float v14[3]; // [esp+34h] [ebp-240h] BYREF
  int v15[3]; // [esp+40h] [ebp-234h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-228h] BYREF
  int v17[3]; // [esp+58h] [ebp-21Ch] BYREF
  int v18[3]; // [esp+64h] [ebp-210h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-204h] BYREF
  float *v20; // [esp+7Ch] [ebp-1F8h]
  int k; // [esp+80h] [ebp-1F4h]
  int first_dword; // [esp+84h] [ebp-1F0h]
  float source[3]; // [esp+88h] [ebp-1ECh] BYREF
  _DWORD *j; // [esp+94h] [ebp-1E0h]
  float v25; // [esp+98h] [ebp-1DCh]
  float destination[76]; // [esp+9Ch] [ebp-1D8h] BYREF
  float v27; // [esp+1CCh] [ebp-A8h]
  float v28; // [esp+1D0h] [ebp-A4h]
  float v29; // [esp+1D4h] [ebp-A0h]
  int v30; // [esp+1D8h] [ebp-9Ch] BYREF
  _DWORD *i; // [esp+1DCh] [ebp-98h]
  float v32; // [esp+1E0h] [ebp-94h]
  float v33; // [esp+1E4h] [ebp-90h]
  int v34; // [esp+1E8h] [ebp-8Ch] BYREF
  int v35; // [esp+1ECh] [ebp-88h]
  int v36; // [esp+1F0h] [ebp-84h] BYREF
  _DWORD v37[26]; // [esp+1F4h] [ebp-80h]
  float v38; // [esp+25Ch] [ebp-18h]
  bool v39; // [esp+263h] [ebp-11h]
  float v40; // [esp+264h] [ebp-10h]
  float v41; // [esp+268h] [ebp-Ch]
  int v42; // [esp+26Ch] [ebp-8h]
  float v43; // [esp+270h] [ebp-4h]

  rf_face_projection_axes_select((float *)a1, &v36, &v30, &v34);
  v35 = 0;
  for ( i = *(_DWORD **)(a1 + 64); i; i = v12 )
  {
    v37[v35++] = *i;
    if ( i[5] == *(_DWORD *)(a1 + 64) )
      v12 = nullptr;
    else
      v12 = (_DWORD *)i[5];
  }
  v43 = 0.0;
  v33 = 0.000099999997;
  v39 = 0;
  v42 = 2;
  v40 = *(float *)(a2 + 4 * v30) - *(float *)(v37[0] + 4 * v30);
  v29 = *(float *)(a2 + 4 * v34) - *(float *)(v37[0] + 4 * v34);
  do
  {
    v27 = *(float *)(v37[v42 - 1] + 4 * v30) - *(float *)(v37[0] + 4 * v30);
    v32 = *(float *)(v37[v42] + 4 * v30) - *(float *)(v37[0] + 4 * v30);
    v41 = *(float *)(v37[v42 - 1] + 4 * v34) - *(float *)(v37[0] + 4 * v34);
    v38 = *(float *)(v37[v42] + 4 * v34) - *(float *)(v37[0] + 4 * v34);
    if ( v27 <= -v33 || v33 <= (double)v27 )
    {
      v28 = (v29 * v27 - v40 * v41) / (v38 * v27 - v32 * v41);
      if ( v28 >= 0.0 && v28 <= 1.0 )
      {
        v43 = (v40 - v28 * v32) / v27;
        v10 = v43 >= 0.0 && v43 + v28 <= 1.0;
        v39 = v10;
      }
    }
    else
    {
      v28 = v40 / v32;
      if ( v28 >= 0.0 && v28 <= 1.0 )
      {
        v43 = (v29 - v28 * v38) / v41;
        v11 = v43 >= 0.0 && v43 + v28 <= 1.0;
        v39 = v11;
      }
    }
    if ( v39 )
      break;
    ++v42;
  }
  while ( v42 < v35 );
  if ( v39 )
  {
    v35 = 0;
    rf_vector_construct_no_unwind((char *)destination, 0xCu, 25, rf_vector3_default_construct_noop);
    for ( j = *(_DWORD **)(a1 + 64); j; j = v9 )
    {
      if ( !v35 || v35 == v42 - 1 || v35 == v42 )
      {
        rf_vector3_default_construct_noop(source);
        rf_vector3_zero_return_destination(source);
        first_dword = rf_receiver_get_first_dword((void *)(*j + 32));
        for ( k = 0; k < first_dword; ++k )
        {
          v20 = *(float **)sub_552200((_DWORD *)(*j + 32), k);
          rf_vector_accumulate(source, v20);
        }
        rf_vector_normalize(source);
        rf_vector_copy(&destination[3 * v35], copy_result, source);
      }
      ++v35;
      if ( j[5] == *(_DWORD *)(a1 + 64) )
        v9 = nullptr;
      else
        v9 = (_DWORD *)j[5];
    }
    v25 = 1.0 - (v43 + v28);
    v8 = rf_vector_scale((float *)v15, v28, &destination[3 * v42]);
    v7 = rf_vector_scale((float *)v17, v43, &destination[3 * v42 - 3]);
    v3 = rf_vector_scale((float *)v18, v25, destination);
    v4 = rf_vector_add(v3, sum_result, v7);
    v5 = rf_vector_add(v4, v14, v8);
    rf_vector_copy(a3, v13, v5);
  }
  return v39;
}

