// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C8BD0 rf_clip_polygon_against_plane
// UNREALRED VERIFIED [projected-shadow-receiver-20260903]: Clips one cyclic 3D polygon against one 16-byte plane. It retains vertices on the classifier's accepted side and linearly inserts an intersection vertex whenever an edge crosses the plane, returning the new vertex count.
int __cdecl rf_clip_polygon_against_plane(int a1, int a2, int a3, float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float scalar; // [esp+0h] [ebp-64h]
  float v9[3]; // [esp+4h] [ebp-60h] BYREF
  float sum_result[3]; // [esp+10h] [ebp-54h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-48h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+34h] [ebp-30h] BYREF
  float v14; // [esp+40h] [ebp-24h]
  float v15; // [esp+44h] [ebp-20h]
  float v16; // [esp+48h] [ebp-1Ch]
  BOOL v17; // [esp+4Ch] [ebp-18h]
  BOOL v18; // [esp+50h] [ebp-14h]
  int v19; // [esp+54h] [ebp-10h]
  int v20; // [esp+58h] [ebp-Ch]
  int v21; // [esp+5Ch] [ebp-8h]
  int v22; // [esp+60h] [ebp-4h]

  v21 = 0;
  v20 = 1;
  v19 = 0;
  while ( v21 < a1 )
  {
    v22 = rf_plane_classify_point_offset_epsilon(a4, (float *)(a2 + 12 * v21), 0.0);
    v17 = v22 != 1;
    v22 = rf_plane_classify_point_offset_epsilon(a4, (float *)(a2 + 12 * v20), 0.0);
    v18 = v22 != 1;
    if ( v17 )
      rf_vector_copy((float *)(a3 + 12 * v19++), copy_result, (const float *)(a2 + 12 * v21));
    if ( v17 && !v18 || !v17 && v18 )
    {
      v15 = -rf_vector_dot((float *)(a2 + 12 * v21), a4);
      v16 = -rf_vector_dot((float *)(a2 + 12 * v20), a4);
      v14 = (a4[3] - v15) / (v16 - v15);
      scalar = v14;
      v4 = rf_vector_subtract((const float *)(a2 + 12 * v20), out_vector, (const float *)(a2 + 12 * v21));
      v5 = rf_vector_multiply_scalar(v4, scaled_result, scalar);
      v6 = rf_vector_add((const float *)(a2 + 12 * v21), sum_result, v5);
      rf_vector_copy((float *)(a3 + 12 * v19++), v9, v6);
    }
    ++v21;
    if ( ++v20 == a1 )
      v20 = 0;
  }
  return v19;
}

