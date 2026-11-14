// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF280 rf_collision_static_triangle_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Loads indexed plane/three signed16 vertex indices. Dot(delta,normal)>=0 requires two-sided flag and plane reversal (stricter parallel test than ray path). Sphere-plane sweep56A420 must succeed;candidate t must be STRICTLY less than current hit before polygon test. Inside projected triangle stores t/contact/plane normal/triangle pointer. Otherwise tests polygon boundary edges56AA00;closer edge result stores normalized(start-contact) as hit normal,NOT sphere center-at-impact minus contact. No independent radius/count/pointer validation,rollback or world-space conversion. Geometry argument unused.
char __cdecl rf_collision_static_triangle_sphere(int a1, _DWORD *a2, int a3, float *a4, int a5, int a6)
{
  float *v7; // eax
  float v8[3]; // [esp+10h] [ebp-78h] BYREF
  float out_vector[3]; // [esp+1Ch] [ebp-6Ch] BYREF
  float v10[3]; // [esp+28h] [ebp-60h] BYREF
  float v11[3]; // [esp+34h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-48h] BYREF
  int v13; // [esp+4Ch] [ebp-3Ch]
  char v14; // [esp+53h] [ebp-35h]
  float rhs[3]; // [esp+54h] [ebp-34h] BYREF
  __int16 *v16; // [esp+60h] [ebp-28h]
  int v17; // [esp+64h] [ebp-24h] BYREF
  int v18[3]; // [esp+68h] [ebp-20h] BYREF
  float source[4]; // [esp+74h] [ebp-14h] BYREF
  char v20; // [esp+87h] [ebp-1h]

  rf_vector3_default_construct_noop(rhs);
  v16 = (__int16 *)(a2[5] + 8 * a3);
  rf_plane4_copy_normal_scalar(source, (float *)(a2[4] + 16 * a3));
  v20 = 1;
  v14 = 1;
  v13 = a2[1];
  if ( rf_vector_dot(a4 + 23, source) >= 0.0 )
  {
    if ( !a6 )
      return 0;
    rf_geomod_face_plane_reverse(source);
  }
  if ( !rf_swept_sphere_front_plane_contact(a4 + 20, a4 + 23, a4[18], source, (float *)&v17, rhs) )
    return 0;
  if ( *(float *)a5 <= (double)*(float *)&v17 )
    return 0;
  v18[0] = v13 + 12 * *v16;
  v18[1] = v13 + 12 * v16[1];
  v18[2] = v13 + 12 * v16[2];
  if ( v20 && rf_polygon_point_inside_projected_triangle_fan((int)rhs, 3, v18, source) )
  {
    *(float *)a5 = *(float *)&v17;
    rf_vector_copy((float *)(a5 + 4), copy_result, rhs);
    rf_vector_copy((float *)(a5 + 16), v11, source);
    *(_DWORD *)(a5 + 28) = v16;
    return 1;
  }
  else if ( rf_swept_sphere_polygon_edge_contacts(rhs, a4 + 20, a4 + 23, a4[18], 3, (const float **)v18, (float *)&v17)
         && *(float *)a5 > (double)*(float *)&v17 )
  {
    *(float *)a5 = *(float *)&v17;
    rf_vector_copy((float *)(a5 + 4), v10, rhs);
    v7 = rf_vector_subtract(a4 + 20, out_vector, rhs);
    rf_vector_copy((float *)(a5 + 16), v8, v7);
    rf_vector_normalize((float *)(a5 + 16));
    *(_DWORD *)(a5 + 28) = v16;
    return 1;
  }
  else
  {
    return 0;
  }
}

