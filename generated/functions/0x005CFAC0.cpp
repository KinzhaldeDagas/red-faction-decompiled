// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CFAC0 rf_collision_test_skinned_triangle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl opaque hitTag,three vertices,query,hit,precomputed broadphase endpoint. Builds triangle AABB,expands by radius,tests working start->endpoint. Computes oriented triangle cross,backface rejects dot(delta,cross)>0;no two-sided flag path. Normalizes normal/builds plane. Radius>0.025: one-sided sphere-plane sweep;INSIDE triangle acceptance overwrites hit fraction/point/normal/tag WITHOUT comparing existing best fraction. Thus later farther face can replace nearer hit (outer endpoint is not recomputed). Outside triangle invokes polygon-edge sweep and requires strict closer result;stores FACE normal even for edge contact. Radius<=0.025: front-plane/triangle segment helper plus strict closer check. Both reject misses with no hit reset.
// Degenerate triangle/radius/normal/pointer validation absent;equal-time ray/edge candidates do not replace.
char __cdecl rf_collision_test_skinned_triangle(
        unsigned int a1,
        const float *a2,
        const float *a3,
        const float *a4,
        void *a5,
        void *a6,
        const float *a7)
{
  float v8[3]; // [esp+10h] [ebp-CCh] BYREF
  float v9[3]; // [esp+1Ch] [ebp-C0h] BYREF
  float v10[3]; // [esp+28h] [ebp-B4h] BYREF
  float v11[3]; // [esp+34h] [ebp-A8h] BYREF
  float v12[3]; // [esp+40h] [ebp-9Ch] BYREF
  float v13[3]; // [esp+4Ch] [ebp-90h] BYREF
  float v14[3]; // [esp+58h] [ebp-84h] BYREF
  float copy_result[3]; // [esp+64h] [ebp-78h] BYREF
  float destination[3]; // [esp+70h] [ebp-6Ch] BYREF
  float v17[3]; // [esp+7Ch] [ebp-60h] BYREF
  bool v18; // [esp+8Bh] [ebp-51h]
  float source[3]; // [esp+8Ch] [ebp-50h] BYREF
  float v20[3]; // [esp+98h] [ebp-44h] BYREF
  float v21[3]; // [esp+A4h] [ebp-38h] BYREF
  int v22; // [esp+B0h] [ebp-2Ch] BYREF
  float *v23; // [esp+B4h] [ebp-28h] BYREF
  float *v24; // [esp+B8h] [ebp-24h]
  float *v25; // [esp+BCh] [ebp-20h]
  float v26[3]; // [esp+C0h] [ebp-1Ch] BYREF
  int v27[4]; // [esp+CCh] [ebp-10h] BYREF

  rf_vector3_default_construct_noop(source);
  rf_vector3_default_construct_noop(v21);
  rf_vector3_default_construct_noop(v20);
  rf_segment_bounds_build(v21, v20, (float *)a2, (float *)a3);
  rf_aabb_include_point_min_else_max(v21, v20, (float *)a4);
  rf_vector3_subtract_scalar_in_place(v21, *((float *)a5 + 18));
  rf_vector3_add_scalar_in_place(v20, *((float *)a5 + 18));
  if ( !rf_segment_intersects_aabb(v21, v20, (float *)a5 + 20, (float *)a7, source) )
    return 0;
  v23 = (float *)a2;
  v24 = (float *)a3;
  v25 = (float *)a4;
  v18 = *((float *)a5 + 18) > 0.02500000037252903;
  rf_vector3_default_construct_noop(v26);
  rf_triangle_cross_from_three_points(v26, v23, v24, v25);
  if ( rf_vector_dot((float *)a5 + 23, v26) > 0.0 )
    return 0;
  rf_vector_normalize(v26);
  rf_plane_construct_from_normal_point(v27, v26, (int)a2);
  if ( v18 )
  {
    if ( rf_swept_sphere_front_plane_contact(
           (float *)a5 + 20,
           (float *)a5 + 23,
           *((float *)a5 + 18),
           (float *)v27,
           (float *)&v22,
           source) )
    {
      if ( rf_polygon_point_inside_projected_triangle_fan((int)source, 3, (int *)&v23, v26) )
      {
        *(float *)a6 = *(float *)&v22;
        rf_vector_copy((float *)a6 + 1, v11, source);
        rf_vector_copy((float *)a6 + 4, v10, v26);
        *((_DWORD *)a6 + 7) = a1;
        return 1;
      }
      else if ( rf_swept_sphere_polygon_edge_contacts(
                  source,
                  (float *)a5 + 20,
                  (float *)a5 + 23,
                  *((float *)a5 + 18),
                  3,
                  (const float **)&v23,
                  (float *)&v22)
             && *(float *)a6 > (double)*(float *)&v22 )
      {
        *(float *)a6 = *(float *)&v22;
        rf_vector_copy((float *)a6 + 1, v9, source);
        rf_vector_copy((float *)a6 + 4, v8, v26);
        *((_DWORD *)a6 + 7) = a1;
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    rf_force_sample44_construct_vectors_noop((char *)destination);
    rf_vector_copy(destination, copy_result, (const float *)a5 + 20);
    rf_vector_copy(v17, v14, (const float *)a5 + 23);
    if ( rf_segment_triangle_intersect_front_plane(destination, (int *)&v23, (float *)v27, source, (float *)&v22)
      && *(float *)a6 > (double)*(float *)&v22 )
    {
      *(float *)a6 = *(float *)&v22;
      rf_vector_copy((float *)a6 + 1, v13, source);
      rf_vector_copy((float *)a6 + 4, v12, v26);
      *((_DWORD *)a6 + 7) = a1;
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

