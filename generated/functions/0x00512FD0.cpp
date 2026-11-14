// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512FD0 rf_projected_shadow_build_and_submit
// UNREALRED VERIFIED [original-shadow-root-20261027] Source packet +4 model handle and +8 anchor from Object+620 feed 0x564D80 -> 0x562050. Animated type 2 uses 0x587B60 -> 0x585C50, which evaluates/copies the current selected bone model transform; a negative anchor produces identity. The builder rotates its translation by packet +24 object orientation and adds packet +12 object position before constructing the cone. Source animation must therefore be evaluated before resolving the projector anchor; unchanged actor placement alone does not justify reusing projected geometry.
// UNREALRED VERIFIED [moving-shadow-receiver-20261027] Moving receiver membership uses the live type-9 list at 0x704BCC, sentinel 0x704940, next +0x28C. 0x486DE0 returns common-object dword +0 (cached room); only equality with source room enters the solid pass. For each match, copies projector (0x513DC0), inverse-transforms it with CURRENT object position +0x3C and basis +0x48 (0x513C40), and clips solid+0x70 from object+0x294. No collision-enabled or common-inactive filter appears in this loop. Static world topology alone is not the receiver set; a host cache must track current solid instances/transforms/removal.
char __cdecl rf_projected_shadow_build_and_submit(int a1, int a2, float a3, int a4)
{
  int first_dword; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  int v16; // eax
  float v18; // [esp+Ch] [ebp-378h]
  float v19; // [esp+Ch] [ebp-378h]
  float v20; // [esp+Ch] [ebp-378h]
  float v21; // [esp+Ch] [ebp-378h]
  float v22; // [esp+Ch] [ebp-378h]
  float v23; // [esp+Ch] [ebp-378h]
  float v24; // [esp+Ch] [ebp-378h]
  float v25; // [esp+Ch] [ebp-378h]
  float *v26; // [esp+Ch] [ebp-378h]
  int v27; // [esp+10h] [ebp-374h]
  float v28; // [esp+14h] [ebp-370h]
  float v29; // [esp+18h] [ebp-36Ch]
  _BYTE v30[16]; // [esp+1Ch] [ebp-368h] BYREF
  _BYTE v31[16]; // [esp+2Ch] [ebp-358h] BYREF
  _BYTE v32[16]; // [esp+3Ch] [ebp-348h] BYREF
  _BYTE v33[16]; // [esp+4Ch] [ebp-338h] BYREF
  _BYTE v34[16]; // [esp+5Ch] [ebp-328h] BYREF
  _BYTE v35[16]; // [esp+6Ch] [ebp-318h] BYREF
  float v36[3]; // [esp+7Ch] [ebp-308h] BYREF
  float v37[3]; // [esp+88h] [ebp-2FCh] BYREF
  float v38[3]; // [esp+94h] [ebp-2F0h] BYREF
  float v39[3]; // [esp+A0h] [ebp-2E4h] BYREF
  float v40[3]; // [esp+ACh] [ebp-2D8h] BYREF
  float v41[3]; // [esp+B8h] [ebp-2CCh] BYREF
  float v42[3]; // [esp+C4h] [ebp-2C0h] BYREF
  float v43[3]; // [esp+D0h] [ebp-2B4h] BYREF
  float sum_result[3]; // [esp+DCh] [ebp-2A8h] BYREF
  float copy_result[3]; // [esp+E8h] [ebp-29Ch] BYREF
  float v46[3]; // [esp+F4h] [ebp-290h] BYREF
  int v47; // [esp+100h] [ebp-284h] BYREF
  float v48[4]; // [esp+104h] [ebp-280h] BYREF
  float v49[4]; // [esp+114h] [ebp-270h] BYREF
  float v50[4]; // [esp+124h] [ebp-260h] BYREF
  float v51[4]; // [esp+134h] [ebp-250h] BYREF
  float v52[4]; // [esp+144h] [ebp-240h] BYREF
  float v53[4]; // [esp+154h] [ebp-230h] BYREF
  float v54; // [esp+164h] [ebp-220h] BYREF
  float v55; // [esp+168h] [ebp-21Ch]
  float v56; // [esp+170h] [ebp-214h] BYREF
  float v57; // [esp+174h] [ebp-210h]
  float v58; // [esp+17Ch] [ebp-208h] BYREF
  float v59; // [esp+180h] [ebp-204h]
  float v60[2]; // [esp+188h] [ebp-1FCh] BYREF
  float v61; // [esp+190h] [ebp-1F4h]
  float v62[2]; // [esp+194h] [ebp-1F0h] BYREF
  float v63; // [esp+19Ch] [ebp-1E8h]
  float v64[2]; // [esp+1A0h] [ebp-1E4h] BYREF
  float v65; // [esp+1A8h] [ebp-1DCh]
  float v66[2]; // [esp+1ACh] [ebp-1D8h] BYREF
  float v67; // [esp+1B4h] [ebp-1D0h]
  float v68[3]; // [esp+1B8h] [ebp-1CCh] BYREF
  float v69[3]; // [esp+1C4h] [ebp-1C0h] BYREF
  float v70[3]; // [esp+1D0h] [ebp-1B4h] BYREF
  float v71[3]; // [esp+1DCh] [ebp-1A8h] BYREF
  float v72[3]; // [esp+1E8h] [ebp-19Ch] BYREF
  float v73[3]; // [esp+1F4h] [ebp-190h] BYREF
  int v74; // [esp+200h] [ebp-184h] BYREF
  float v75; // [esp+204h] [ebp-180h]
  float v76; // [esp+208h] [ebp-17Ch]
  float v77; // [esp+20Ch] [ebp-178h]
  float v78; // [esp+210h] [ebp-174h]
  int v79; // [esp+214h] [ebp-170h]
  float v80[70]; // [esp+21Ch] [ebp-168h] BYREF
  float destination[4]; // [esp+334h] [ebp-50h] BYREF
  char v82[36]; // [esp+344h] [ebp-40h] BYREF
  int j; // [esp+368h] [ebp-1Ch]
  float v84; // [esp+36Ch] [ebp-18h]
  float v85; // [esp+370h] [ebp-14h] BYREF
  float v86; // [esp+374h] [ebp-10h]
  float v87; // [esp+378h] [ebp-Ch]
  int v88; // [esp+37Ch] [ebp-8h] BYREF
  void *i; // [esp+380h] [ebp-4h]

  rf_vector3_default_construct_noop(&v85);
  rf_matrix3_construct(v82);
  LOBYTE(first_dword) = (unsigned __int8)rf_shadow_projector276_construct_noop((char *)v48);
  if ( rf_projected_shadow_work_count < 8 )
  {
    ++rf_projected_shadow_work_count;
    unk_928418 = 0;
    v78 = a3;
    v79 = a4;
    rf_vector3_default_construct_noop(destination);
    rf_model_handle_get_node_transform_adapter(*(_DWORD *)(a2 + 4), (int)v71, (int)v82, *(_DWORD *)(a2 + 8));
    v5 = rf_matrix3_rotate_vector(v71, v46, (float *)(a2 + 24));
    rf_vector_copy(destination, copy_result, v5);
    v6 = rf_vector_add((const float *)(a2 + 12), sum_result, destination);
    rf_vector_copy(&v56, v43, v6);
    v7 = rf_vector_add((const float *)(a2 + 12), v42, destination);
    rf_vector_copy(&v54, v41, v7);
    v55 = *(float *)a2 * 3.0 + v55;
    v8 = rf_vector_add((const float *)(a2 + 12), v40, destination);
    rf_vector_copy(&v58, v39, v8);
    v59 = v59 - *(float *)a2 * 2.5;
    destination[3] = v55 - v59;
    LOBYTE(first_dword) = rf_projected_shadow_compute_cone_extent(
                            (int)&v54,
                            (int)&v56,
                            *(float *)a2,
                            (float *)&v47,
                            (float *)&v74,
                            (float *)&v88);
    if ( (_BYTE)first_dword )
    {
      *(float *)&v74 = *(float *)&v74 * 0.5;
      v69[0] = 0.0;
      v69[1] = 1.0;
      v69[2] = 0.0;
      rf_vector_copy(v68, v38, (const float *)(a2 + 24));
      v9 = rf_vector_cross(v69, v37, v68);
      rf_vector_copy(v70, v36, v9);
      v29 = *(float *)&v74 * 0.5;
      v76 = rf_tan_float(v29);
      v84 = (v55 - v59) * v76;
      v60[0] = -v84;
      v60[1] = 0.0;
      v61 = v60[0];
      rf_vector_rotate_by_matrix3(v60, v68);
      rf_vector_accumulate(v60, &v58);
      v62[0] = -v84;
      v62[1] = 0.0;
      v63 = v84;
      rf_vector_rotate_by_matrix3(v62, v68);
      rf_vector_accumulate(v62, &v58);
      v64[0] = v84;
      v64[1] = 0.0;
      v65 = v84;
      rf_vector_rotate_by_matrix3(v64, v68);
      rf_vector_accumulate(v64, &v58);
      v66[0] = v84;
      v66[1] = 0.0;
      v67 = -v84;
      rf_vector_rotate_by_matrix3(v66, v68);
      rf_vector_accumulate(v66, &v58);
      v18 = rf_float_minimum_two_values(v64[0], v66[0]);
      v19 = rf_float_minimum_two_values(v62[0], v18);
      v72[0] = rf_float_minimum_two_values(v60[0], v19);
      v20 = rf_float_maximum_two_values(v64[0], v66[0]);
      v21 = rf_float_maximum_two_values(v62[0], v20);
      v73[0] = rf_float_maximum_two_values(v60[0], v21);
      v72[1] = v59;
      v73[1] = v57;
      v22 = rf_float_minimum_two_values(v65, v67);
      v23 = rf_float_minimum_two_values(v63, v22);
      v72[2] = rf_float_minimum_two_values(v61, v23);
      v24 = rf_float_maximum_two_values(v65, v67);
      v25 = rf_float_maximum_two_values(v63, v24);
      v73[2] = rf_float_maximum_two_values(v61, v25);
      v28 = *(float *)&v74 * 0.5;
      v75 = rf_tan_float(v28);
      v85 = 0.0;
      v86 = -1.0;
      v87 = 0.0;
      v10 = (float *)rf_plane_construct_from_normal_point(v35, &v85, (int)&v58);
      rf_plane_copy(v48, v10);
      v85 = -1.0;
      v86 = v75;
      v87 = 0.0;
      rf_vector_normalize_reciprocal_sqrt(&v85);
      rf_vector_rotate_by_matrix3(&v85, v68);
      v11 = (float *)rf_plane_construct_from_normal_point(v34, &v85, (int)&v54);
      rf_plane_copy(v49, v11);
      v85 = 0.0;
      v86 = v75;
      v87 = 1.0;
      rf_vector_normalize_reciprocal_sqrt(&v85);
      rf_vector_rotate_by_matrix3(&v85, v68);
      v12 = (float *)rf_plane_construct_from_normal_point(v33, &v85, (int)&v54);
      rf_plane_copy(v50, v12);
      v85 = 1.0;
      v86 = v75;
      v87 = 0.0;
      rf_vector_normalize_reciprocal_sqrt(&v85);
      rf_vector_rotate_by_matrix3(&v85, v68);
      v13 = (float *)rf_plane_construct_from_normal_point(v32, &v85, (int)&v54);
      rf_plane_copy(v51, v13);
      v85 = 0.0;
      v86 = v75;
      v87 = -1.0;
      rf_vector_normalize_reciprocal_sqrt(&v85);
      rf_vector_rotate_by_matrix3(&v85, v68);
      v14 = (float *)rf_plane_construct_from_normal_point(v31, &v85, (int)&v54);
      rf_plane_copy(v52, v14);
      v85 = 0.0;
      v86 = 1.0;
      v87 = 0.0;
      v15 = (float *)rf_plane_construct_from_normal_point(v30, &v85, (int)&v56);
      rf_plane_copy(v53, v15);
      v77 = (v55 - v59) / (v55 - v57) * 0.8999999761581421;
      rf_projected_shadow_walk_intersecting_geometry(a1, a2, v48, nullptr, nullptr);
      rf_shadow_projector276_construct_noop((char *)v80);
      for ( i = (void *)unk_704BCC; i != &unk_704940; i = *((void **)i + 163) )
      {
        if ( rf_receiver_get_first_dword(i) == a1 )
        {
          rf_shadow_projector276_copy_members((int)v80, (int)v48);
          sub_513C40((int)v80, (float *)i + 15, (float *)i + 18);
          rf_projected_shadow_clip_solid_polygons(
            a2,
            v80,
            (void *)(*((_DWORD *)i + 165) + 112),
            (float *)i + 15,
            (float *)i + 18);
        }
      }
      for ( j = 0; ; ++j )
      {
        first_dword = rf_receiver_get_first_dword((void *)(a1 + 48));
        if ( j >= first_dword )
          break;
        v26 = (float *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 48), j) + 20);
        v16 = sub_552200((_DWORD *)(a1 + 48), j);
        if ( rf_aabb_overlap_strict_ordered(v72, v73, (float *)(*(_DWORD *)v16 + 8), v26) )
        {
          if ( **(_DWORD **)sub_552200((_DWORD *)(a1 + 48), j) == a1 )
            v27 = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 48), j) + 4);
          else
            v27 = **(_DWORD **)sub_552200((_DWORD *)(a1 + 48), j);
          rf_projected_shadow_walk_intersecting_geometry(v27, a2, v48, nullptr, nullptr);
        }
      }
    }
  }
  return first_dword;
}

