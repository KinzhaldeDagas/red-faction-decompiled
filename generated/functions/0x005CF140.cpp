// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF140 rf_collision_static_triangle_ray
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Batch plane from pointer+16+16*triangleIndex,index record from+20+8*index,vertex array+4. If dot(workingDelta,normal)>0,requires two-sided flag then reverses plane;dot0 proceeds to segment-plane helper,which rejects exact denominator0. Helper writes contact/fraction and requires fraction[0,1]. Rejects candidate when existing hit.fraction<=candidate,so equal-distance hits never replace. Reads three SIGNED16 vertex indices,performs projected triangle containment. On acceptance stores fraction,point,plane normal,triangle-record pointer tag+28. Geometry argument unused. No epsilon-parallel,vertex/index/plane validity or output reset here.
char __cdecl rf_collision_static_triangle_ray(int a1, _DWORD *a2, int a3, int a4, int a5, int a6)
{
  float v7[3]; // [esp+0h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-40h] BYREF
  int v9; // [esp+18h] [ebp-34h]
  float source[3]; // [esp+1Ch] [ebp-30h] BYREF
  float v11; // [esp+28h] [ebp-24h]
  __int16 *v12; // [esp+2Ch] [ebp-20h]
  int v13[3]; // [esp+30h] [ebp-1Ch] BYREF
  float v14[4]; // [esp+3Ch] [ebp-10h] BYREF

  rf_vector_prefix_construct_noop(source);
  rf_plane4_copy_normal_scalar(v14, (float *)(a2[4] + 16 * a3));
  v12 = (__int16 *)(a2[5] + 8 * a3);
  v9 = a2[1];
  if ( rf_vector_dot((float *)(a4 + 92), v14) > 0.0 )
  {
    if ( !a6 )
      return 0;
    rf_geomod_face_plane_reverse(v14);
  }
  if ( !rf_segment_plane_intersection_point_fraction(source, (float *)(a4 + 80), (float *)(a4 + 92), v14) )
    return 0;
  if ( *(float *)a5 <= (double)v11 )
    return 0;
  v13[0] = v9 + 12 * *v12;
  v13[1] = v9 + 12 * v12[1];
  v13[2] = v9 + 12 * v12[2];
  if ( !rf_polygon_point_inside_projected_triangle_fan((int)source, 3, v13, v14) )
    return 0;
  *(float *)a5 = v11;
  rf_vector_copy((float *)(a5 + 4), copy_result, source);
  rf_vector_copy((float *)(a5 + 16), v7, v14);
  *(_DWORD *)(a5 + 28) = v12;
  return 1;
}

