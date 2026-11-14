// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051DC10 rf_solid_split_face_at_primary_uv_value
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl solid,face,axis,cut returnsAL bool. Construct TWO24-byte intersection records; constructor51EA00 is no-op, so it does not initialize output face slots. Walk original corner ring64; classify each current/next selected primaryUV against cut using51DFE0. Recognize exactly one 1->(2or3) crossing and one3->(2or1); second of same direction returns0 BEFORE allocations. When next classified2 record reuses next vertex pointer (secondNULL); strict1<->3 interpolates XYZ atF32 t=(cut-currentUV)/(nextUV-currentUV), records both source endpoint pointers. Current2 starts no crossing; coplanar edges ignored. Missing either crossing returns0. For each strict-intersection record allocate NEW44-byte vertex
// appended to solid120, propagate through common incident faces51AAA0, set record to new vertex/NULL. If face corner lookup finds inserted vertex, overwrite ONLY selected primaryUV with exact cut via51DFC0; secondaryUV and other face interpolatedUV remain. Call face split534120 with records indexes0/1 and output face pointer slots; ignores split bool. Rebase primaryUV average domain on each nonNULL returned child; unconditionally remove/destroy original with flag0, return1 even if both children invalid. Output slots uninitialized before split; if split returns early (adjacent endpoints) before writing them, caller still reads those slots. No transactional rollback, tolerance weld, check on failed propagation/allocation, or child recursive splitting.
char __cdecl rf_solid_split_face_at_primary_uv_value(int *a1, _DWORD *a2, int a3, float a4)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float scalar; // [esp+4h] [ebp-F8h]
  float scalara; // [esp+4h] [ebp-F8h]
  int v11; // [esp+8h] [ebp-F4h]
  float v12[3]; // [esp+Ch] [ebp-F0h] BYREF
  float v13[3]; // [esp+18h] [ebp-E4h] BYREF
  float v14[3]; // [esp+24h] [ebp-D8h] BYREF
  float v15[3]; // [esp+30h] [ebp-CCh] BYREF
  float v16[3]; // [esp+3Ch] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+48h] [ebp-B4h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-A8h] BYREF
  float copy_result[3]; // [esp+60h] [ebp-9Ch] BYREF
  float *v20; // [esp+6Ch] [ebp-90h]
  int corner_for_vertex_unchecked; // [esp+70h] [ebp-8Ch]
  float v22; // [esp+74h] [ebp-88h]
  float sum_result[3]; // [esp+78h] [ebp-84h] BYREF
  float v24; // [esp+84h] [ebp-78h]
  float source[3]; // [esp+88h] [ebp-74h] BYREF
  float v26; // [esp+94h] [ebp-68h]
  int v27; // [esp+98h] [ebp-64h]
  int v28; // [esp+9Ch] [ebp-60h]
  float *lhs; // [esp+A0h] [ebp-5Ch]
  float v30; // [esp+A4h] [ebp-58h]
  float *rhs; // [esp+A8h] [ebp-54h]
  char v32; // [esp+AFh] [ebp-4Dh]
  int i; // [esp+B0h] [ebp-4Ch]
  _DWORD v34[2]; // [esp+B4h] [ebp-48h] BYREF
  int v35; // [esp+BCh] [ebp-40h] BYREF
  char v36; // [esp+C3h] [ebp-39h]
  float *v37; // [esp+C4h] [ebp-38h] BYREF
  float *v38; // [esp+C8h] [ebp-34h]
  _QWORD destination[2]; // [esp+CCh] [ebp-30h] BYREF
  float *v40; // [esp+DCh] [ebp-20h] BYREF
  float *v41; // [esp+E0h] [ebp-1Ch]
  float v42[4]; // [esp+E4h] [ebp-18h] BYREF
  int j; // [esp+F4h] [ebp-8h]
  _DWORD *v44; // [esp+F8h] [ebp-4h] BYREF

  v36 = 0;
  v32 = 0;
  rf_vector_construct_no_unwind(
    (char *)&v37,
    0x18u,
    2,
    (void *(__thiscall *)(void *))rf_geomod_intersection24_construct_noop);
  v34[0] = &v37;
  v34[1] = &v40;
  i = a2[16];
  for ( i = a2[16]; i; i = v11 )
  {
    rhs = *(float **)i;
    lhs = **(float ***)(i + 20);
    v26 = rf_geomod_corner_primary_uv_component(i, a3);
    v30 = rf_geomod_corner_primary_uv_component(*(_DWORD *)(i + 20), a3);
    v27 = rf_primary_uv_classify_against_cut_epsilon(v26, a4);
    v28 = rf_primary_uv_classify_against_cut_epsilon(v30, a4);
    if ( v27 == 1 && (v28 == 2 || v28 == 3) )
    {
      if ( v36 )
        return 0;
      v36 = 1;
      if ( v28 == 2 )
      {
        v37 = lhs;
        v38 = nullptr;
        rf_vector_copy((float *)destination, copy_result, lhs);
      }
      else
      {
        v24 = (a4 - v26) / (v30 - v26);
        scalar = v24;
        v5 = rf_vector_subtract(lhs, out_vector, rhs);
        v6 = rf_vector_multiply_scalar(v5, scaled_result, scalar);
        rf_vector_add(rhs, source, v6);
        v37 = rhs;
        v38 = lhs;
        rf_vector_copy((float *)destination, v16, source);
      }
    }
    else if ( v27 == 3 && (v28 == 2 || v28 == 1) )
    {
      if ( v32 )
        return 0;
      v32 = 1;
      if ( v28 == 2 )
      {
        v40 = lhs;
        v41 = nullptr;
        rf_vector_copy(v42, v15, lhs);
      }
      else
      {
        v22 = (a4 - v26) / (v30 - v26);
        scalara = v22;
        v7 = rf_vector_subtract(lhs, v14, rhs);
        v8 = rf_vector_multiply_scalar(v7, v13, scalara);
        rf_vector_add(rhs, sum_result, v8);
        v40 = rhs;
        v41 = lhs;
        rf_vector_copy(v42, v12, sum_result);
      }
    }
    if ( *(_DWORD *)(i + 20) == a2[16] )
      v11 = 0;
    else
      v11 = *(_DWORD *)(i + 20);
  }
  if ( !v32 || !v36 )
    return 0;
  for ( j = 0; j < 2; ++j )
  {
    if ( (&v38)[6 * j] )
    {
      v20 = rf_solid_vertex_copy_append(a1, (float *)&destination[3 * j]);
      rf_geomod_split_vertex_propagate_to_incident_faces((&v37)[6 * j], (&v38)[6 * j], v20);
      (&v37)[6 * j] = v20;
      (&v38)[6 * j] = nullptr;
      corner_for_vertex_unchecked = (int)rf_face_find_corner_for_vertex_unchecked(a2, (int)v20);
      if ( corner_for_vertex_unchecked )
        rf_geomod_corner_set_primary_uv_component(corner_for_vertex_unchecked, a3, a4);
    }
  }
  rf_geomod_face_split_between_intersection_vertices((int)a2, (int)a1, 0, 1, (int)v34, &v35, (int *)&v44);
  if ( v35 )
    rf_geomod_face_primary_uv_rebase((_DWORD *)v35);
  if ( v44 )
    rf_geomod_face_primary_uv_rebase(v44);
  rf_solid_face_remove_destroy(a1, a2, 0);
  return 1;
}

