// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052F1B0 rf_collision_sweep_face_test
// UNREALRED VERIFIED [mission-visibility-20261020] UnHide mask3/query0x21 rejects see-through faceflag0x40, positive signed portal marker, liquid faceflag4, invisible faceflag0x2000 and faceflag1. World-coordinate querybit4 does not alter these admissions. It does NOT select query0x40 damage-specific filtering or alpha-sampled query0x80/0x100. Remaining face plane/polygon intersection, spatial tree and geomod-hole behavior still apply; a generic UE visibility ray is not established equivalent.
// UNREALRED VERIFIED [mission-unhide-20261020] For UnHide query0x21 skip face flags0x40,0x04,0x2000,0x01 and portal marker interpreted as signed16 >0. Surviving plane/polygon admission remains directional. Current UnrealRed triangle traversal has no RF spatial-tree acceleration and does not establish exact float/polygon/geomod-hole equivalence.
// UNREALRED VERIFIED [combat-panic-20261104]: Panic clearanceflags45 use bit40 faceflag80 rejection, notsee-through bit20; rejects positive portal,liquid,invisible andfacebit1 absent overrides. Radius>=float.0001 selects radius-expanded face bounds and56A420 frontplane contact, then projectedrawpolygon containment; outsidepolygon uses56A540 orderededge/startvertex contact. Querybit1 permits firstaccepted early return. Point/triangulated visibility is not equivalent.
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Selected-drop flags2000: no query20/40 rejection, so face40/80 are admitted; invisible2000 admitted by query2000; stillreject positive signed16portal,liquid4,face1. Polygon interior accepts T==currentbest (reject only best<T), copies surface point/rawface normal, edgeflag0,face and incrementscount. Outside polygon sphere uses ordered56A540 edges; accepted edge writes surfacepoint,normal=559200(center-contact),edgeflag1,count. Do not substitute bool/point query or SafeNormal.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Point geometry pickup queryflags1/5 have neither20(see-through rejection) nor40(face80 rejection), no alpha sampling bits80/100, no sphereedge fallback at zero radius. Both skip positive signed16portal, liquid4,invisible2000 and facebit1. Face40/80 can obstruct. Ordered front-plane569600 and raw geomod polygon containment apply; fraction==best is accepted. Internal worldbit4 changes transforms, not these face gates.
bool __cdecl rf_collision_sweep_face_test(float *source, int a2, int a3)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  int v12; // [esp+18h] [ebp-11Ch]
  float v13[3]; // [esp+1Ch] [ebp-118h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-10Ch] BYREF
  float v15[3]; // [esp+34h] [ebp-100h] BYREF
  float v16[3]; // [esp+40h] [ebp-F4h] BYREF
  float v17[3]; // [esp+4Ch] [ebp-E8h] BYREF
  float v18[3]; // [esp+58h] [ebp-DCh] BYREF
  float v19[3]; // [esp+64h] [ebp-D0h] BYREF
  float v20[3]; // [esp+70h] [ebp-C4h] BYREF
  float v21[3]; // [esp+7Ch] [ebp-B8h] BYREF
  int v22[3]; // [esp+88h] [ebp-ACh] BYREF
  float v23[3]; // [esp+94h] [ebp-A0h] BYREF
  int v24[3]; // [esp+A0h] [ebp-94h] BYREF
  float copy_result[3]; // [esp+ACh] [ebp-88h] BYREF
  float v26[3]; // [esp+B8h] [ebp-7Ch] BYREF
  float scaled_result[3]; // [esp+C4h] [ebp-70h] BYREF
  float sum_result[3]; // [esp+D0h] [ebp-64h] BYREF
  int v29; // [esp+DCh] [ebp-58h] BYREF
  int v30; // [esp+E0h] [ebp-54h]
  int v31; // [esp+E4h] [ebp-50h]
  int i; // [esp+E8h] [ebp-4Ch]
  float v33[3]; // [esp+ECh] [ebp-48h] BYREF
  int v34; // [esp+F8h] [ebp-3Ch] BYREF
  float v35; // [esp+FCh] [ebp-38h] BYREF
  float v36; // [esp+100h] [ebp-34h] BYREF
  float v37[3]; // [esp+104h] [ebp-30h] BYREF
  _BYTE v38[15]; // [esp+110h] [ebp-24h] BYREF
  char v39; // [esp+11Fh] [ebp-15h]
  float scalar; // [esp+120h] [ebp-14h] BYREF
  char v41; // [esp+127h] [ebp-Dh]
  int v42; // [esp+130h] [ebp-4h]

  if ( (*(_DWORD *)(a2 + 80) & 0x20) != 0 && rf_face_is_see_through((_DWORD *)source + 10) )
    return 0;
  if ( (*(_DWORD *)(a2 + 80) & 0x40) != 0 && rf_face_flags_test_bit80((_DWORD *)source + 10) )
    return 0;
  if ( (*(_DWORD *)(a2 + 80) & 0x400) != 0 && rf_geomod_face_owner_type1_flag152_clear((int)source) )
    return 0;
  if ( (*(_DWORD *)(a2 + 80) & 2) == 0 && rf_face_is_portal((__int16 *)source + 20) )
    return 0;
  if ( (*(_DWORD *)(a2 + 80) & 0x1000) == 0 && rf_face_is_liquid((_DWORD *)source + 10) )
    return 0;
  if ( (*(_DWORD *)(a2 + 80) & 8) == 0 )
  {
    if ( rf_face_is_invisible((_DWORD *)source + 10) && (*(_DWORD *)(a2 + 80) & 0x2000) == 0 )
      return 0;
    if ( ((_DWORD)source[10] & 1) != 0 && (*(_DWORD *)(a2 + 80) & 0x800) == 0 )
      return 0;
  }
  ++unk_D55560;
  if ( (dword_D555F8[0] & 1) == 0 )
  {
    dword_D555F8[0] |= 1u;
    rf_vector3_default_construct_noop(unk_D555EC);
    v42 = -1;
  }
  if ( (dword_D555F8[0] & 2) == 0 )
  {
    dword_D555F8[0] |= 2u;
    rf_vector3_default_construct_noop(unk_D555E0);
    v42 = -1;
  }
  if ( (dword_D555F8[0] & 4) == 0 )
  {
    dword_D555F8[0] |= 4u;
    rf_vector3_default_construct_noop(unk_D555D4);
    v42 = -1;
  }
  v41 = 1;
  v39 = 1;
  if ( *(float *)(a2 + 76) >= 0.00009999999747378752 )
  {
    v7 = rf_vector3_subtract_scalar_from_components(source + 4, (float *)v24, *(float *)(a2 + 76));
    rf_vector_copy(unk_D555EC, v23, v7);
    v8 = rf_vector3_add_scalar_to_components(source + 7, (float *)v22, *(float *)(a2 + 76));
    rf_vector_copy(unk_D555E0, v21, v8);
    rf_vector_add((const float *)(a2 + 84), v37, (const float *)(a2 + 96));
    if ( !rf_segment_intersects_aabb(unk_D555EC, unk_D555E0, (float *)(a2 + 84), v37, unk_D555D4) )
      return 0;
    ++unk_D55564;
    if ( !rf_swept_sphere_front_plane_contact(a2 + 84, a2 + 96, *(float *)(a2 + 76), (int)source, &scalar, unk_D555D4) )
      return 0;
  }
  else
  {
    v39 = 0;
    v4 = rf_vector_add((const float *)(a2 + 84), sum_result, (const float *)(a2 + 96));
    rf_vector3_copy_return_destination((float *)v38, v4);
    if ( !rf_segment_intersects_aabb(source + 4, source + 7, (float *)(a2 + 84), (float *)v38, unk_D555D4) )
      return 0;
    ++unk_D55564;
    if ( !rf_polygon_segment_intersect_front_plane((float *)(a2 + 84), (float *)(a2 + 96), source, &scalar) )
      return 0;
    v5 = rf_vector_multiply_scalar((const float *)(a2 + 96), scaled_result, scalar);
    v6 = rf_vector_add((const float *)(a2 + 84), v26, v5);
    rf_vector_copy(unk_D555D4, copy_result, v6);
  }
  if ( *(float *)(a3 + 4) < (double)scalar )
    return 0;
  if ( v41 && rf_geomod_face_contains_projected_point(source, (int)unk_D555D4) )
  {
    if ( *((int *)source + 12) > -1
      && ((*(_DWORD *)(a2 + 80) & 0x80) != 0 && rf_face_is_see_through((_DWORD *)source + 10)
       || (*(_DWORD *)(a2 + 80) & 0x100) != 0 && rf_face_flags_test_bit80((_DWORD *)source + 10))
      && (rf_face_interpolate_primary_uv_projected_fan((float **)source, (int)unk_D555D4, &v35, &v36),
          rf_rgba8_default_construct_noop(&v34),
          rf_bitmap_sample_wrapped_uv_rgba_dispatch(*((_DWORD *)source + 12), v35, v36, &v34),
          HIBYTE(v34) < 0x80u) )
    {
      return 0;
    }
    else
    {
      *(float *)(a3 + 4) = scalar;
      rf_vector_copy((float *)(a3 + 8), v20, unk_D555D4);
      rf_vector_copy((float *)(a3 + 20), v19, source);
      *(_DWORD *)(a3 + 32) = 0;
      *(_DWORD *)(a3 + 36) = source;
      ++*(_DWORD *)a3;
      return 1;
    }
  }
  else
  {
    if ( v39 )
    {
      rf_vector_add((const float *)(a2 + 84), v33, (const float *)(a2 + 96));
      rf_segment_bounds_build(unk_D555EC, unk_D555E0, (float *)(a2 + 84), v33);
      rf_vector3_subtract_scalar_in_place(unk_D555EC, *(float *)(a2 + 76));
      rf_vector3_add_scalar_in_place(unk_D555E0, *(float *)(a2 + 76));
      if ( (dword_D555F8[0] & 8) == 0 )
      {
        dword_D555F8[0] |= 8u;
        v42 = 3;
        rf_vector3_default_construct_noop(unk_D555C8);
        v42 = -1;
      }
      for ( i = *((_DWORD *)source + 16); i; i = v12 )
      {
        v31 = *(_DWORD *)i;
        v30 = **(_DWORD **)(i + 20);
        if ( rf_segment_intersects_aabb(unk_D555EC, unk_D555E0, (float *)v31, (float *)v30, unk_D555D4)
          && rf_swept_sphere_edge_or_start_vertex_contact(
               (int)unk_D555D4,
               a2 + 84,
               a2 + 96,
               *(float *)(a2 + 76),
               v31,
               v30,
               (float *)&v29,
               *(float *)(a3 + 4)) )
        {
          *(float *)(a3 + 4) = *(float *)&v29;
          rf_vector_copy((float *)(a3 + 8), v18, unk_D555D4);
          v9 = rf_vector_multiply_scalar((const float *)(a2 + 64), v17, *(float *)&v29);
          v10 = rf_vector_add((const float *)(a2 + 84), v16, v9);
          rf_vector_copy(unk_D555C8, v15, v10);
          v11 = rf_vector_subtract(unk_D555C8, out_vector, unk_D555D4);
          rf_vector_copy((float *)(a3 + 20), v13, v11);
          rf_vector_normalize_reciprocal_sqrt((float *)(a3 + 20));
          *(_DWORD *)(a3 + 32) = 1;
          *(_DWORD *)(a3 + 36) = source;
          ++*(_DWORD *)a3;
        }
        if ( *(_DWORD *)(i + 20) == *((_DWORD *)source + 16) )
          v12 = 0;
        else
          v12 = *(_DWORD *)(i + 20);
      }
    }
    return *(_DWORD *)a3 > 0;
  }
}

