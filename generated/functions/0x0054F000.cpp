// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054F000 rf_lightmap_accumulate_float_rgb_samples
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments solidcontext,lightmaprecord,unused,optionalperlightmaskpointerarray. Requires atlaspointer+12,width+24,height+28 nonzero. Operates globalRGBfloatplanes0x1566B20/0x14A6B20/0x14E6B20; callerinitializesambient. If recordbyte+9clear,maps each atlastexelcenter using scales+76/+80,offsets+84/+88 and selector+92; accumulatesactive-lightRGB atworldpoint with recordnormal+108,maskarray andlinearindex,then clampsnegativeRGB0. If byte+9set,collects faces whose signedlightmapindex+54 matchesrecordDWORD0,using either solidface list+112 or ownerroom index+104 androomfacelist+40. Builds per-corner smoothednormals0x5503F0. For eachtexel tests UVrectangleedgecrossings against collectedfaceedges; scanline state persists acrossrow. Relevanttexels seek2UVedgeintersections with doublingepsilon starting0.0001,up toboundedattempts; may use nearbycorner
// withinhalftexeldiagonal asfallback. Interpolates both worldposition andsmoothednormal inUV,then accumulatesactive lights; failure assignsRGB0.33. Outside/unreached texels assign0.1. Afterward copies interiorneighborvalues into left/right then top/bottom borders. Freesperfacevectorarrays andouterblock. If allocationblocknull,does not run sampling/fill and callerambient remains. No globalplanecapacity,dimension>=2,mappingselector or scalevalidation; bordercopyassumes neighborsexist. Does not clear prior positivefloatRGB before accumulation or normalize interpolatednormals inthisbody.
void __cdecl rf_lightmap_accumulate_float_rgb_samples(int a1, int a2, int a3, int a4)
{
  int first_dword; // eax
  int v5; // eax
  float *v6; // eax
  float *v7; // eax
  int v8; // eax
  const float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  float *v23; // eax
  float *v24; // eax
  float *v25; // eax
  float *v26; // eax
  float *v27; // eax
  int v28; // eax
  float v29; // [esp+18h] [ebp-364h]
  int v30; // [esp+1Ch] [ebp-360h]
  float v31; // [esp+20h] [ebp-35Ch]
  int v32; // [esp+24h] [ebp-358h]
  int v33; // [esp+28h] [ebp-354h]
  int v34; // [esp+2Ch] [ebp-350h]
  int v35; // [esp+30h] [ebp-34Ch]
  float v36; // [esp+3Ch] [ebp-340h]
  float v37[3]; // [esp+40h] [ebp-33Ch] BYREF
  float v38[3]; // [esp+4Ch] [ebp-330h] BYREF
  int v39[3]; // [esp+58h] [ebp-324h] BYREF
  float v40[3]; // [esp+64h] [ebp-318h] BYREF
  float v41[3]; // [esp+70h] [ebp-30Ch] BYREF
  float v42[3]; // [esp+7Ch] [ebp-300h] BYREF
  int v43[3]; // [esp+88h] [ebp-2F4h] BYREF
  float v44[3]; // [esp+94h] [ebp-2E8h] BYREF
  float v45[3]; // [esp+A0h] [ebp-2DCh] BYREF
  float v46[3]; // [esp+ACh] [ebp-2D0h] BYREF
  int v47[3]; // [esp+B8h] [ebp-2C4h] BYREF
  float v48[3]; // [esp+C4h] [ebp-2B8h] BYREF
  float v49[3]; // [esp+D0h] [ebp-2ACh] BYREF
  float v50[3]; // [esp+DCh] [ebp-2A0h] BYREF
  float v51[3]; // [esp+E8h] [ebp-294h] BYREF
  int v52[3]; // [esp+F4h] [ebp-288h] BYREF
  float v53[3]; // [esp+100h] [ebp-27Ch] BYREF
  float v54[3]; // [esp+10Ch] [ebp-270h] BYREF
  float v55[3]; // [esp+118h] [ebp-264h] BYREF
  float v56[3]; // [esp+124h] [ebp-258h] BYREF
  int v57[3]; // [esp+130h] [ebp-24Ch] BYREF
  float v58[3]; // [esp+13Ch] [ebp-240h] BYREF
  float v59[3]; // [esp+148h] [ebp-234h] BYREF
  float v60[3]; // [esp+154h] [ebp-228h] BYREF
  float sum_result[3]; // [esp+160h] [ebp-21Ch] BYREF
  int v62[3]; // [esp+16Ch] [ebp-210h] BYREF
  float v63[3]; // [esp+178h] [ebp-204h] BYREF
  float out_vector[3]; // [esp+184h] [ebp-1F8h] BYREF
  float v65[3]; // [esp+190h] [ebp-1ECh] BYREF
  float copy_result[3]; // [esp+19Ch] [ebp-1E0h] BYREF
  float v67[3]; // [esp+1A8h] [ebp-1D4h] BYREF
  float v68; // [esp+1B4h] [ebp-1C8h]
  int v69; // [esp+1B8h] [ebp-1C4h]
  float v70; // [esp+1BCh] [ebp-1C0h]
  int v71; // [esp+1C0h] [ebp-1BCh]
  float v72; // [esp+1C4h] [ebp-1B8h]
  float v73; // [esp+1C8h] [ebp-1B4h]
  float v74; // [esp+1CCh] [ebp-1B0h]
  float v75; // [esp+1D0h] [ebp-1ACh]
  int v76; // [esp+1D4h] [ebp-1A8h]
  int v77; // [esp+1D8h] [ebp-1A4h]
  int v78; // [esp+1DCh] [ebp-1A0h]
  int v79; // [esp+1E0h] [ebp-19Ch]
  void **v80; // [esp+1E4h] [ebp-198h]
  int i1; // [esp+1E8h] [ebp-194h]
  float v82; // [esp+1ECh] [ebp-190h]
  float v83; // [esp+1F0h] [ebp-18Ch]
  float v84; // [esp+1F4h] [ebp-188h]
  float v85; // [esp+1F8h] [ebp-184h]
  float v86; // [esp+1FCh] [ebp-180h]
  float v87[3]; // [esp+200h] [ebp-17Ch] BYREF
  float v88[3]; // [esp+20Ch] [ebp-170h] BYREF
  float v89; // [esp+218h] [ebp-164h]
  float v90; // [esp+21Ch] [ebp-160h]
  float v91[3]; // [esp+220h] [ebp-15Ch] BYREF
  float v92[3]; // [esp+22Ch] [ebp-150h] BYREF
  float v93; // [esp+238h] [ebp-144h]
  float v94[3]; // [esp+23Ch] [ebp-140h] BYREF
  float v95[3]; // [esp+248h] [ebp-134h] BYREF
  float v96; // [esp+254h] [ebp-128h]
  float v97; // [esp+258h] [ebp-124h]
  float v98; // [esp+25Ch] [ebp-120h]
  int v99; // [esp+260h] [ebp-11Ch]
  _DWORD *v100; // [esp+264h] [ebp-118h]
  int v101; // [esp+268h] [ebp-114h]
  int nn; // [esp+26Ch] [ebp-110h]
  int mm; // [esp+270h] [ebp-10Ch]
  int v104; // [esp+274h] [ebp-108h]
  int v105; // [esp+278h] [ebp-104h]
  int v106; // [esp+27Ch] [ebp-100h]
  _DWORD *v107; // [esp+280h] [ebp-FCh]
  int v108; // [esp+284h] [ebp-F8h]
  int kk; // [esp+288h] [ebp-F4h]
  int jj; // [esp+28Ch] [ebp-F0h]
  int v111; // [esp+290h] [ebp-ECh]
  float *rhs; // [esp+294h] [ebp-E8h]
  int v113; // [esp+298h] [ebp-E4h]
  float *lhs; // [esp+29Ch] [ebp-E0h]
  int v115; // [esp+2A0h] [ebp-DCh]
  float *v116; // [esp+2A4h] [ebp-D8h]
  int v117; // [esp+2A8h] [ebp-D4h]
  float *v118; // [esp+2ACh] [ebp-D0h]
  int v119; // [esp+2B0h] [ebp-CCh]
  float v120[3]; // [esp+2B4h] [ebp-C8h] BYREF
  char v121; // [esp+2C3h] [ebp-B9h]
  float v122; // [esp+2C4h] [ebp-B8h]
  int v123; // [esp+2C8h] [ebp-B4h]
  float destination[3]; // [esp+2CCh] [ebp-B0h] BYREF
  int v125; // [esp+2D8h] [ebp-A4h]
  int v126; // [esp+2DCh] [ebp-A0h]
  int ii; // [esp+2E0h] [ebp-9Ch]
  int n; // [esp+2E4h] [ebp-98h]
  int v129[2]; // [esp+2E8h] [ebp-94h] BYREF
  float v130; // [esp+2F0h] [ebp-8Ch]
  int v131[2]; // [esp+2F4h] [ebp-88h] BYREF
  float v132; // [esp+2FCh] [ebp-80h]
  float v133; // [esp+300h] [ebp-7Ch]
  int v134; // [esp+304h] [ebp-78h]
  int v135[2]; // [esp+308h] [ebp-74h] BYREF
  int v136[2]; // [esp+310h] [ebp-6Ch] BYREF
  float v137; // [esp+318h] [ebp-64h]
  int v138; // [esp+31Ch] [ebp-60h]
  float v139; // [esp+320h] [ebp-5Ch]
  float v140; // [esp+324h] [ebp-58h]
  int v141; // [esp+328h] [ebp-54h]
  int i; // [esp+32Ch] [ebp-50h]
  int j; // [esp+330h] [ebp-4Ch]
  int v144; // [esp+334h] [ebp-48h]
  float v145; // [esp+338h] [ebp-44h]
  float v146; // [esp+33Ch] [ebp-40h]
  void *v147[3]; // [esp+340h] [ebp-3Ch] BYREF
  float v148; // [esp+34Ch] [ebp-30h]
  void *Block; // [esp+350h] [ebp-2Ch] BYREF
  int v150; // [esp+354h] [ebp-28h]
  float *v151; // [esp+358h] [ebp-24h]
  float *v152; // [esp+35Ch] [ebp-20h]
  float *v153; // [esp+360h] [ebp-1Ch]
  int m; // [esp+364h] [ebp-18h]
  int k; // [esp+368h] [ebp-14h]
  int v156; // [esp+36Ch] [ebp-10h]
  int v157; // [esp+378h] [ebp-4h]

  if ( *(_DWORD *)(a2 + 12) && *(_DWORD *)(a2 + 24) && *(_DWORD *)(a2 + 28) )
  {
    v151 = flt_1566B20;
    v152 = flt_14A6B20;
    v153 = flt_14E6B20;
    v156 = 0;
    if ( *(_BYTE *)(a2 + 9) )
    {
      v148 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 4);
      v145 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 8);
      v36 = v148 * v148 + v145 * v145;
      v146 = rf_sqrt_float(v36) / 2.0;
      rf_dword_array_construct_capacity(v147, 0);
      v157 = 0;
      if ( *(_DWORD *)(a2 + 104) == -1 )
      {
        for ( i = rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = rf_solid_face_next_link(i) )
        {
          if ( *(__int16 *)(i + 54) == *(_DWORD *)a2 )
            rf_pointer_array_append_dword(v147, i);
        }
      }
      else
      {
        v144 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 144), *(_DWORD *)(a2 + 104));
        for ( j = rf_receiver_get_first_dword((void *)(v144 + 40)); j; j = rf_face_next_room_link(j) )
        {
          if ( *(__int16 *)(j + 54) == *(_DWORD *)a2 )
            rf_pointer_array_append_dword(v147, j);
        }
      }
      Block = nullptr;
      rf_lightmap_build_face_corner_smoothed_normals((int)v147, &Block);
      if ( Block )
      {
        for ( k = 0; k < *(_DWORD *)(a2 + 28); ++k )
        {
          v141 = *(_DWORD *)(a2 + 20) + k;
          v139 = (double)v141 * v145;
          v137 = ((double)v141 + 0.5) * v145;
          v140 = (double)(v141 + 1) * v145;
          v138 = 0;
          for ( m = 0; m < *(_DWORD *)(a2 + 24); ++m )
          {
            v134 = *(_DWORD *)(a2 + 16) + m;
            v130 = (double)v134 * v148;
            v132 = ((double)v134 + 0.5) * v148;
            v133 = (double)(v134 + 1) * v148;
            v150 = 0;
            rf_vector2_assign_components((float *)v131, v130, v139);
            rf_vector2_assign_components((float *)v135, v133, v139);
            rf_vector2_assign_components((float *)v129, v130, v140);
            rf_vector2_assign_components((float *)v136, v133, v140);
            for ( n = 0; ; ++n )
            {
              first_dword = rf_receiver_get_first_dword(v147);
              if ( n >= first_dword )
                break;
              v126 = *(_DWORD *)sub_552200(v147, n);
              for ( ii = *(_DWORD *)(v126 + 64); ii; ii = v35 )
              {
                if ( *(_DWORD *)(ii + 20) == *(_DWORD *)(v126 + 64) )
                  v34 = 0;
                else
                  v34 = *(_DWORD *)(ii + 20);
                v125 = v34;
                if ( !v34 )
                  v125 = *(_DWORD *)(v126 + 64);
                if ( rf_segments_intersect_2d_closed_nonparallel(
                       (float *)v131,
                       (float *)v129,
                       *(float *)(ii + 12),
                       *(float *)(ii + 16),
                       *(float *)(v125 + 12),
                       *(float *)(v125 + 16)) )
                {
                  ++v150;
                }
                if ( rf_segments_intersect_2d_closed_nonparallel(
                       (float *)v135,
                       (float *)v136,
                       *(float *)(ii + 12),
                       *(float *)(ii + 16),
                       *(float *)(v125 + 12),
                       *(float *)(v125 + 16)) )
                {
                  ++v150;
                }
                if ( rf_segments_intersect_2d_closed_nonparallel(
                       (float *)v131,
                       (float *)v135,
                       *(float *)(ii + 12),
                       *(float *)(ii + 16),
                       *(float *)(v125 + 12),
                       *(float *)(v125 + 16)) )
                {
                  ++v150;
                }
                if ( rf_segments_intersect_2d_closed_nonparallel(
                       (float *)v129,
                       (float *)v136,
                       *(float *)(ii + 12),
                       *(float *)(ii + 16),
                       *(float *)(v125 + 12),
                       *(float *)(v125 + 16)) )
                {
                  ++v150;
                }
                if ( *(_DWORD *)(ii + 20) == *(_DWORD *)(v126 + 64) )
                  v35 = 0;
                else
                  v35 = *(_DWORD *)(ii + 20);
              }
            }
            if ( v150 > 0 )
              v138 = 1;
            if ( v138 )
            {
              v123 = 0;
              v122 = 0.000099999997;
              v119 = -1;
              v121 = 0;
              rf_vector3_default_construct_noop(destination);
              rf_vector3_default_construct_noop(v120);
              do
              {
                v123 = 0;
                for ( jj = 0; ; ++jj )
                {
                  v5 = rf_receiver_get_first_dword(v147);
                  if ( jj >= v5 || v123 >= 2 )
                    break;
                  v108 = *(_DWORD *)sub_552200(v147, jj);
                  v107 = (char *)Block + 12 * jj;
                  v106 = 0;
                  for ( kk = *(_DWORD *)(v108 + 64); kk && v123 < 2; kk = v33 )
                  {
                    if ( *(_DWORD *)(kk + 20) == *(_DWORD *)(v108 + 64) )
                      v32 = 0;
                    else
                      v32 = *(_DWORD *)(kk + 20);
                    v105 = v32;
                    v104 = v106 + 1;
                    if ( !v32 )
                    {
                      v105 = *(_DWORD *)(v108 + 64);
                      v104 = 0;
                    }
                    v31 = fabs(*(float *)(v105 + 16) - *(float *)(kk + 16));
                    if ( v31 > 0.001
                      && (v137 >= *(float *)(kk + 16) - v122 && v137 <= *(float *)(v105 + 16) + v122
                       || v137 <= *(float *)(kk + 16) + v122 && v137 >= *(float *)(v105 + 16) - v122) )
                    {
                      *(&v111 + 4 * v123) = kk;
                      v6 = (float *)rf_vector_array12_element_address_unchecked(v107, v106);
                      (&rhs)[4 * v123] = v6;
                      *(&v113 + 4 * v123) = v105;
                      v7 = (float *)rf_vector_array12_element_address_unchecked(v107, v104);
                      (&lhs)[4 * v123++] = v7;
                    }
                    ++v106;
                    if ( *(_DWORD *)(kk + 20) == *(_DWORD *)(v108 + 64) )
                      v33 = 0;
                    else
                      v33 = *(_DWORD *)(kk + 20);
                  }
                }
                v122 = v122 + v122;
                ++v119;
                if ( v123 < 2 && !v119 )
                {
                  for ( mm = 0; ; ++mm )
                  {
                    v8 = rf_receiver_get_first_dword(v147);
                    if ( mm >= v8 || v121 )
                      break;
                    v101 = *(_DWORD *)sub_552200(v147, mm);
                    v100 = (char *)Block + 12 * mm;
                    v99 = 0;
                    for ( nn = *(_DWORD *)(v101 + 64); nn; nn = v30 )
                    {
                      v98 = *(float *)(nn + 12) - v132;
                      v96 = *(float *)(nn + 16) - v137;
                      v29 = v98 * v98 + v96 * v96;
                      v97 = rf_sqrt_float(v29);
                      if ( v146 >= (double)v97 )
                      {
                        v9 = (const float *)rf_vector_array12_element_address_unchecked(v100, v99);
                        rf_vector_copy(destination, copy_result, v9);
                        rf_vector_copy(v120, v65, *(const float **)nn);
                        v121 = 1;
                        break;
                      }
                      ++v99;
                      if ( *(_DWORD *)(nn + 20) == *(_DWORD *)(v101 + 64) )
                        v30 = 0;
                      else
                        v30 = *(_DWORD *)(nn + 20);
                    }
                  }
                }
              }
              while ( v123 != 2 && !v121 && v119 < 10 );
              if ( v119 >= 10 )
              {
                *v151 = 0.33000001;
                *v152 = 0.33000001;
                *v153 = 0.33000001;
              }
              else
              {
                if ( !v121 )
                {
                  v84 = *(float *)(v113 + 16) - *(float *)(v111 + 16);
                  v85 = (v137 - *(float *)(v111 + 16)) / v84;
                  v89 = *(float *)(v117 + 16) - *(float *)(v115 + 16);
                  v90 = (v137 - *(float *)(v115 + 16)) / v89;
                  v86 = (*(float *)(v113 + 12) - *(float *)(v111 + 12)) * v85 + *(float *)(v111 + 12);
                  v82 = (*(float *)(v117 + 12) - *(float *)(v115 + 12)) * v90 + *(float *)(v115 + 12);
                  v93 = v82 - v86;
                  if ( v93 == 0.0 )
                    v93 = 1.0;
                  v83 = (v132 - v86) / v93;
                  rf_vector3_default_construct_noop(v94);
                  rf_vector3_default_construct_noop(v91);
                  rf_vector3_default_construct_noop(v92);
                  rf_vector3_default_construct_noop(v95);
                  rf_vector3_default_construct_noop(v87);
                  rf_vector3_default_construct_noop(v88);
                  v10 = rf_vector_subtract(lhs, out_vector, rhs);
                  rf_vector_copy(v87, v63, v10);
                  v11 = rf_vector_scale((float *)v62, v85, v87);
                  v12 = rf_vector_add(rhs, sum_result, v11);
                  rf_vector_copy(v94, v60, v12);
                  v13 = rf_vector_subtract(v118, v59, v116);
                  rf_vector_copy(v87, v58, v13);
                  v14 = rf_vector_scale((float *)v57, v90, v87);
                  v15 = rf_vector_add(v116, v56, v14);
                  rf_vector_copy(v91, v55, v15);
                  v16 = rf_vector_subtract(*(const float **)v113, v54, *(const float **)v111);
                  rf_vector_copy(v88, v53, v16);
                  v17 = rf_vector_scale((float *)v52, v85, v88);
                  v18 = rf_vector_add(*(const float **)v111, v51, v17);
                  rf_vector_copy(v92, v50, v18);
                  v19 = rf_vector_subtract(*(const float **)v117, v49, *(const float **)v115);
                  rf_vector_copy(v88, v48, v19);
                  v20 = rf_vector_scale((float *)v47, v90, v88);
                  v21 = rf_vector_add(*(const float **)v115, v46, v20);
                  rf_vector_copy(v95, v45, v21);
                  v22 = rf_vector_subtract(v91, v44, v94);
                  v23 = rf_vector_scale((float *)v43, v83, v22);
                  v24 = rf_vector_add(v94, v42, v23);
                  rf_vector_copy(destination, v41, v24);
                  v25 = rf_vector_subtract(v95, v40, v92);
                  v26 = rf_vector_scale((float *)v39, v83, v25);
                  v27 = rf_vector_add(v92, v38, v26);
                  rf_vector_copy(v120, v37, v27);
                }
                rf_renderer_accumulate_active_light_rgb(
                  v151,
                  v152,
                  v153,
                  v120,
                  destination,
                  a4,
                  v156,
                  (_BYTE *)(a2 + 9));
                if ( *v151 < 0.0 )
                  *v151 = 0.0;
                if ( *v152 < 0.0 )
                  *v152 = 0.0;
                if ( *v153 < 0.0 )
                  *v153 = 0.0;
              }
            }
            else
            {
              *v151 = 0.1;
              *v152 = 0.1;
              *v153 = 0.1;
            }
            ++v151;
            ++v152;
            ++v153;
            ++v156;
          }
        }
        for ( i1 = 0; ; ++i1 )
        {
          v28 = rf_receiver_get_first_dword(v147);
          if ( i1 >= v28 )
            break;
          v80 = (void **)((char *)Block + 12 * i1);
          rf_pointer_array_scalar_deleting_destructor_552170(v80, 0);
        }
        free(Block);
        v151 = flt_1566B20;
        v152 = flt_14A6B20;
        v153 = flt_14E6B20;
        for ( k = 0; k < *(_DWORD *)(a2 + 28); ++k )
        {
          v79 = *(_DWORD *)(a2 + 24) * k;
          v78 = v79 + *(_DWORD *)(a2 + 24) - 1;
          v151[v79] = v151[v79 + 1];
          v151[v78] = v151[v78 - 1];
          v152[v79] = v152[v79 + 1];
          v152[v78] = v152[v78 - 1];
          v153[v79] = v153[v79 + 1];
          v153[v78] = v153[v78 - 1];
        }
        for ( m = 0; m < *(_DWORD *)(a2 + 24); ++m )
        {
          v77 = m;
          v76 = m + *(_DWORD *)(a2 + 24) * (*(_DWORD *)(a2 + 28) - 1);
          v151[m] = v151[*(_DWORD *)(a2 + 24) + m];
          v151[v76] = v151[v76 - *(_DWORD *)(a2 + 24)];
          v152[v77] = v152[*(_DWORD *)(a2 + 24) + v77];
          v152[v76] = v152[v76 - *(_DWORD *)(a2 + 24)];
          v153[v77] = v153[*(_DWORD *)(a2 + 24) + v77];
          v153[v76] = v153[v76 - *(_DWORD *)(a2 + 24)];
        }
        v157 = -1;
        rf_pointer_array_destroy_backing_storage(v147);
      }
      else
      {
        v157 = -1;
        rf_pointer_array_destroy_backing_storage(v147);
      }
    }
    else
    {
      v73 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 4);
      v72 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 8);
      v74 = 1.0 / *(float *)(a2 + 80);
      v75 = 1.0 / *(float *)(a2 + 76);
      for ( k = 0; k < *(_DWORD *)(a2 + 28); ++k )
      {
        v71 = *(_DWORD *)(a2 + 20) + k;
        v70 = ((double)v71 + 0.5) * v72;
        v70 = v70 - *(float *)(a2 + 88);
        v70 = v70 * v74;
        for ( m = 0; m < *(_DWORD *)(a2 + 24); ++m )
        {
          v69 = *(_DWORD *)(a2 + 16) + m;
          v68 = ((double)v69 + 0.5) * v73;
          v68 = v68 - *(float *)(a2 + 84);
          v68 = v68 * v75;
          rf_vector3_default_construct_noop(v67);
          ((void (__thiscall *)(int, _DWORD, _DWORD, float *))unk_1425E98[4 * *(_DWORD *)(a2 + 92)])(
            unk_1425E9C[4 * *(_DWORD *)(a2 + 92)] + a2,
            LODWORD(v68),
            LODWORD(v70),
            v67);
          rf_renderer_accumulate_active_light_rgb(
            v151,
            v152,
            v153,
            v67,
            (float *)(a2 + 108),
            a4,
            v156,
            (_BYTE *)(a2 + 9));
          if ( *v151 < 0.0 )
            *v151 = 0.0;
          if ( *v152 < 0.0 )
            *v152 = 0.0;
          if ( *v153 < 0.0 )
            *v153 = 0.0;
          ++v151;
          ++v152;
          ++v153;
          ++v156;
        }
      }
    }
  }
}

