// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00550950 rf_lightmap_build_projected_occluder_shadow_mask
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Arguments solidcontext,lightmaprecord,lightrecord,debugbyte,callerinitializedmask. Requires regionwidth+24,height+28nonzero. Maps fourinteriorregionUVcorners andcenter via0x54D700. LightAABB built fromposition+/-radius+60; uses transformedpositions+92/+104 whenreceiver-space0x18CD388 set,elseworld+12/+24. LightDWORD+8==4 samplesboth endpoints withcoverage127each; otherlights sampleoneposition withcoverage255. Collects receiverfaceUVpolygons matching signedface+54==lightmapDWORD0 fromsolidfacelist+112 orroom index+104/facelist+40. Allocates260-bytepolygonrecords with32XYslots,count+256; cornerappend hasno32capacityguard. For eachlightsample,normalizes light-center andtests dotwithreceiver normal+108; nonpositive clearsENTIREmask to0,freesrecords,andreturns,even ifanotherendpointsamplemightfacefront. Builds6 clippingplanes
// fromlight,receiversurface andinteriorrectangle; orientsplanes and supportcornerselectors. Walks solidoccluderfaces,requiring overlapwithlightAABB andlight-expandedreceiverAABB,portalmarker+52<=0,flagmask4/0x40/0x2000clear,differentlightmapindex,andnobitmap ORbitmapformatpredicate0x576580false. Skipsnear-coplanarreceiverplane when Ddifference<0.001 andnormaldot>0.999. UsesAABBsupporttests,clipsworldpolygonagainst6planesinto2global64-vertexbuffers,requires>=3. Projects verticesfromlightsampleontoreceiverplane via0x56BE00,converts selectedworldcomponents throughrecordUVscales+76/+80,offsets+84/+88,atlasdimensions,andregionorigin; clampsXY1..regiondimension-1,removesadjacentexactduplicates. Projectionfailure skipsoccluder. Intersectsprojectedpolygon withreceiverUVpolygons via0x5C87D0; ifintersectionhas>2vertices andarea0x54D870 exceedsrecordfloat+44*+48,accepts. Rasterizes
// ORIGINALprojectedoccluderpolygon through0x54D1F0,notreceiverintersection,subtractingcoverage127/255. Afteranysuccessfullyprojectedpolygonprocessed,duplicatesinteriorneighbors onto left/right then top/bottom maskborders,evenifareatestpreventedrasterwrite. Normalpath doesnotinitialize mask; updater0x54D990 supplies255bytes. Freesreceiverpolygonrecords andarraystorage; debugcalls0x54D6E0/6F0areno-ops. No dimensions>=2,world/UVpolygon<=64,allocationfailure or mapperaxisvalidation; fixedscratch/globalclipbuffers make nonreentrant. Existing Face+0x34 portal versus+0x36 lightmap distinction retained.
void __cdecl rf_lightmap_build_projected_occluder_shadow_mask(int a1, int a2, int a3, char a4, char *a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  int first_dword; // eax
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
  int v24; // eax
  const void **v25; // eax
  int v26; // eax
  int v27; // eax
  void **v28; // eax
  int v29; // [esp+4h] [ebp-A80h]
  float v30; // [esp+8h] [ebp-A7Ch]
  size_t v31; // [esp+8h] [ebp-A7Ch]
  float *v32; // [esp+10h] [ebp-A74h]
  float *v33; // [esp+14h] [ebp-A70h]
  int v34; // [esp+28h] [ebp-A5Ch]
  float *v35; // [esp+2Ch] [ebp-A58h]
  float v36; // [esp+30h] [ebp-A54h]
  int v37; // [esp+34h] [ebp-A50h]
  int v38; // [esp+38h] [ebp-A4Ch]
  int v39; // [esp+3Ch] [ebp-A48h]
  int v40; // [esp+40h] [ebp-A44h]
  float v41; // [esp+44h] [ebp-A40h]
  float v42; // [esp+48h] [ebp-A3Ch]
  float v43[3]; // [esp+58h] [ebp-A2Ch] BYREF
  float v44[3]; // [esp+64h] [ebp-A20h] BYREF
  float v45[3]; // [esp+70h] [ebp-A14h] BYREF
  float v46[3]; // [esp+7Ch] [ebp-A08h] BYREF
  float v47[3]; // [esp+88h] [ebp-9FCh] BYREF
  float v48[3]; // [esp+94h] [ebp-9F0h] BYREF
  char v49[12]; // [esp+A0h] [ebp-9E4h] BYREF
  float v50[3]; // [esp+ACh] [ebp-9D8h] BYREF
  char v51[12]; // [esp+B8h] [ebp-9CCh] BYREF
  _BYTE v52[16]; // [esp+C4h] [ebp-9C0h] BYREF
  _BYTE v53[16]; // [esp+D4h] [ebp-9B0h] BYREF
  _BYTE v54[16]; // [esp+E4h] [ebp-9A0h] BYREF
  _BYTE v55[16]; // [esp+F4h] [ebp-990h] BYREF
  char v56[12]; // [esp+104h] [ebp-980h] BYREF
  _BYTE v57[16]; // [esp+110h] [ebp-974h] BYREF
  _BYTE v58[16]; // [esp+120h] [ebp-964h] BYREF
  float v59[3]; // [esp+130h] [ebp-954h] BYREF
  float v60[3]; // [esp+13Ch] [ebp-948h] BYREF
  void *v61; // [esp+148h] [ebp-93Ch]
  float v62[3]; // [esp+14Ch] [ebp-938h] BYREF
  float v63[3]; // [esp+158h] [ebp-92Ch] BYREF
  void *v64; // [esp+164h] [ebp-920h]
  int v65; // [esp+168h] [ebp-91Ch]
  void *v66; // [esp+16Ch] [ebp-918h]
  int v67; // [esp+170h] [ebp-914h]
  float v68[3]; // [esp+174h] [ebp-910h] BYREF
  float v69[3]; // [esp+180h] [ebp-904h] BYREF
  float v70[3]; // [esp+18Ch] [ebp-8F8h] BYREF
  float v71[3]; // [esp+198h] [ebp-8ECh] BYREF
  int v72[3]; // [esp+1A4h] [ebp-8E0h] BYREF
  float v73[3]; // [esp+1B0h] [ebp-8D4h] BYREF
  float v74[3]; // [esp+1BCh] [ebp-8C8h] BYREF
  float sum_result[3]; // [esp+1C8h] [ebp-8BCh] BYREF
  int v76[3]; // [esp+1D4h] [ebp-8B0h] BYREF
  float out_vector[3]; // [esp+1E0h] [ebp-8A4h] BYREF
  float v78[3]; // [esp+1ECh] [ebp-898h] BYREF
  float v79[3]; // [esp+1F8h] [ebp-88Ch] BYREF
  float v80[3]; // [esp+204h] [ebp-880h] BYREF
  float copy_result[3]; // [esp+210h] [ebp-874h] BYREF
  int v82; // [esp+21Ch] [ebp-868h]
  int v83; // [esp+220h] [ebp-864h]
  int i1; // [esp+224h] [ebp-860h]
  int v85; // [esp+228h] [ebp-85Ch]
  int v86; // [esp+22Ch] [ebp-858h]
  int nn; // [esp+230h] [ebp-854h]
  float *v88; // [esp+234h] [ebp-850h] BYREF
  float v89; // [esp+238h] [ebp-84Ch] BYREF
  float v90; // [esp+23Ch] [ebp-848h]
  float v91[3]; // [esp+240h] [ebp-844h] BYREF
  float v92[3]; // [esp+24Ch] [ebp-838h] BYREF
  void *v93; // [esp+258h] [ebp-82Ch]
  int v94; // [esp+25Ch] [ebp-828h]
  float v95[3]; // [esp+260h] [ebp-824h] BYREF
  float v96; // [esp+26Ch] [ebp-818h]
  float v97[2]; // [esp+270h] [ebp-814h] BYREF
  int v98; // [esp+278h] [ebp-80Ch]
  int v99; // [esp+27Ch] [ebp-808h]
  int v100; // [esp+280h] [ebp-804h]
  float *v101; // [esp+284h] [ebp-800h]
  float v102[128]; // [esp+288h] [ebp-7FCh] BYREF
  int v103; // [esp+488h] [ebp-5FCh]
  float v104[3]; // [esp+48Ch] [ebp-5F8h] BYREF
  char v105[512]; // [esp+498h] [ebp-5ECh] BYREF
  float Src[128]; // [esp+698h] [ebp-3ECh] BYREF
  char v107; // [esp+89Bh] [ebp-1E9h]
  void *v108; // [esp+89Ch] [ebp-1E8h]
  float source[3]; // [esp+8A0h] [ebp-1E4h] BYREF
  int v110; // [esp+8ACh] [ebp-1D8h]
  void *v111; // [esp+8B0h] [ebp-1D4h]
  int v112; // [esp+8B4h] [ebp-1D0h]
  int kk; // [esp+8B8h] [ebp-1CCh]
  char v114[12]; // [esp+8BCh] [ebp-1C8h] BYREF
  float v115[3]; // [esp+8C8h] [ebp-1BCh] BYREF
  int v116; // [esp+8D4h] [ebp-1B0h]
  float *mm; // [esp+8D8h] [ebp-1ACh]
  float v118[3]; // [esp+8DCh] [ebp-1A8h] BYREF
  float lhs[3]; // [esp+8E8h] [ebp-19Ch] BYREF
  int v120; // [esp+8F4h] [ebp-190h]
  int ii; // [esp+8F8h] [ebp-18Ch]
  int k; // [esp+8FCh] [ebp-188h]
  int v123; // [esp+900h] [ebp-184h]
  int j; // [esp+904h] [ebp-180h]
  int n; // [esp+908h] [ebp-17Ch]
  int v126; // [esp+90Ch] [ebp-178h]
  int m; // [esp+910h] [ebp-174h]
  int v128; // [esp+914h] [ebp-170h]
  float v129; // [esp+918h] [ebp-16Ch]
  int i; // [esp+91Ch] [ebp-168h]
  int v131[3]; // [esp+920h] [ebp-164h] BYREF
  float v132; // [esp+92Ch] [ebp-158h]
  _BYTE v133[12]; // [esp+930h] [ebp-154h] BYREF
  float v134; // [esp+93Ch] [ebp-148h]
  float v135; // [esp+940h] [ebp-144h]
  float v136[3]; // [esp+944h] [ebp-140h] BYREF
  float v137[4]; // [esp+950h] [ebp-134h] BYREF
  float v138[4]; // [esp+960h] [ebp-124h] BYREF
  float v139[4]; // [esp+970h] [ebp-114h] BYREF
  float v140[4]; // [esp+980h] [ebp-104h] BYREF
  float v141[4]; // [esp+990h] [ebp-F4h] BYREF
  float v142[5]; // [esp+9A0h] [ebp-E4h] BYREF
  float v143; // [esp+9B4h] [ebp-D0h]
  float v144; // [esp+9B8h] [ebp-CCh]
  int v145[9]; // [esp+9BCh] [ebp-C8h] BYREF
  char v146; // [esp+9E3h] [ebp-A1h]
  _BYTE v147[12]; // [esp+9E4h] [ebp-A0h] BYREF
  float v148; // [esp+9F0h] [ebp-94h]
  float v149; // [esp+9F4h] [ebp-90h] BYREF
  float v150; // [esp+9F8h] [ebp-8Ch]
  float v151; // [esp+9FCh] [ebp-88h]
  float v152[6]; // [esp+A00h] [ebp-84h] BYREF
  int jj; // [esp+A18h] [ebp-6Ch]
  float destination; // [esp+A1Ch] [ebp-68h] BYREF
  float v155; // [esp+A20h] [ebp-64h]
  float v156; // [esp+A24h] [ebp-60h]
  void *v157[3]; // [esp+A28h] [ebp-5Ch] BYREF
  int v158[9]; // [esp+A34h] [ebp-50h] BYREF
  float rhs[3]; // [esp+A58h] [ebp-2Ch] BYREF
  int v160[3]; // [esp+A64h] [ebp-20h] BYREF
  int v161; // [esp+A70h] [ebp-14h]
  char v162; // [esp+A77h] [ebp-Dh]
  int v163; // [esp+A80h] [ebp-4h]

  rf_vector3_default_construct_noop(v133);
  rf_vector3_default_construct_noop(v147);
  rf_vector_construct_no_unwind((char *)v137, 0x10u, 6, rf_vector_prefix_construct_noop);
  if ( *(_DWORD *)(a2 + 24) && *(_DWORD *)(a2 + 28) )
  {
    rf_vector3_default_construct_noop(rhs);
    rf_vector3_default_construct_noop(v145);
    rf_vector3_default_construct_noop(v158);
    rf_vector3_default_construct_noop(v131);
    rf_vector3_default_construct_noop(v160);
    v143 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 4);
    v134 = 1.0 / (double)*(int *)(*(_DWORD *)(a2 + 12) + 8);
    v132 = ((double)*(int *)(a2 + 16) + 1.0) * v143;
    v148 = ((double)*(int *)(a2 + 20) + 1.0) * v134;
    v144 = (double)(*(_DWORD *)(a2 + 24) - 2) * v143 + v132;
    v135 = (double)(*(_DWORD *)(a2 + 28) - 2) * v134 + v148;
    rf_lightmap_uv_to_world_dispatch(a2, v132, v148, (int)v145);
    rf_lightmap_uv_to_world_dispatch(a2, v132, v135, (int)v131);
    rf_lightmap_uv_to_world_dispatch(a2, v144, v148, (int)v158);
    rf_lightmap_uv_to_world_dispatch(a2, v144, v135, (int)v160);
    v42 = (v135 - v148) * 0.5 + v148;
    v41 = (v144 - v132) * 0.5 + v132;
    rf_lightmap_uv_to_world_dispatch(a2, v41, v42, (int)rhs);
    rf_vector3_default_construct_noop(v136);
    rf_vector_construct_no_unwind((char *)v152, 0xCu, 2, rf_vector3_default_construct_noop);
    rf_vector3_default_construct_noop(&destination);
    rf_vector3_default_construct_noop(&v149);
    if ( unk_18CD388 )
    {
      rf_vector_copy(&destination, v79, (const float *)(a3 + 92));
      rf_vector_copy(&v149, v78, (const float *)(a3 + 92));
    }
    else
    {
      rf_vector_copy(&destination, copy_result, (const float *)(a3 + 12));
      rf_vector_copy(&v149, v80, (const float *)(a3 + 12));
    }
    destination = destination - *(float *)(a3 + 60);
    v155 = v155 - *(float *)(a3 + 60);
    v156 = v156 - *(float *)(a3 + 60);
    v149 = v149 + *(float *)(a3 + 60);
    v150 = v150 + *(float *)(a3 + 60);
    v151 = v151 + *(float *)(a3 + 60);
    if ( *(_DWORD *)(a3 + 8) == 4 )
    {
      for ( i = 0; i < 2; ++i )
      {
        v129 = (double)i / 1.0;
        if ( unk_18CD388 )
        {
          v8 = rf_vector_subtract((const float *)(a3 + 104), v73, (const float *)(a3 + 92));
          v9 = rf_vector_scale((float *)v72, v129, v8);
          v10 = rf_vector_add((const float *)(a3 + 92), v71, v9);
          rf_vector_copy(&v152[3 * i], v70, v10);
        }
        else
        {
          v5 = rf_vector_subtract((const float *)(a3 + 24), out_vector, (const float *)(a3 + 12));
          v6 = rf_vector_scale((float *)v76, v129, v5);
          v7 = rf_vector_add((const float *)(a3 + 12), sum_result, v6);
          rf_vector_copy(&v152[3 * i], v74, v7);
        }
      }
      v146 = 127;
      v161 = 2;
    }
    else
    {
      if ( unk_18CD388 )
        rf_vector_copy(v152, v68, (const float *)(a3 + 92));
      else
        rf_vector_copy(v152, v69, (const float *)(a3 + 12));
      v146 = -1;
      v161 = 1;
    }
    v162 = 0;
    rf_dword_array_construct_capacity(v157, 0);
    v163 = 0;
    if ( *(_DWORD *)(a2 + 104) == -1 )
    {
      for ( j = rf_receiver_get_first_dword((void *)(a1 + 112)); j; j = rf_solid_face_next_link(j) )
      {
        if ( *(__int16 *)(j + 54) == *(_DWORD *)a2 )
        {
          v64 = operator new(0x104u);
          LOBYTE(v163) = 2;
          if ( v64 )
            v38 = rf_lightmap_polygon2_32_construct_empty((int)v64);
          else
            v38 = 0;
          v65 = v38;
          LOBYTE(v163) = 0;
          v123 = v38;
          for ( k = *(_DWORD *)(j + 64); k; k = v37 )
          {
            *(float *)(v123 + 8 * *(_DWORD *)(v123 + 256)) = (double)*(int *)(*(_DWORD *)(a2 + 12) + 4)
                                                           * *(float *)(k + 12)
                                                           - (double)*(int *)(a2 + 16);
            *(float *)(v123 + 8 * (*(_DWORD *)(v123 + 256))++ + 4) = (double)*(int *)(*(_DWORD *)(a2 + 12) + 8)
                                                                   * *(float *)(k + 16)
                                                                   - (double)*(int *)(a2 + 20);
            if ( *(_DWORD *)(k + 20) == *(_DWORD *)(j + 64) )
              v37 = 0;
            else
              v37 = *(_DWORD *)(k + 20);
          }
          rf_pointer_array_append_dword(v157, v123);
        }
      }
    }
    else
    {
      v128 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 144), *(_DWORD *)(a2 + 104));
      for ( m = rf_receiver_get_first_dword((void *)(v128 + 40)); m; m = rf_face_next_room_link(m) )
      {
        if ( *(__int16 *)(m + 54) == *(_DWORD *)a2 )
        {
          v66 = operator new(0x104u);
          LOBYTE(v163) = 1;
          if ( v66 )
            v40 = rf_lightmap_polygon2_32_construct_empty((int)v66);
          else
            v40 = 0;
          v67 = v40;
          LOBYTE(v163) = 0;
          v126 = v40;
          for ( n = *(_DWORD *)(m + 64); n; n = v39 )
          {
            *(float *)(v126 + 8 * *(_DWORD *)(v126 + 256)) = (double)*(int *)(*(_DWORD *)(a2 + 12) + 4)
                                                           * *(float *)(n + 12)
                                                           - (double)*(int *)(a2 + 16);
            *(float *)(v126 + 8 * (*(_DWORD *)(v126 + 256))++ + 4) = (double)*(int *)(*(_DWORD *)(a2 + 12) + 8)
                                                                   * *(float *)(n + 16)
                                                                   - (double)*(int *)(a2 + 20);
            if ( *(_DWORD *)(n + 20) == *(_DWORD *)(m + 64) )
              v39 = 0;
            else
              v39 = *(_DWORD *)(n + 20);
          }
          rf_pointer_array_append_dword(v157, v126);
        }
      }
    }
    for ( ii = 0; ii < v161; ++ii )
    {
      rf_vector3_copy_return_destination(lhs, &v152[3 * ii]);
      v11 = rf_vector_subtract(lhs, v63, rhs);
      rf_vector_copy(v136, v62, v11);
      rf_vector_normalize_reciprocal_sqrt(v136);
      if ( rf_vector_dot(v136, (float *)(a2 + 108)) <= 0.0 )
      {
        memset(a5, 0, *(_DWORD *)(a2 + 28) * *(_DWORD *)(a2 + 24));
        for ( jj = 0; ; ++jj )
        {
          first_dword = rf_receiver_get_first_dword(v157);
          if ( jj >= first_dword )
            break;
          v61 = *(void **)sub_552200(v157, jj);
          operator delete(v61);
        }
        goto LABEL_149;
      }
      v120 = 6;
      v116 = 1;
      rf_vector3_default_construct_noop(v118);
      rf_vector3_default_construct_noop(v115);
      rf_vector_copy(v118, v60, (const float *)(a2 + 52));
      rf_vector_copy(v115, v59, (const float *)(a2 + 64));
      rf_aabb_include_point_min_else_max(v118, v115, lhs);
      rf_vector3_copy_return_destination((float *)v114, (float *)(a2 + 108));
      v13 = (float *)rf_plane_construct_from_normal_point(v58, (float *)v114, (int)lhs);
      rf_plane_copy(v137, v13);
      v14 = rf_vector_negate((float *)v114, (float *)v56);
      v15 = (float *)rf_plane_construct_from_normal_point(v57, v14, (int)rhs);
      rf_plane_copy(v138, v15);
      v16 = (float *)rf_plane_construct_from_three_world_points(v55, lhs, (int)v145, (int)v158);
      rf_plane_copy(v139, v16);
      v17 = (float *)rf_plane_construct_from_three_world_points(v54, lhs, (int)v131, (int)v145);
      rf_plane_copy(v140, v17);
      v18 = (float *)rf_plane_construct_from_three_world_points(v53, lhs, (int)v158, (int)v160);
      rf_plane_copy(v141, v18);
      v19 = (float *)rf_plane_construct_from_three_world_points(v52, lhs, (int)v160, (int)v131);
      rf_plane_copy(v142, v19);
      for ( kk = 0; kk < 6; ++kk )
      {
        if ( rf_plane_point_signed_distance(&v137[4 * kk], rhs) > 0.0 )
        {
          v20 = rf_vector_negate(&v137[4 * kk], (float *)v51);
          rf_vector_copy(&v137[4 * kk], v50, v20);
          v137[4 * kk + 3] = -v137[4 * kk + 3];
        }
      }
      v21 = rf_vector_negate((float *)(a2 + 108), (float *)v49);
      rf_vector_copy(v138, v48, v21);
      v138[3] = -*(float *)(a2 + 120);
      for ( kk = 0; kk < 6; ++kk )
        rf_plane_select_aabb_support_corners(&v137[4 * kk], &v158[kk + 3], &v145[kk + 3]);
      if ( a4 )
      {
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_draw_noop();
        rf_lightmap_shadow_debug_flush_noop();
      }
      for ( mm = (float *)rf_receiver_get_first_dword((void *)(a1 + 112));
            mm;
            mm = (float *)rf_solid_face_next_link((int)mm) )
      {
        if ( rf_aabb_overlap_strict_ordered(&destination, &v149, mm + 4, mm + 7)
          && rf_aabb_overlap_strict_ordered(v118, v115, mm + 4, mm + 7)
          && *((__int16 *)mm + 26) <= 0
          && ((_DWORD)mm[10] & 4) == 0
          && ((_DWORD)mm[10] & 0x40) == 0
          && ((_DWORD)mm[10] & 0x2000) == 0
          && *((__int16 *)mm + 27) != *(_DWORD *)a2
          && (*((_DWORD *)mm + 12) == -1 || !rf_bitmap_resolved_format_is_4_5_7(*((_DWORD *)mm + 12))) )
        {
          v36 = fabs(mm[3] - *(float *)(a2 + 120));
          if ( v36 >= 0.001000000047497451 || (v96 = rf_vector_dot(mm, (float *)(a2 + 108)), v96 <= 0.9990000128746033) )
          {
            v107 = 0;
            for ( jj = 0; jj < v120; ++jj )
            {
              rf_vector3_default_construct_noop(v95);
              rf_aabb_select_corner_by_index(v95, v158[jj + 3], mm + 4, mm + 7);
              if ( rf_plane_point_signed_distance(&v137[4 * jj], v95) > -0.001 )
              {
                v107 = 1;
                break;
              }
            }
            if ( !v107 )
            {
              v98 = *((_DWORD *)mm + 16);
              v103 = 0;
              while ( v98 )
              {
                v35 = (float *)((char *)&unk_15A6E48 + 12 * v103++);
                rf_vector_copy(v35, v47, *(const float **)v98);
                if ( *(_DWORD *)(v98 + 20) == *((_DWORD *)mm + 16) )
                  v34 = 0;
                else
                  v34 = *(_DWORD *)(v98 + 20);
                v98 = v34;
              }
              v108 = &unk_15A6E48;
              v111 = &unk_15A6B48;
              for ( jj = 0; jj < v120; ++jj )
              {
                v94 = rf_clip_polygon_against_plane(v103, (int)v108, (int)v111, (int)&v137[4 * jj]);
                if ( v94 < 3 )
                {
                  v103 = 0;
                  break;
                }
                v103 = v94;
                v93 = v108;
                v108 = v111;
                v111 = v93;
              }
              if ( v103 >= 3 )
              {
                rf_vector_construct_no_unwind((char *)Src, 8u, 64, rf_vector3_default_construct_noop);
                v99 = 0;
                rf_vector3_default_construct_noop(source);
                rf_vector3_default_construct_noop(v104);
                rf_vector2_assign_components(v97, 0.0, 0.0);
                v110 = 0;
                for ( jj = 0; jj < v103; ++jj )
                {
                  rf_force_sample44_construct_vectors_noop((char *)v91);
                  v22 = rf_vector_subtract((const float *)v108 + 3 * jj, v46, lhs);
                  rf_vector_copy(v92, v45, v22);
                  rf_vector_copy(v91, v44, lhs);
                  if ( a4 )
                    rf_lightmap_shadow_debug_draw_noop();
                  if ( !rf_ray_intersect_plane_write_point_if_nonparallel((int)v91, (int)&v137[4 * v116], source) )
                  {
                    ++v99;
                    break;
                  }
                  if ( a4 && jj > 0 )
                    rf_lightmap_shadow_debug_draw_noop();
                  rf_vector_copy(v104, v43, source);
                  v30 = *(float *)rf_vector_component_address_unchecked((char *)source, *(_DWORD *)(a2 + 100));
                  v23 = (float *)rf_vector_component_address_unchecked((char *)source, *(_DWORD *)(a2 + 96));
                  rf_vector2_assign_components(&v89, *v23, v30);
                  v89 = v89 * *(float *)(a2 + 76);
                  v90 = v90 * *(float *)(a2 + 80);
                  rf_vector2_accumulate(&v89, (float *)(a2 + 84));
                  v89 = (double)*(int *)(*(_DWORD *)(a2 + 12) + 4) * v89;
                  v90 = (double)*(int *)(*(_DWORD *)(a2 + 12) + 8) * v90;
                  v89 = v89 - (double)*(int *)(a2 + 16);
                  v90 = v90 - (double)*(int *)(a2 + 20);
                  if ( v89 >= 1.0 )
                  {
                    if ( v89 > (double)(*(_DWORD *)(a2 + 24) - 1) )
                      v89 = (float)(*(_DWORD *)(a2 + 24) - 1);
                  }
                  else
                  {
                    v89 = 1.0;
                  }
                  if ( v90 >= 1.0 )
                  {
                    if ( v90 > (double)(*(_DWORD *)(a2 + 28) - 1) )
                      v90 = (float)(*(_DWORD *)(a2 + 28) - 1);
                  }
                  else
                  {
                    v90 = 1.0;
                  }
                  if ( v110 <= 0 )
                  {
                    v32 = &Src[2 * v110++];
                    rf_vector2_copy_return_source(v32, &v89);
                    rf_vector2_copy_return_source(v97, &v89);
                  }
                  else if ( v97[0] != v89 || v97[1] != v90 )
                  {
                    v33 = &Src[2 * v110++];
                    rf_vector2_copy_return_source(v33, &v89);
                    rf_vector2_copy_return_source(v97, &v89);
                  }
                }
                if ( !v99 )
                {
                  v162 = 1;
                  if ( *(float *)&v105[8 * v110 + 504] == Src[0] && *(float *)&v105[8 * v110 + 508] == Src[1] )
                    --v110;
                  v100 = 0;
                  rf_vector_construct_no_unwind(v105, 8u, 64, rf_vector3_default_construct_noop);
                  rf_vector_construct_no_unwind((char *)v102, 8u, 64, rf_vector3_default_construct_noop);
                  v112 = v110;
                  v101 = (float *)v105;
                  while ( 1 )
                  {
                    v24 = rf_receiver_get_first_dword(v157);
                    if ( v100 >= v24 )
                      break;
                    v88 = v101;
                    memcpy(v102, Src, 8 * v112);
                    v31 = 8 * *(_DWORD *)(*(_DWORD *)sub_552200(v157, v100) + 256);
                    v25 = (const void **)sub_552200(v157, v100);
                    memcpy(v105, *v25, v31);
                    v29 = (int)v101;
                    v26 = sub_552200(v157, v100);
                    v110 = rf_clip_polygon2_against_convex_edges(
                             v112,
                             v102,
                             *(_DWORD *)(*(_DWORD *)v26 + 256),
                             (int)v105,
                             v29,
                             &v88);
                    ++v100;
                    if ( v110 > 2 )
                    {
                      if ( *(float *)(a2 + 44) * *(float *)(a2 + 48) < rf_polygon2_area_triangle_fan_heron(v110, v88) )
                        break;
                      v110 = 0;
                    }
                  }
                  if ( v110 > 2 )
                    rf_lightmap_shadow_mask_subtract_polygon_scanlines(
                      a2,
                      v112,
                      (int)v102,
                      (int)a5,
                      *(_DWORD *)(a2 + 24),
                      *(_DWORD *)(a2 + 28),
                      v146);
                }
              }
            }
          }
        }
      }
    }
    for ( jj = 0; ; ++jj )
    {
      v27 = rf_receiver_get_first_dword(v157);
      if ( jj >= v27 )
        break;
      v28 = (void **)sub_552200(v157, jj);
      operator delete(*v28);
    }
    if ( v162 == 1 )
    {
      for ( nn = 0; nn < *(_DWORD *)(a2 + 28); ++nn )
      {
        v86 = *(_DWORD *)(a2 + 24) * nn;
        v85 = v86 + *(_DWORD *)(a2 + 24) - 1;
        a5[v86] = a5[v86 + 1];
        a5[v85] = a5[v85 - 1];
      }
      for ( i1 = 0; i1 < *(_DWORD *)(a2 + 24); ++i1 )
      {
        v83 = i1;
        v82 = i1 + *(_DWORD *)(a2 + 24) * (*(_DWORD *)(a2 + 28) - 1);
        a5[i1] = a5[*(_DWORD *)(a2 + 24) + i1];
        a5[v82] = a5[v82 - *(_DWORD *)(a2 + 24)];
      }
    }
LABEL_149:
    v163 = -1;
    rf_pointer_array_destroy_backing_storage(v157);
  }
}

