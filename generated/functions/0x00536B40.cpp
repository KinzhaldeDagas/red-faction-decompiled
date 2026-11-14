// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536B40 rf_lightmap_descriptor_configure_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall descriptor,solid/world receiver,facePointerArray,representativePlane,density. Nonempty:byte9=any faceDWORD60 nonNULL;room-index104 from first face owner68+32 or-1;fullbrightBYTE10 from first face only;copies plane normal plus first corner point into plane108,selects dropped/U/V axes92/96/100. Scans projected coordinates of ALL face corners for U/V extents,max level=(FaceFlags40>>8)&3. Density44/48=caller density times(0.5,1,2,4) for levels0,1,2,3. Initial tile dims=trunc(extent*density+0.5),stats maxima recorded BEFORE clamps. Dimensions above64 clamped64 with density rescale;minimum4 or8 when byte9 set,zero treated1 for scaling. Claims atlas region552480,stores page pointer12,origin16/20.
// Mapping Uscale76=(tileW-2)/pageW/extentU,Vscale80 analog;offset84/88=-min*scale+(origin+1)/pageDimension. No zero extent/density/page validation. Builds AABB52/64 from first point and min-else-max helper;writes SECONDARY corner UVs+12/+16 with mapping and inclusive[0,1] clamp,primaryUV unchanged. FlagsBYTE8=0. Fullbright baselineRGB128;otherwise use room custom ambient if room-index valid and roomBYTE69==1 (RGB bytes70..72 /255),else global ambient floats;trunc(channel*128),store lowBYTE without saturation. Fills RGB24 RAM tile and,if bitmap lock succeeds,uploads each to1RGB555 WORD with channels>>3 and bit15 set;lock failure silently leaves RAM/configuration valid,return still tileW*tileH. Empty list sets dimensions0,byte9=0,still claims zero-sized atlas region/stores page,returns0;other mapping/flag fields not refreshed. No face lightmap-ID assignment,old-region release or
// transactional cleanup.
int __thiscall rf_lightmap_descriptor_configure_faces(int this, int a2, _DWORD *a3, float *a4, float a5)
{
  int v6; // eax
  int v7; // eax
  int first_dword; // eax
  int v9; // eax
  float *v10; // eax
  float v11; // [esp+4h] [ebp-13Ch]
  int v12; // [esp+18h] [ebp-128h]
  int v13; // [esp+28h] [ebp-118h]
  int v15; // [esp+30h] [ebp-110h]
  float v16[3]; // [esp+34h] [ebp-10Ch] BYREF
  float copy_result[3]; // [esp+40h] [ebp-100h] BYREF
  unsigned __int8 v18; // [esp+4Dh] [ebp-F3h]
  unsigned __int8 v19; // [esp+4Eh] [ebp-F2h]
  unsigned __int8 v20; // [esp+4Fh] [ebp-F1h]
  int v21; // [esp+50h] [ebp-F0h]
  int jj; // [esp+54h] [ebp-ECh]
  int v23; // [esp+58h] [ebp-E8h]
  int v24; // [esp+5Ch] [ebp-E4h]
  unsigned int v25; // [esp+60h] [ebp-E0h]
  int v26; // [esp+64h] [ebp-DCh]
  int ii; // [esp+68h] [ebp-D8h]
  unsigned int v28[6]; // [esp+6Ch] [ebp-D4h] BYREF
  int v29; // [esp+84h] [ebp-BCh]
  _BYTE *v30; // [esp+8Ch] [ebp-B4h]
  float v31; // [esp+90h] [ebp-B0h] BYREF
  float v32; // [esp+94h] [ebp-ACh] BYREF
  float v33; // [esp+98h] [ebp-A8h] BYREF
  float v34; // [esp+9Ch] [ebp-A4h] BYREF
  float v35; // [esp+A0h] [ebp-A0h]
  int k; // [esp+A4h] [ebp-9Ch]
  int v37; // [esp+A8h] [ebp-98h]
  float v38; // [esp+ACh] [ebp-94h]
  float v39; // [esp+B0h] [ebp-90h]
  float v40; // [esp+B4h] [ebp-8Ch]
  float v41; // [esp+B8h] [ebp-88h]
  float v42; // [esp+BCh] [ebp-84h]
  float v43; // [esp+C0h] [ebp-80h]
  int v44; // [esp+C4h] [ebp-7Ch]
  unsigned int v45; // [esp+C8h] [ebp-78h]
  int j; // [esp+CCh] [ebp-74h]
  int v47; // [esp+D0h] [ebp-70h] BYREF
  int v48; // [esp+D4h] [ebp-6Ch] BYREF
  float v49; // [esp+D8h] [ebp-68h]
  int v50; // [esp+DCh] [ebp-64h] BYREF
  char v51; // [esp+E3h] [ebp-5Dh]
  char v52[12]; // [esp+E4h] [ebp-5Ch] BYREF
  int v53; // [esp+F0h] [ebp-50h]
  unsigned int v54; // [esp+F4h] [ebp-4Ch]
  int v55; // [esp+F8h] [ebp-48h]
  int v56; // [esp+FCh] [ebp-44h]
  float v57; // [esp+100h] [ebp-40h]
  int v58; // [esp+104h] [ebp-3Ch] BYREF
  float v59; // [esp+108h] [ebp-38h]
  _DWORD *v60; // [esp+10Ch] [ebp-34h]
  float v61; // [esp+110h] [ebp-30h]
  int v62; // [esp+114h] [ebp-2Ch]
  int v63; // [esp+118h] [ebp-28h] BYREF
  int i; // [esp+11Ch] [ebp-24h]
  float v65; // [esp+120h] [ebp-20h]
  int n; // [esp+124h] [ebp-1Ch]
  int m; // [esp+128h] [ebp-18h]
  char v68; // [esp+12Fh] [ebp-11h]
  float v69; // [esp+130h] [ebp-10h]
  int v70; // [esp+13Ch] [ebp-4h]

  if ( rf_receiver_get_first_dword(a3) )
  {
    *(_BYTE *)(this + 9) = 0;
    for ( i = 0; i < rf_receiver_get_first_dword(a3); ++i )
    {
      if ( *(_DWORD *)(*(_DWORD *)sub_552200(a3, i) + 60) )
      {
        *(_BYTE *)(this + 9) = 1;
        break;
      }
    }
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(a3, 0) + 68) )
      *(_DWORD *)(this + 104) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200(a3, 0) + 68) + 32);
    else
      *(_DWORD *)(this + 104) = -1;
    *(float *)(this + 44) = a5;
    *(float *)(this + 48) = a5;
    rf_face_projection_axes_select(a4, &v58, &v63, &v48);
    *(_DWORD *)(this + 92) = v58;
    *(_DWORD *)(this + 96) = v63;
    *(_DWORD *)(this + 100) = v48;
    v6 = sub_552200(a3, 0);
    rf_plane4_construct_normal_point((float *)(this + 108), a4, **(float ***)(*(_DWORD *)v6 + 64));
    v7 = sub_552200(a3, 0);
    *(_BYTE *)(this + 10) = rf_world_face_is_fullbright((_DWORD *)(*(_DWORD *)v7 + 40));
    v57 = 0.0;
    v61 = 0.0;
    v65 = 0.0;
    v59 = 0.0;
    v68 = 1;
    v54 = 0;
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(a3);
      if ( i >= first_dword )
        break;
      v44 = *(_DWORD *)sub_552200(a3, i);
      v45 = (*(_DWORD *)(v44 + 40) >> 8) & 3;
      if ( v45 > v54 )
        v54 = v45;
      for ( j = *(_DWORD *)(v44 + 64); j; j = v13 )
      {
        v42 = *(float *)rf_vector_component_address_unchecked(*(char **)j, v63);
        v43 = *(float *)rf_vector_component_address_unchecked(*(char **)j, v48);
        if ( v68 )
        {
          v68 = 0;
          v65 = v42;
          v57 = v42;
          v59 = v43;
          v61 = v43;
        }
        else
        {
          v57 = rf_float_minimum_two_values(v42, v57);
          v61 = rf_float_minimum_two_values(v43, v61);
          v65 = rf_float_maximum_two_values(v42, v65);
          v59 = rf_float_maximum_two_values(v43, v59);
        }
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(v44 + 64) )
          v13 = 0;
        else
          v13 = *(_DWORD *)(j + 20);
      }
    }
    if ( v54 )
    {
      if ( v54 == 2 )
      {
        *(float *)(this + 44) = *(float *)(this + 44) + *(float *)(this + 44);
        *(float *)(this + 48) = *(float *)(this + 48) + *(float *)(this + 48);
      }
      else if ( v54 == 3 )
      {
        *(float *)(this + 44) = *(float *)(this + 44) * 4.0;
        *(float *)(this + 48) = *(float *)(this + 48) * 4.0;
      }
    }
    else
    {
      *(float *)(this + 44) = *(float *)(this + 44) * 0.5;
      *(float *)(this + 48) = *(float *)(this + 48) * 0.5;
    }
    v69 = v65 - v57;
    v49 = v59 - v61;
    *(_DWORD *)(this + 24) = (int)(v69 * *(float *)(this + 44) + 0.5);
    *(_DWORD *)(this + 28) = (int)(v49 * *(float *)(this + 48) + 0.5);
    dword_1425E90 = rf_int_max(*(_DWORD *)(this + 24), dword_1425E90);
    dword_1425E94 = rf_int_max(*(_DWORD *)(this + 28), dword_1425E94);
    if ( *(int *)(this + 24) > 64 )
    {
      v41 = 64.0 / (double)*(int *)(this + 24);
      *(_DWORD *)(this + 24) = 64;
      *(float *)(this + 44) = *(float *)(this + 44) * v41;
    }
    if ( *(int *)(this + 28) > 64 )
    {
      v40 = 64.0 / (double)*(int *)(this + 28);
      *(_DWORD *)(this + 28) = 64;
      *(float *)(this + 48) = *(float *)(this + 48) * v40;
    }
    if ( *(_BYTE *)(this + 9) )
      v62 = 8;
    else
      v62 = 4;
    if ( *(_DWORD *)(this + 24) < v62 )
    {
      if ( !*(_DWORD *)(this + 24) )
        *(_DWORD *)(this + 24) = 1;
      v39 = (double)v62 / (double)*(int *)(this + 24);
      *(_DWORD *)(this + 24) = v62;
      *(float *)(this + 44) = *(float *)(this + 44) * v39;
    }
    if ( *(_DWORD *)(this + 28) < v62 )
    {
      if ( !*(_DWORD *)(this + 28) )
        *(_DWORD *)(this + 28) = 1;
      v38 = (double)v62 / (double)*(int *)(this + 28);
      *(_DWORD *)(this + 28) = v62;
      *(float *)(this + 48) = *(float *)(this + 48) * v38;
    }
    rf_lightmap_atlas_allocate_region(
      *(_DWORD *)(this + 24),
      *(_DWORD *)(this + 28),
      &v50,
      (_DWORD *)(this + 16),
      (_DWORD *)(this + 20));
    *(_DWORD *)(this + 12) = *(_DWORD *)sub_552200(unk_15A7148, v50);
    v51 = 1;
    *(float *)(this + 76) = (double)(*(_DWORD *)(this + 24) - 2) / (double)*(int *)(*(_DWORD *)(this + 12) + 4) / v69;
    *(float *)(this + 80) = (double)(*(_DWORD *)(this + 28) - 2) / (double)*(int *)(*(_DWORD *)(this + 12) + 8) / v49;
    *(float *)(this + 84) = -v57 * *(float *)(this + 76)
                          + ((double)*(int *)(this + 16) + 1.0) / (double)*(int *)(*(_DWORD *)(this + 12) + 4);
    *(float *)(this + 88) = -v61 * *(float *)(this + 80)
                          + ((double)*(int *)(this + 20) + 1.0) / (double)*(int *)(*(_DWORD *)(this + 12) + 8);
    for ( i = 0; ; ++i )
    {
      v9 = rf_receiver_get_first_dword(a3);
      if ( i >= v9 )
        break;
      v37 = *(_DWORD *)sub_552200(a3, i);
      for ( k = *(_DWORD *)(v37 + 64); k; k = v12 )
      {
        if ( v51 )
        {
          v51 = 0;
          rf_vector_copy((float *)(this + 52), copy_result, *(const float **)k);
          rf_vector_copy((float *)(this + 64), v16, *(const float **)k);
        }
        else
        {
          rf_aabb_include_point_min_else_max((float *)(this + 52), (float *)(this + 64), *(float **)k);
        }
        v11 = *(float *)rf_vector_component_address_unchecked(*(char **)k, v48);
        v10 = (float *)rf_vector_component_address_unchecked(*(char **)k, v63);
        rf_vector2_assign_components(&v34, *v10, v11);
        v34 = v34 * *(float *)(this + 76);
        v35 = v35 * *(float *)(this + 80);
        rf_vector2_accumulate(&v34, (float *)(this + 84));
        *(float *)(k + 12) = v34;
        *(float *)(k + 16) = v35;
        rf_float_clamp_in_place((float *)(k + 12), 0.0, 1.0);
        rf_float_clamp_in_place((float *)(k + 16), 0.0, 1.0);
        if ( *(_DWORD *)(k + 20) == *(_DWORD *)(v37 + 64) )
          v12 = 0;
        else
          v12 = *(_DWORD *)(k + 20);
      }
    }
    *(_BYTE *)(this + 8) = 0;
    if ( *(_BYTE *)(this + 10) )
    {
      dword_1425EC8 = 128;
      dword_1425ECC = 128;
      dword_1425ED0[0] = 128;
    }
    else
    {
      if ( *(_DWORD *)(this + 104) == -1
        || (v30 = *(_BYTE **)sub_552200((_DWORD *)(a2 + 144), *(_DWORD *)(this + 104)), v30[69] != 1) )
      {
        rf_light_get_ambient_rgb_floats(&v31, &v32, &v33);
      }
      else
      {
        v31 = (double)(unsigned __int8)v30[70] * 0.003921568859368563;
        v32 = (double)(unsigned __int8)v30[71] * 0.003921568859368563;
        v33 = (double)(unsigned __int8)v30[72] * 0.003921568859368563;
      }
      dword_1425ED0[0] = (int)(v31 * 128.0);
      dword_1425ECC = (int)(v32 * 128.0);
      dword_1425EC8 = (int)(v33 * 128.0);
    }
    rf_dword_array_construct_capacity(v52, 0);
    v70 = 0;
    v55 = 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4) * *(_DWORD *)(this + 20);
    for ( m = 0; m < *(_DWORD *)(this + 28); ++m )
    {
      v56 = 3 * *(_DWORD *)(this + 16);
      for ( n = 0; n < *(_DWORD *)(this + 24); ++n )
      {
        *(_BYTE *)(v55 + v56 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12)) = dword_1425ED0[0];
        *(_BYTE *)(v55 + v56 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 1) = dword_1425ECC;
        *(_BYTE *)(v55 + v56 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 2) = dword_1425EC8;
        v56 += 3;
      }
      v55 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
    }
    v53 = this;
    v60 = *(_DWORD **)(this + 12);
    if ( v60 && rf_bitmap_lock_pixels_backend_dispatch(v60[4], 0, (int)v28, 1) )
    {
      v26 = 3 * *(_DWORD *)(this + 16) + 3 * v60[1] * *(_DWORD *)(this + 20);
      v24 = *(_DWORD *)(this + 16) + *(_DWORD *)(this + 20) * (v29 / 2);
      v23 = v26 + v60[3];
      v25 = v28[3] + 2 * v24;
      for ( ii = 0; ii < *(_DWORD *)(this + 28); ++ii )
      {
        for ( jj = 0; jj < *(_DWORD *)(this + 24); ++jj )
        {
          v21 = 3 * jj;
          v18 = *(_BYTE *)(3 * jj + v23);
          v18 >>= 3;
          v19 = *(_BYTE *)(3 * jj + v23 + 1);
          v19 >>= 3;
          v20 = *(_BYTE *)(3 * jj + v23 + 2);
          v20 >>= 3;
          *(_WORD *)(v25 + 2 * jj) = v20 | (32 * v19) | (v18 << 10) | 0x8000;
        }
        v23 += 3 * v60[1];
        v25 += 2 * (v29 / 2);
      }
      rf_bitmap_unlock_pixels_backend_dispatch(v28);
    }
    v15 = *(_DWORD *)(this + 28) * *(_DWORD *)(this + 24);
    v70 = -1;
    rf_pointer_array_destroy_backing_storage((void **)v52);
    return v15;
  }
  else
  {
    *(_DWORD *)(this + 24) = 0;
    *(_DWORD *)(this + 28) = 0;
    *(_BYTE *)(this + 9) = 0;
    rf_lightmap_atlas_allocate_region(
      *(_DWORD *)(this + 24),
      *(_DWORD *)(this + 28),
      &v47,
      (_DWORD *)(this + 16),
      (_DWORD *)(this + 20));
    *(_DWORD *)(this + 12) = *(_DWORD *)sub_552200(unk_15A7148, v47);
    return 0;
  }
}

