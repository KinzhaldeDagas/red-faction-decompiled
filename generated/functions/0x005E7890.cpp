// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7890 rf_world_room_packets_draw_base_decals_and_lights
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(worldReceiver,roomPointerArray,signedCount),VOID behavior;old additive-only name/int return incomplete. Increments call epoch1E41990 and accumulated time1E4198C by frame delta PER CALL,snapshots camera/projection,decal head/count,flushes pending immediate buffers when1E014E5,sets direct-world flag1E014E6. Builds active lights with(receiver,1,0),retains cached spatial order;later uses only first min(count,32),without importance sort. Per room,rebuilds absent/state2 packet via54AE50;first failure rewinds shared scratch arena/clears tracked owner pointers then retries once,second failure skips room. Selects room clip aperture,classifies AABB:outside skips,fully inside tests front-facing planes
// directly,intersecting traverses44-byte packet BVH with per-node plane mask/stamp. Restores full aperture before draws. Builds visible vertex marks and conditional face light masks by testing light center inside node AABB expanded by range;no Euclidean sphere/AABB test. Zero-overlap branches do not blanket-clear prior face mask words. Projects referenced vertices into20-byte cached XY/depth/rhw/fog/outcode records;663F06 chooses clipping-aware path vs faster prescaled-matrix path,not projection-mode byte663F39. Both use reciprocal cameraZ,no own zero/finite guard. Base groups80bytes:packedState32,diffuse36,vertexMap40,UV4f44,faces28B48,visibility52,tex0/1 at64/68,signed16 vertex/face/triangle counts72/74/76. Applies group packed state,binds tex0 when changed and tex1 each group;bind failure skips base group. Scroll flag16 mutates time20,offsets0/4 and primary
// UVs:delta=elapsed*speed,subtract floor(OLD offset) ONLY if OLD offset>1,then add delta;not general modulo of new offset,negative offsets not wrapped. Uses shared40-byte VB/WORD IB at offsets18CCFBC/FC0. Base reservation=count and3*triangles,plus768 each when clipping;if reservation+offset>=6000/10000 restarts offsets0 but DOES NOT clamp oversized base request. Locks/draw HRESULTs ignored. Writes XYZRHW0..15,diffuse16..19,fog byte23,UV0/UV1 at24..39;specular RGB bytes20..22 not explicitly initialized here. Unclipped faces fan-triangulated;partially outcoded faces copied to48-entry clip48 scratch,clip dispatcher planes01..40(mask3 preserves both UVs),projects ALL returned vertices and fans. Base clipped append requires strict vertex/index-end headroom;no explicit per-vertex projection-reject check after clip call. Dispatcher does not process80,so not guaranteed near-plane clipping. Base
// indexed draw precedes decals and projected lights. Decals:enable663F04 and positive count;select matching room face fragments/visible source face,temporary scaled bias0.025,white globalRGBA,state(2,0,2,3,1,0),25 local clip48 slots,submit mask9;reset bias0 after optional flush. Dynamic lights:select dual-stage light/detail state if two capability flags else single-stage glow state;no fog restore afterward. Counts eligible non-special visible face/light pairs;clamps per-light reservations6000 vertices/10000 indices(+768 clipping allowance before clamp). Capacity miss inside a group skips its remaining faces for that light rather than flushing/retrying. Each record uses position/range/RGB without branching on renderer light type. Face distance d admitted by -R<=d<R;project center onto face,projected scale=R*cos(abs(d)*pi/2/R),brightness=max(255-abs(d)*255/R,0). RGB converted with legacy
// float-to-byte helper,alphaFF. UV0=face-basis dot(worldVertex-projectedCenter)/projectedScale+0.5 (no factor2),UV1=original PRIMARY UV*4. Clipped and unclipped paths fan-triangulate;light vertex fog byteFF. At end direct-world flag0,active-light-valid/count cleared. Global color/textures/packed state not saved/restored. Fixed scratch arrays/traversal stacks/count assumptions unchecked;global mutable state,not reentrant.
void __cdecl rf_world_room_packets_draw_base_decals_and_lights(void *a1, void *const *a2, int a3)
{
  char v3; // al
  char v4; // al
  double v5; // st7
  char v6; // al
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  char v11; // al
  int *v12; // eax
  float *v13; // eax
  double v14; // st7
  char v15; // al
  char v16; // al
  char v17; // al
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  float value; // [esp+2Ch] [ebp-2C4A8h]
  float v24; // [esp+34h] [ebp-2C4A0h]
  float v25; // [esp+38h] [ebp-2C49Ch]
  float v26; // [esp+3Ch] [ebp-2C498h]
  float v27; // [esp+40h] [ebp-2C494h]
  float v28; // [esp+44h] [ebp-2C490h]
  float v29; // [esp+48h] [ebp-2C48Ch]
  int v30; // [esp+4Ch] [ebp-2C488h]
  int v31; // [esp+50h] [ebp-2C484h]
  int v32; // [esp+54h] [ebp-2C480h]
  unsigned int v33; // [esp+58h] [ebp-2C47Ch]
  int *v34; // [esp+5Ch] [ebp-2C478h]
  int v35; // [esp+60h] [ebp-2C474h]
  float v36; // [esp+64h] [ebp-2C470h]
  float v37; // [esp+68h] [ebp-2C46Ch]
  float v38; // [esp+6Ch] [ebp-2C468h]
  float v39; // [esp+70h] [ebp-2C464h]
  float v40; // [esp+74h] [ebp-2C460h]
  float v41; // [esp+78h] [ebp-2C45Ch]
  unsigned int v42; // [esp+7Ch] [ebp-2C458h]
  float v43[3]; // [esp+80h] [ebp-2C454h] BYREF
  float scaled_result[3]; // [esp+8Ch] [ebp-2C448h] BYREF
  int v45; // [esp+98h] [ebp-2C43Ch] BYREF
  float copy_result[3]; // [esp+9Ch] [ebp-2C438h] BYREF
  int v47; // [esp+A8h] [ebp-2C42Ch]
  float v48[3]; // [esp+ACh] [ebp-2C428h] BYREF
  float *v49; // [esp+B8h] [ebp-2C41Ch]
  int v50; // [esp+BCh] [ebp-2C418h]
  float out_vector[3]; // [esp+C0h] [ebp-2C414h] BYREF
  __int16 v52; // [esp+CCh] [ebp-2C408h]
  int v53; // [esp+D0h] [ebp-2C404h] BYREF
  int v54; // [esp+D4h] [ebp-2C400h]
  __int16 v55; // [esp+D8h] [ebp-2C3FCh]
  float *v56; // [esp+DCh] [ebp-2C3F8h]
  __int16 v57; // [esp+E0h] [ebp-2C3F4h]
  _DWORD *v58; // [esp+E4h] [ebp-2C3F0h]
  _DWORD *v59; // [esp+E8h] [ebp-2C3ECh]
  int i7; // [esp+ECh] [ebp-2C3E8h]
  __int16 v61; // [esp+F0h] [ebp-2C3E4h]
  float v62; // [esp+F4h] [ebp-2C3E0h]
  float v63; // [esp+F8h] [ebp-2C3DCh]
  int v64; // [esp+FCh] [ebp-2C3D8h] BYREF
  float v65; // [esp+100h] [ebp-2C3D4h]
  float rhs[3]; // [esp+104h] [ebp-2C3D0h] BYREF
  int *v67; // [esp+110h] [ebp-2C3C4h]
  int v68; // [esp+114h] [ebp-2C3C0h]
  __int16 v69; // [esp+118h] [ebp-2C3BCh]
  __int16 v70; // [esp+11Ch] [ebp-2C3B8h]
  int v71; // [esp+120h] [ebp-2C3B4h]
  float *v72; // [esp+124h] [ebp-2C3B0h]
  int v73; // [esp+128h] [ebp-2C3ACh]
  int v74; // [esp+12Ch] [ebp-2C3A8h]
  float *v75; // [esp+130h] [ebp-2C3A4h]
  _WORD *v76; // [esp+134h] [ebp-2C3A0h] BYREF
  int v77; // [esp+138h] [ebp-2C39Ch]
  int v78; // [esp+13Ch] [ebp-2C398h] BYREF
  int v79; // [esp+140h] [ebp-2C394h]
  int v80; // [esp+144h] [ebp-2C390h]
  int v81; // [esp+148h] [ebp-2C38Ch]
  int v82; // [esp+14Ch] [ebp-2C388h]
  int v83; // [esp+150h] [ebp-2C384h]
  __int16 *v84; // [esp+154h] [ebp-2C380h]
  int v85; // [esp+158h] [ebp-2C37Ch]
  signed int v86; // [esp+15Ch] [ebp-2C378h]
  int i6; // [esp+160h] [ebp-2C374h]
  char v88[1200]; // [esp+164h] [ebp-2C370h] BYREF
  int v89[26]; // [esp+614h] [ebp-2BEC0h] BYREF
  int *i5; // [esp+67Ch] [ebp-2BE58h]
  int i4; // [esp+680h] [ebp-2BE54h]
  int i3; // [esp+684h] [ebp-2BE50h]
  int v93; // [esp+688h] [ebp-2BE4Ch]
  int v94; // [esp+68Ch] [ebp-2BE48h]
  int v95; // [esp+690h] [ebp-2BE44h]
  int v96; // [esp+694h] [ebp-2BE40h] BYREF
  int i2; // [esp+698h] [ebp-2BE3Ch]
  float *destination; // [esp+69Ch] [ebp-2BE38h]
  _DWORD *v99; // [esp+6A0h] [ebp-2BE34h]
  int i1; // [esp+6A4h] [ebp-2BE30h]
  __int16 *v101; // [esp+6A8h] [ebp-2BE2Ch]
  float *v102; // [esp+6ACh] [ebp-2BE28h]
  _DWORD *v103; // [esp+6B0h] [ebp-2BE24h]
  int v104; // [esp+6B4h] [ebp-2BE20h]
  int nn; // [esp+6B8h] [ebp-2BE1Ch]
  __int16 *v106; // [esp+6BCh] [ebp-2BE18h]
  float v107; // [esp+6C0h] [ebp-2BE14h]
  float v108; // [esp+6C4h] [ebp-2BE10h]
  float v109; // [esp+6C8h] [ebp-2BE0Ch]
  _BYTE *v110; // [esp+6CCh] [ebp-2BE08h]
  int v111; // [esp+6D0h] [ebp-2BE04h]
  float *v112; // [esp+6D4h] [ebp-2BE00h]
  _BYTE *v113; // [esp+6D8h] [ebp-2BDFCh]
  char v114[12]; // [esp+6DCh] [ebp-2BDF8h] BYREF
  int v115; // [esp+6E8h] [ebp-2BDECh]
  char v116[12]; // [esp+6ECh] [ebp-2BDE8h] BYREF
  int v117; // [esp+6F8h] [ebp-2BDDCh]
  int v118; // [esp+6FCh] [ebp-2BDD8h]
  _WORD *v119; // [esp+700h] [ebp-2BDD4h]
  char *v120; // [esp+704h] [ebp-2BDD0h]
  unsigned int v121; // [esp+708h] [ebp-2BDCCh]
  int v122; // [esp+70Ch] [ebp-2BDC8h]
  int v123; // [esp+710h] [ebp-2BDC4h]
  int v124; // [esp+714h] [ebp-2BDC0h]
  float *v125; // [esp+718h] [ebp-2BDBCh]
  float *v126; // [esp+71Ch] [ebp-2BDB8h]
  float *v127; // [esp+720h] [ebp-2BDB4h]
  int v128; // [esp+724h] [ebp-2BDB0h]
  int jj; // [esp+728h] [ebp-2BDACh]
  int v130; // [esp+72Ch] [ebp-2BDA8h]
  char v131[12]; // [esp+730h] [ebp-2BDA4h] BYREF
  char v132[12]; // [esp+73Ch] [ebp-2BD98h] BYREF
  int v133; // [esp+748h] [ebp-2BD8Ch]
  int v134; // [esp+74Ch] [ebp-2BD88h]
  int v135; // [esp+750h] [ebp-2BD84h]
  int v136; // [esp+754h] [ebp-2BD80h]
  signed int v137; // [esp+758h] [ebp-2BD7Ch]
  _BYTE *v138; // [esp+75Ch] [ebp-2BD78h]
  __int16 *n; // [esp+760h] [ebp-2BD74h]
  int v140; // [esp+764h] [ebp-2BD70h]
  __int16 *v141; // [esp+768h] [ebp-2BD6Ch]
  int v142; // [esp+76Ch] [ebp-2BD68h]
  int v143; // [esp+770h] [ebp-2BD64h]
  int m; // [esp+774h] [ebp-2BD60h]
  int v145; // [esp+778h] [ebp-2BD5Ch] BYREF
  int v146; // [esp+77Ch] [ebp-2BD58h]
  _BYTE *v147; // [esp+780h] [ebp-2BD54h]
  __int16 *k; // [esp+784h] [ebp-2BD50h]
  int v149; // [esp+788h] [ebp-2BD4Ch]
  __int16 *v150; // [esp+78Ch] [ebp-2BD48h]
  int v151; // [esp+790h] [ebp-2BD44h]
  int v152; // [esp+794h] [ebp-2BD40h]
  int v153; // [esp+798h] [ebp-2BD3Ch]
  void *v154; // [esp+79Ch] [ebp-2BD38h]
  int v155; // [esp+7A0h] [ebp-2BD34h]
  int v156; // [esp+7A4h] [ebp-2BD30h] BYREF
  int v157; // [esp+7A8h] [ebp-2BD2Ch]
  int v158; // [esp+7ACh] [ebp-2BD28h]
  int v159; // [esp+7B0h] [ebp-2BD24h]
  _WORD *v160; // [esp+7B4h] [ebp-2BD20h] BYREF
  _DWORD *v161; // [esp+7B8h] [ebp-2BD1Ch]
  int v162; // [esp+7BCh] [ebp-2BD18h]
  float v163; // [esp+7C0h] [ebp-2BD14h]
  float v164; // [esp+7C4h] [ebp-2BD10h] BYREF
  float v165; // [esp+7C8h] [ebp-2BD0Ch]
  float v166; // [esp+7CCh] [ebp-2BD08h]
  float v167[3]; // [esp+7D0h] [ebp-2BD04h] BYREF
  float v168[6]; // [esp+7DCh] [ebp-2BCF8h] BYREF
  float v169; // [esp+7F4h] [ebp-2BCE0h]
  _BYTE *v170; // [esp+7F8h] [ebp-2BCDCh]
  int v171; // [esp+7FCh] [ebp-2BCD8h] BYREF
  float v172; // [esp+800h] [ebp-2BCD4h]
  _DWORD v173[48]; // [esp+804h] [ebp-2BCD0h] BYREF
  char v174[4]; // [esp+8C4h] [ebp-2BC10h] BYREF
  int mm; // [esp+8C8h] [ebp-2BC0Ch]
  float v176; // [esp+8CCh] [ebp-2BC08h]
  float v177; // [esp+8D0h] [ebp-2BC04h]
  _DWORD v178[33]; // [esp+8D4h] [ebp-2BC00h] BYREF
  int v179; // [esp+958h] [ebp-2BB7Ch]
  int v180; // [esp+95Ch] [ebp-2BB78h]
  float v181; // [esp+960h] [ebp-2BB74h]
  char v182[2304]; // [esp+964h] [ebp-2BB70h] BYREF
  _WORD v183[48]; // [esp+1264h] [ebp-2B270h]
  _DWORD v184[48]; // [esp+12C4h] [ebp-2B210h] BYREF
  char v185[4]; // [esp+1384h] [ebp-2B150h] BYREF
  int kk; // [esp+1388h] [ebp-2B14Ch]
  int j; // [esp+138Ch] [ebp-2B148h]
  float v188[9]; // [esp+1390h] [ebp-2B144h] BYREF
  float v189; // [esp+13B4h] [ebp-2B120h]
  float v190; // [esp+13B8h] [ebp-2B11Ch]
  _DWORD v191[32]; // [esp+13BCh] [ebp-2B118h] BYREF
  _DWORD v192[1025]; // [esp+143Ch] [ebp-2B098h]
  float v193; // [esp+2440h] [ebp-2A094h]
  _BYTE v194[8004]; // [esp+2444h] [ebp-2A090h] BYREF
  float v195[3]; // [esp+438Ch] [ebp-28148h] BYREF
  float v196[6]; // [esp+4398h] [ebp-2813Ch] BYREF
  int i; // [esp+43B0h] [ebp-28124h]
  _DWORD v198[1025]; // [esp+43B4h] [ebp-28120h]
  char v199; // [esp+53B8h] [ebp-2711Ch] BYREF
  char v200; // [esp+53B9h] [ebp-2711Bh]
  char v201; // [esp+53BFh] [ebp-27115h]
  float v202; // [esp+53C0h] [ebp-27114h]
  _DWORD v203[40001]; // [esp+53C4h] [ebp-27110h] BYREF
  signed int ii; // [esp+2C4C8h] [ebp-Ch]
  float v205; // [esp+2C4CCh] [ebp-8h]
  int v206; // [esp+2C4D0h] [ebp-4h] BYREF

  ++unk_1E41990;
  unk_1E4198C = unk_1E4198C + rf_frame_delta_seconds;
  rf_matrix3_copy_construct((int)v188, &flt_18CD4B4);
  rf_matrix3_copy_construct((int)v195, v188);
  rf_vector3_copy_return_destination(&v164, &flt_18CD5E8);
  rf_matrix3_construct((char *)v167);
  v189 = unk_18CD35C;
  v181 = unk_18CD364;
  v190 = unk_18CD358;
  v176 = unk_18CD360;
  v193 = unk_187CD00;
  rf_world_decal_get_active_head_and_count(&v206, &v171);
  rf_vector_construct_no_unwind(v182, 0x30u, 48, rf_vector_prefix_construct_noop);
  v201 = byte_663F06;
  if ( unk_1E014E5 )
    rf_renderer_flush_immediate_buffers();
  unk_1E014E6 = 1;
  if ( !v201 )
  {
    rf_vector3_scale_in_place_return_self(v195, unk_18CD35C);
    rf_vector3_scale_in_place_return_self(v196, unk_18CD364);
  }
  rf_light_build_active_list_for_world_receiver((int)a1, 1, 0);
  for ( i = 0; i < a3; ++i )
  {
    v154 = a2[i];
    if ( !*((_DWORD *)v154 + 1) || *(_DWORD *)(*((_DWORD *)v154 + 1) + 32) == 2 )
    {
      if ( rf_world_room_build_render_packets((int)a1, (int)v154) )
      {
        rf_scratch_arena_rewind_and_clear_owners();
        if ( rf_world_room_build_render_packets((int)a1, (int)v154) )
          continue;
      }
      if ( !*((_DWORD *)v154 + 1) )
        continue;
    }
    rf_renderer_select_room_clip_aperture((int)v154);
    v153 = *((_DWORD *)v154 + 1);
    memset(v194, 255, *(_DWORD *)(v153 + 4));
    v158 = rf_frustum_classify_aabb((float *)v154 + 2, (float *)v154 + 5);
    if ( v158 == -1 )
    {
      v170 = *(_BYTE **)(v153 + 16);
      for ( j = 0; j < *(unsigned __int16 *)(v153 + 24); ++j )
      {
        v151 = *(_DWORD *)(v153 + 20) + 80 * j;
        if ( *(_BYTE *)(v151 + 24) )
        {
          v170 += *(__int16 *)(v151 + 74);
        }
        else
        {
          v152 = *(_DWORD *)(v151 + 40);
          v179 = 0;
          while ( v179 < *(__int16 *)(v151 + 74) )
          {
            v150 = (__int16 *)(*(_DWORD *)(v151 + 48) + 28 * v179);
            if ( rf_plane_point_signed_distance((float *)v150 + 2, &v164) > 0.0 )
            {
              *v170 = 0;
              v149 = *((_DWORD *)v150 + 1) + 2 * *v150;
              for ( k = *((__int16 **)v150 + 1); k != (__int16 *)v149; ++k )
              {
                v147 = &v194[*(__int16 *)(v152 + 2 * *k)];
                if ( *v147 )
                  *v147 = 0;
              }
            }
            else
            {
              *v170 = -1;
            }
            ++v179;
            ++v170;
          }
        }
      }
    }
    else
    {
      if ( v158 )
      {
        rf_renderer_select_room_clip_aperture(0);
        continue;
      }
      memset(*(void **)(v153 + 16), 255, *(_DWORD *)(v153 + 8));
      v192[0] = *(_DWORD *)(v153 + 28);
      v198[0] = -1;
      v180 = 1;
      while ( v180 > 0 )
      {
        v146 = v192[--v180];
        v145 = v198[v180];
        if ( !v145 || !rf_frustum_reject_aabb_update_plane_mask((float *)(v146 + 4), (float *)(v146 + 16), &v145) )
        {
          *(_DWORD *)v146 = unk_1E41990;
          if ( *(_DWORD *)(v146 + 28) )
          {
            v192[v180] = *(_DWORD *)(v146 + 28);
            v198[v180++] = v145;
          }
          if ( *(_DWORD *)(v146 + 32) )
          {
            v192[v180] = *(_DWORD *)(v146 + 32);
            v198[v180++] = v145;
          }
          if ( *(_DWORD *)(v146 + 36) )
          {
            for ( m = 0; m < *(_DWORD *)(v146 + 36); ++m )
            {
              if ( *(__int16 *)(*(_DWORD *)(v146 + 40) + 2 * m) >= 0
                && *(__int16 *)(*(_DWORD *)(v146 + 40) + 2 * m) < *(_DWORD *)(v153 + 8) )
              {
                *(_BYTE *)(*(__int16 *)(*(_DWORD *)(v146 + 40) + 2 * m) + *(_DWORD *)(v153 + 16)) = 0;
              }
            }
          }
        }
      }
      v170 = *(_BYTE **)(v153 + 16);
      for ( j = 0; j < *(unsigned __int16 *)(v153 + 24); ++j )
      {
        v142 = *(_DWORD *)(v153 + 20) + 80 * j;
        if ( *(_BYTE *)(v142 + 24) )
        {
          v170 += *(__int16 *)(v142 + 74);
        }
        else
        {
          v143 = *(_DWORD *)(v142 + 40);
          v179 = 0;
          while ( v179 < *(__int16 *)(v142 + 74) )
          {
            v141 = (__int16 *)(*(_DWORD *)(v142 + 48) + 28 * v179);
            if ( !*v170 )
            {
              if ( rf_plane_point_signed_distance((float *)v141 + 2, &v164) > 0.0 )
              {
                v140 = *((_DWORD *)v141 + 1) + 2 * *v141;
                for ( n = *((__int16 **)v141 + 1); n != (__int16 *)v140; ++n )
                {
                  v138 = &v194[*(__int16 *)(v143 + 2 * *n)];
                  if ( *v138 )
                    *v138 = 0;
                }
              }
              else
              {
                *v170 = -1;
              }
            }
            ++v179;
            ++v170;
          }
        }
      }
    }
    rf_renderer_select_room_clip_aperture(0);
    if ( rf_light_active_world_count )
    {
      if ( (int)rf_light_active_world_count <= 32 )
        v42 = rf_light_active_world_count;
      else
        v42 = 32;
      v137 = v42;
      v192[0] = *(_DWORD *)(v153 + 28);
      v198[0] = -1;
      v180 = 1;
      while ( v180 > 0 )
      {
        v134 = v192[--v180];
        v135 = v198[v180];
        if ( v158 || *(_DWORD *)v134 == unk_1E41990 )
        {
          v136 = 0;
          for ( ii = 0; ii < v137; ++ii )
          {
            v133 = 1 << ii;
            if ( ((1 << ii) & v135) != 0 )
            {
              v130 = rf_light_active_world_records[ii];
              v41 = *(float *)(v134 + 12) - *(float *)(v130 + 60);
              v40 = *(float *)(v134 + 8) - *(float *)(v130 + 60);
              v39 = *(float *)(v134 + 4) - *(float *)(v130 + 60);
              rf_vector3_set_components_return_destination((float *)v132, v39, v40, v41);
              v38 = *(float *)(v134 + 24) + *(float *)(v130 + 60);
              v37 = *(float *)(v134 + 20) + *(float *)(v130 + 60);
              v36 = *(float *)(v134 + 16) + *(float *)(v130 + 60);
              rf_vector3_set_components_return_destination((float *)v131, v36, v37, v38);
              if ( rf_aabb_contains_point_inclusive((float *)(v130 + 12), (float *)v132, (float *)v131) )
                v136 |= v133;
            }
          }
          if ( v136 )
          {
            if ( *(_DWORD *)(v134 + 28) )
            {
              v192[v180] = *(_DWORD *)(v134 + 28);
              v198[v180++] = v136;
            }
            if ( *(_DWORD *)(v134 + 32) )
            {
              v192[v180] = *(_DWORD *)(v134 + 32);
              v198[v180++] = v136;
            }
            for ( jj = 0; jj < *(_DWORD *)(v134 + 36); ++jj )
            {
              if ( *(__int16 *)(*(_DWORD *)(v134 + 40) + 2 * jj) >= 0
                && *(__int16 *)(*(_DWORD *)(v134 + 40) + 2 * jj) < *(_DWORD *)(v153 + 8)
                && !*(_BYTE *)(*(_DWORD *)(v153 + 16) + *(__int16 *)(*(_DWORD *)(v134 + 40) + 2 * jj)) )
              {
                v128 = *(_DWORD *)(v153 + 12) + 28 * *(__int16 *)(*(_DWORD *)(v134 + 40) + 2 * jj);
                *(_DWORD *)(v128 + 24) = v136;
              }
            }
          }
        }
      }
    }
    v170 = v194;
    if ( v201 )
    {
      v127 = flt_1C998E0;
      kk = 0;
      while ( kk < *(_DWORD *)(v153 + 4) )
      {
        if ( !*v170 )
        {
          v161 = &v203[5 * kk];
          v126 = (float *)(*(_DWORD *)v153 + 12 * kk);
          v172 = *v126 - v164;
          v169 = v126[1] - v165;
          v177 = v126[2] - v166;
          *v127 = v172 * v188[0] + v169 * v188[1] + v177 * v188[2];
          v127[1] = v172 * v188[3] + v169 * v188[4] + v177 * v188[5];
          v205 = v172 * v188[6] + v169 * v188[7] + v177 * v188[8];
          v127[2] = v205;
          v3 = rf_camera_frustum_outcode(v127);
          *((_BYTE *)v161 + 17) = v3;
          if ( !*((_BYTE *)v161 + 17) )
          {
            v4 = rf_world_depth_fog_byte(v205, v193);
            *((_BYTE *)v161 + 16) = v4;
            v205 = 1.0 / v205;
            *(float *)v161 = *v127 * v205 * v189 + v190;
            *((float *)v161 + 1) = v127[1] * v205 * v181 + v176;
            v5 = rf_renderer_scale_reciprocal_depth(v205);
            *((float *)v161 + 2) = v5;
            *((float *)v161 + 3) = v205 * flt_6649F8;
          }
        }
        ++kk;
        ++v170;
        v127 += 3;
      }
    }
    else
    {
      kk = 0;
      while ( kk < *(_DWORD *)(v153 + 4) )
      {
        if ( !*v170 )
        {
          v161 = &v203[5 * kk];
          v125 = (float *)(*(_DWORD *)v153 + 12 * kk);
          v172 = *v125 - v164;
          v169 = v125[1] - v165;
          v177 = v125[2] - v166;
          v163 = v172 * v195[0] + v169 * v195[1] + v177 * v195[2];
          v202 = v172 * v196[0] + v169 * v196[1] + v177 * v196[2];
          v205 = v172 * v196[3] + v169 * v196[4] + v177 * v196[5];
          v6 = rf_world_depth_fog_byte(v205, v193);
          *((_BYTE *)v161 + 16) = v6;
          v205 = 1.0 / v205;
          *(float *)v161 = v163 * v205 + v190;
          *((float *)v161 + 1) = v202 * v205 + v176;
          v7 = rf_renderer_scale_reciprocal_depth(v205);
          *((float *)v161 + 2) = v7;
          *((float *)v161 + 3) = v205 * flt_6649F8;
        }
        ++kk;
        ++v170;
      }
    }
    v159 = dword_18CCFBC;
    v162 = unk_18CCFC0;
    v156 = 0;
    v160 = nullptr;
    v155 = -1;
    for ( kk = 0; kk < *(unsigned __int16 *)(v153 + 24); ++kk )
    {
      v117 = *(_DWORD *)(v153 + 20) + 80 * kk;
      if ( !rf_packed_state_word_equal((_DWORD *)(v117 + 32), &dword_1E014FC) )
        rf_renderer_apply_packed_render_state(*(_DWORD *)(v117 + 32));
      if ( (v155 == *(_DWORD *)(v117 + 64)
         || rf_renderer_bind_texture_handle(0, *(_DWORD *)(v117 + 64), 0, (float *)v185, (float *)v174, 1))
        && rf_renderer_bind_texture_handle(1, *(_DWORD *)(v117 + 68), 0, (float *)v185, (float *)v174, 1) )
      {
        v155 = *(_DWORD *)(v117 + 64);
        v112 = *(float **)(v117 + 44);
        if ( *(_BYTE *)(v117 + 16) )
        {
          v108 = unk_1E4198C - *(float *)(v117 + 20);
          *(float *)(v117 + 20) = unk_1E4198C;
          v107 = v108 * *(float *)(v117 + 8);
          if ( *(float *)v117 > 1.0 )
          {
            v8 = rf_floor_float(*(float *)v117);
            v107 = v107 - v8;
          }
          v109 = v108 * *(float *)(v117 + 12);
          if ( *(float *)(v117 + 4) > 1.0 )
          {
            v9 = rf_floor_float(*(float *)(v117 + 4));
            v109 = v109 - v9;
          }
          *(float *)v117 = *(float *)v117 + v107;
          *(float *)(v117 + 4) = *(float *)(v117 + 4) + v109;
          mm = 0;
          while ( mm < *(__int16 *)(v117 + 72) )
          {
            *v112 = *v112 + v107;
            v112[1] = v112[1] + v109;
            ++mm;
            v112 += 4;
          }
          v112 = *(float **)(v117 + 44);
        }
        v111 = *(__int16 *)(v117 + 72);
        v123 = 3 * *(__int16 *)(v117 + 76);
        v115 = *(__int16 *)(v117 + 72);
        if ( v201 )
        {
          v111 += 768;
          v123 += 768;
        }
        if ( v111 + v159 >= 6000 || v123 + v162 >= 10000 )
        {
          v159 = 0;
          v162 = 0;
        }
        if ( v159 )
          v35 = unk_1DAEE08;
        else
          v35 = unk_1DAEE04;
        v124 = v35;
        (*(void (__stdcall **)(_DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
          dword_1DAEDB0,
          40 * v159,
          40 * v111,
          &v156,
          v35);
        (*(void (__stdcall **)(_DWORD *, int, int, _WORD **, int))(*dword_1DAEDB4 + 44))(
          dword_1DAEDB4,
          2 * v162,
          2 * v123,
          &v160,
          v124);
        if ( *(_BYTE *)(v117 + 24) )
        {
          for ( mm = 0; mm < *(__int16 *)(v117 + 74); ++mm )
            *(_BYTE *)(*(_DWORD *)(v117 + 52) + mm) = *(_BYTE *)(*(__int16 *)(*(_DWORD *)(v117 + 60) + 2 * mm)
                                                               + *(_DWORD *)(v153 + 16));
        }
        memset(v194, 255, *(__int16 *)(v117 + 72));
        for ( mm = 0; mm < *(__int16 *)(v117 + 74); ++mm )
        {
          if ( !*(_BYTE *)(*(_DWORD *)(v117 + 52) + mm) )
          {
            v106 = (__int16 *)(*(_DWORD *)(v117 + 48) + 28 * mm);
            for ( nn = 0; nn < *v106; ++nn )
            {
              v104 = *(__int16 *)(*((_DWORD *)v106 + 1) + 2 * nn);
              v194[v104] = 0;
            }
          }
        }
        rf_vector3_default_construct_noop(v116);
        rf_vector3_default_construct_noop(v114);
        v122 = v156;
        v120 = unk_1C97950;
        v113 = v194;
        if ( v201 )
        {
          mm = 0;
          while ( mm < *(__int16 *)(v117 + 72) )
          {
            if ( !*v113 )
            {
              v103 = &v203[5 * *(__int16 *)(*(_DWORD *)(v117 + 40) + 2 * mm)];
              *v120 = *((_BYTE *)v103 + 17);
              if ( !*v120 )
              {
                *(float *)v122 = *(float *)v103;
                *(float *)(v122 + 4) = *((float *)v103 + 1);
                *(float *)(v122 + 8) = *((float *)v103 + 2);
                *(float *)(v122 + 12) = *((float *)v103 + 3);
                *(_BYTE *)(v122 + 23) = *((_BYTE *)v103 + 16);
                *(float *)(v122 + 24) = *v112;
                *(float *)(v122 + 28) = v112[1];
                *(float *)(v122 + 32) = v112[2];
                *(float *)(v122 + 36) = v112[3];
                *(_DWORD *)(v122 + 16) = *(_DWORD *)(v117 + 36);
              }
            }
            ++mm;
            v122 += 40;
            v112 += 4;
            ++v120;
            ++v113;
          }
        }
        else
        {
          mm = 0;
          while ( mm < *(__int16 *)(v117 + 72) )
          {
            if ( !*v113 )
            {
              v102 = (float *)&v203[5 * *(__int16 *)(*(_DWORD *)(v117 + 40) + 2 * mm)];
              *(float *)v122 = *v102;
              *(float *)(v122 + 4) = v102[1];
              *(float *)(v122 + 8) = v102[2];
              *(float *)(v122 + 12) = v102[3];
              *(_BYTE *)(v122 + 23) = *((_BYTE *)v102 + 16);
              *(float *)(v122 + 24) = *v112;
              *(float *)(v122 + 28) = v112[1];
              *(float *)(v122 + 32) = v112[2];
              *(float *)(v122 + 36) = v112[3];
              *(_DWORD *)(v122 + 16) = *(_DWORD *)(v117 + 36);
            }
            ++mm;
            v122 += 40;
            v112 += 4;
            ++v113;
          }
        }
        v119 = v160;
        v121 = (unsigned int)&v160[v123];
        v110 = *(_BYTE **)(v117 + 52);
        mm = 0;
LABEL_163:
        if ( mm >= *(__int16 *)(v117 + 74) )
        {
          (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
          (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
          v118 = v119 - v160;
          if ( v118 )
          {
            (*(void (__thiscall **)(int, int, int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              4,
              v159,
              v115,
              v162,
              v118 / 3);
            v159 += v115;
            v162 += v118;
          }
          else
          {
            v159 += v115;
          }
          continue;
        }
        if ( !*v110 )
        {
          v101 = (__int16 *)(*(_DWORD *)(v117 + 48) + 28 * mm);
          if ( !v201 )
            goto LABEL_187;
          v200 = -1;
          v199 = 0;
          for ( i1 = 0; i1 < *v101; v199 |= unk_1C97950[*(__int16 *)(*((_DWORD *)v101 + 1) + 2 * i1++)] )
            v200 &= unk_1C97950[*(__int16 *)(*((_DWORD *)v101 + 1) + 2 * i1)];
          if ( !v200 )
          {
            if ( v199 )
            {
              rf_clip_vertex48_pool_reset();
              v96 = *v101;
              destination = (float *)v182;
              i2 = 0;
              while ( i2 < v96 )
              {
                v184[i2] = destination;
                v95 = *(__int16 *)(*((_DWORD *)v101 + 1) + 2 * i2);
                v94 = *(__int16 *)(*(_DWORD *)(v117 + 40) + 2 * v95);
                rf_vector_copy(destination, copy_result, &flt_1C998E0[3 * v94]);
                *((_BYTE *)destination + 24) = unk_1C97950[v95];
                *((_BYTE *)destination + 25) = 0;
                destination[7] = *(float *)(*(_DWORD *)(v117 + 44) + 16 * v95);
                destination[8] = *(float *)(*(_DWORD *)(v117 + 44) + 16 * v95 + 4);
                destination[9] = *(float *)(*(_DWORD *)(v117 + 44) + 16 * v95 + 8);
                destination[10] = *(float *)(*(_DWORD *)(v117 + 44) + 16 * v95 + 12);
                ++i2;
                destination += 12;
              }
              v99 = rf_clip_polygon_outcode_planes_48(v184, v173, &v96, &v199, 3);
              if ( v96 >= 3 && !v200 && v96 + v115 < v111 && (unsigned int)&v119[3 * v96 - 6] < v121 )
              {
                for ( i2 = 0; i2 < v96; ++i2 )
                {
                  v93 = v156 + 40 * v115;
                  v183[i2] = v115++;
                  destination = (float *)v99[i2];
                  rf_renderer_project_clip_vertex_cached((int)destination);
                  *(float *)v93 = destination[3];
                  *(float *)(v93 + 4) = destination[4];
                  destination[5] = 1.0 / destination[2];
                  *(float *)(v93 + 12) = destination[5] * flt_6649F8;
                  v10 = rf_renderer_scale_reciprocal_depth(destination[5]);
                  *(float *)(v93 + 8) = v10;
                  *(float *)(v93 + 24) = destination[7];
                  *(float *)(v93 + 28) = destination[8];
                  *(float *)(v93 + 32) = destination[9];
                  *(float *)(v93 + 36) = destination[10];
                  v11 = rf_world_depth_fog_byte(destination[2], v193);
                  *(_BYTE *)(v93 + 23) = v11;
                  *(_DWORD *)(v93 + 16) = *(_DWORD *)(v117 + 36);
                }
                for ( i2 = 0; i2 < v96 - 2; ++i2 )
                {
                  *v119 = v159 + v183[0];
                  v119[1] = v159 + v183[i2 + 1];
                  v119[2] = v159 + v183[i2 + 2];
                  v119 += 3;
                }
              }
              goto LABEL_162;
            }
            if ( (unsigned int)(v119 + 3) < v121 )
            {
LABEL_187:
              for ( i3 = 0; i3 < *v101 - 2; ++i3 )
              {
                *v119 = v159 + **((_WORD **)v101 + 1);
                v119[1] = v159 + *(_WORD *)(*((_DWORD *)v101 + 1) + 2 * i3 + 2);
                v119[2] = v159 + *(_WORD *)(*((_DWORD *)v101 + 1) + 2 * i3 + 4);
                v119 += 3;
              }
            }
          }
        }
LABEL_162:
        ++mm;
        ++v110;
        goto LABEL_163;
      }
    }
    dword_18CCFBC = v159;
    unk_18CCFC0 = v162;
    v157 = v206;
    if ( byte_663F04 && v171 )
    {
      unk_1E014E6 = 0;
      unk_1E014E0 = rf_renderer_scale_camera_depth_bias(0.025);
      rf_render_color_set_rgba8(255, 255, 255, 255);
      for ( i4 = 0; i4 < v171; ++i4 )
      {
        if ( (*(_DWORD *)(v157 + 80) & 8) == 0 && (*(void **)(v157 + 64) == v154 || *(void **)(v157 + 68) == v154) )
        {
          rf_renderer_set_pending_texture_handles(*(_DWORD *)(v157 + 60), -1);
          for ( i5 = *(int **)(v157 + 212); i5; i5 = v34 )
          {
            if ( *(__int16 *)(i5[328] + 80) >= 0
              && !*(_BYTE *)(*(_DWORD *)(v153 + 16) + *(__int16 *)(i5[328] + 80))
              && *(void **)(i5[328] + 68) == v154 )
            {
              rf_vector_construct_no_unwind(v88, 0x30u, 25, rf_vector_prefix_construct_noop);
              for ( i6 = 0; i6 < i5[52]; ++i6 )
              {
                rf_renderer_transform_world_point_to_clip_vertex((int)&v88[48 * i6], (float *)&i5[11 * i6 + 57]);
                v89[i6] = (int)&v88[48 * i6];
                *(float *)&v88[48 * i6 + 28] = *(float *)&i5[11 * i6 + 53];
                *(float *)&v88[48 * i6 + 32] = *(float *)&i5[11 * i6 + 54];
                v88[48 * i6 + 47] = *(_BYTE *)(v157 + 76);
              }
              v12 = rf_render_state_pack(&v45, 2, 0, 2, 3, 1, 0);
              rf_d3d8_submit_immediate_polygon(i5[52], (int)v89, 9u, *v12, 0, 0.0);
            }
            if ( i5[330] == *(_DWORD *)(v157 + 212) )
              v34 = nullptr;
            else
              v34 = (int *)i5[330];
          }
        }
        v157 = *(_DWORD *)(v157 + 224);
      }
      if ( unk_1E014E5 )
        rf_renderer_flush_immediate_buffers();
      unk_1E014E6 = 1;
      unk_1E014E0 = 0.0;
    }
    if ( rf_light_active_world_count )
    {
      if ( rf_d3d8_multitexture_available && rf_d3d8_ground_detail_dual_stage_compatible )
      {
        rf_renderer_apply_packed_render_state(unk_187CC6C);
        rf_renderer_bind_texture_handle(0, dword_664A04, 0, (float *)v185, (float *)v174, 1);
        rf_renderer_bind_texture_handle(1, dword_664A0C, 0, (float *)v185, (float *)v174, 1);
      }
      else
      {
        rf_renderer_apply_packed_render_state(SLODWORD(rf_particle_glow_billboard_render_state));
        rf_renderer_bind_texture_handle(0, dword_664A04, 0, (float *)v185, (float *)v174, 1);
      }
      if ( (int)rf_light_active_world_count <= 32 )
        v33 = rf_light_active_world_count;
      else
        v33 = 32;
      v86 = v33;
      memset(v191, 0, 4 * v33);
      memset(v178, 0, 4 * v86);
      for ( j = 0; j < *(unsigned __int16 *)(v153 + 24); ++j )
      {
        v85 = *(_DWORD *)(v153 + 20) + 80 * j;
        if ( !*(_BYTE *)(v85 + 24) )
        {
          v170 = *(_BYTE **)(v85 + 52);
          *(_DWORD *)(v85 + 28) = 0;
          v179 = 0;
          while ( v179 < *(__int16 *)(v85 + 74) )
          {
            if ( !*v170 )
            {
              v84 = (__int16 *)(*(_DWORD *)(v85 + 48) + 28 * v179);
              if ( *((_DWORD *)v84 + 6) )
              {
                for ( ii = 0; ii < v86; ++ii )
                {
                  v83 = 1 << ii;
                  if ( ((1 << ii) & *((_DWORD *)v84 + 6)) != 0 )
                  {
                    v191[ii] += *v84;
                    v178[ii] += 3 * (*v84 - 2);
                    ++*(_DWORD *)(v85 + 28);
                  }
                }
              }
            }
            ++v179;
            ++v170;
          }
        }
      }
      ii = 0;
LABEL_244:
      if ( ii >= v86 )
        continue;
      if ( v191[ii] )
      {
        v74 = 1 << ii;
        v75 = (float *)rf_light_active_world_records[ii];
        v80 = v191[ii];
        v73 = v178[ii];
        if ( v201 )
        {
          v80 += 768;
          v73 += 768;
        }
        if ( v80 >= 6000 )
          v32 = 6000;
        else
          v32 = v80;
        v80 = v32;
        if ( v73 >= 10000 )
          v31 = 10000;
        else
          v31 = v73;
        v73 = v31;
        if ( v80 + dword_18CCFBC >= 6000 || v73 + unk_18CCFC0 >= 10000 )
        {
          dword_18CCFBC = 0;
          unk_18CCFC0 = 0;
        }
        if ( dword_18CCFBC )
          v30 = unk_1DAEE08;
        else
          v30 = unk_1DAEE04;
        v81 = v30;
        (*(void (__stdcall **)(_DWORD *, int, int, int *, int))(*dword_1DAEDB0 + 44))(
          dword_1DAEDB0,
          40 * dword_18CCFBC,
          40 * v80,
          &v78,
          v30);
        (*(void (__stdcall **)(_DWORD *, int, int, _WORD **, int))(*dword_1DAEDB4 + 44))(
          dword_1DAEDB4,
          2 * unk_18CCFC0,
          2 * v73,
          &v76,
          v81);
        v77 = dword_18CCFBC;
        v79 = 0;
        v82 = 0;
        j = 0;
        while ( 2 )
        {
          if ( j < *(unsigned __int16 *)(v153 + 24) )
          {
            v71 = *(_DWORD *)(v153 + 20) + 80 * j;
            if ( *(_BYTE *)(v71 + 24) || !*(_DWORD *)(v71 + 28) )
            {
LABEL_261:
              ++j;
              continue;
            }
            v170 = *(_BYTE **)(v71 + 52);
            v72 = *(float **)(v71 + 48);
            v179 = 0;
            while ( 2 )
            {
              if ( v179 >= *(__int16 *)(v71 + 74) )
                goto LABEL_261;
              if ( !*v170 && (v74 & (_DWORD)v72[6]) != 0 )
              {
                if ( v79 + *(__int16 *)v72 > v80 || v82 + 3 * (*(__int16 *)v72 - 2) > v73 )
                  goto LABEL_261;
                v62 = rf_plane_point_signed_distance(v72 + 2, v75 + 3);
                if ( v75[15] > (double)v62 && v62 >= -v75[15] )
                {
                  value = -v62;
                  v13 = rf_vector_multiply_scalar(v72 + 2, scaled_result, value);
                  rf_vector_add(v75 + 3, rhs, v13);
                  v29 = fabs(v62);
                  v62 = v29;
                  v28 = v29 * 1.570796370506287 / v75[15];
                  v14 = rf_cos_float(v28);
                  v63 = v14 * v75[15];
                  v65 = 255.0 - v62 * 255.0 / v75[15];
                  if ( v65 <= 0.0 )
                    v27 = 0.0;
                  else
                    v27 = v65;
                  v65 = v27;
                  v67 = &v64;
                  v26 = v27 * v75[18];
                  v15 = rf_float_to_byte_add_12582912_bits(v26);
                  *(_BYTE *)v67 = v15;
                  v25 = v65 * v75[17];
                  v16 = rf_float_to_byte_add_12582912_bits(v25);
                  *((_BYTE *)v67 + 1) = v16;
                  v24 = v65 * v75[16];
                  v17 = rf_float_to_byte_add_12582912_bits(v24);
                  *((_BYTE *)v67 + 2) = v17;
                  *((_BYTE *)v67 + 3) = -1;
                  rf_orientation_matrix_from_direction(v167, v72 + 2);
                  if ( v201 )
                  {
                    v200 = -1;
                    v199 = 0;
                    for ( i7 = 0; i7 < *(__int16 *)v72; ++i7 )
                    {
                      v59 = &v203[5
                                * *(__int16 *)(*(_DWORD *)(v71 + 40) + 2 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * i7))];
                      v200 &= *((_BYTE *)v59 + 17);
                      v199 |= *((_BYTE *)v59 + 17);
                    }
                    if ( v200 )
                      goto LABEL_267;
                    if ( v199 )
                    {
                      rf_clip_vertex48_pool_reset();
                      v53 = *(__int16 *)v72;
                      v56 = (float *)v182;
                      v54 = 0;
                      while ( v54 < *(__int16 *)v72 )
                      {
                        v184[v54] = v56;
                        v50 = *(__int16 *)(*(_DWORD *)(v71 + 40) + 2 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v54));
                        rf_vector_subtract((const float *)(*(_DWORD *)v153 + 12 * v50), out_vector, rhs);
                        rf_vector_copy(v56, v43, &flt_1C998E0[3 * v50]);
                        *((_BYTE *)v56 + 24) = BYTE1(v203[5 * v50 + 4]);
                        *((_BYTE *)v56 + 25) = 0;
                        v18 = rf_vector_dot(out_vector, v167);
                        v56[7] = v18 / v63 + 0.5;
                        v19 = rf_vector_dot(out_vector, v168);
                        v56[8] = v19 / v63 + 0.5;
                        v56[9] = *(float *)(*(_DWORD *)(v71 + 44) + 16 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v54))
                               * 4.0;
                        v56[10] = *(float *)(*(_DWORD *)(v71 + 44)
                                           + 16 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v54++)
                                           + 4)
                                * 4.0;
                        v56 += 12;
                      }
                      v58 = rf_clip_polygon_outcode_planes_48(v184, v173, &v53, &v199, 3);
                      if ( v53 >= 3 && !v200 )
                      {
                        if ( v53 + v79 > v80 || v82 + 3 * (v53 - 2) > v73 )
                          goto LABEL_261;
                        v54 = 0;
                        while ( v54 < v53 )
                        {
                          v56 = (float *)v58[v54];
                          rf_renderer_project_clip_vertex_cached((int)v56);
                          *(float *)v78 = v56[3];
                          *(float *)(v78 + 4) = v56[4];
                          v56[5] = 1.0 / v56[2];
                          *(float *)(v78 + 12) = v56[5] * flt_6649F8;
                          v20 = rf_renderer_scale_reciprocal_depth(v56[5]);
                          *(float *)(v78 + 8) = v20;
                          *(float *)(v78 + 24) = v56[7];
                          *(float *)(v78 + 28) = v56[8];
                          *(float *)(v78 + 32) = v56[9];
                          *(float *)(v78 + 36) = v56[10];
                          *(_BYTE *)(v78 + 23) = -1;
                          *(_DWORD *)(v78 + 16) = v64;
                          ++v54;
                          v78 += 40;
                          ++v79;
                        }
                        v52 = v77;
                        v57 = v77 + 1;
                        v54 = 0;
                        while ( v54 < v53 - 2 )
                        {
                          v55 = v57 + 1;
                          *v76 = v52;
                          v76[1] = v57;
                          v76[2] = v55;
                          v57 = v55;
                          ++v54;
                          v76 += 3;
                          v82 += 3;
                        }
                        v77 += v53;
                      }
                      goto LABEL_267;
                    }
                  }
                  v68 = 0;
                  while ( v68 < *(__int16 *)v72 )
                  {
                    v47 = *(__int16 *)(*(_DWORD *)(v71 + 40) + 2 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v68));
                    rf_vector_subtract((const float *)(*(_DWORD *)v153 + 12 * v47), v48, rhs);
                    v49 = (float *)&v203[5 * v47];
                    *(float *)v78 = *v49;
                    *(float *)(v78 + 4) = v49[1];
                    *(float *)(v78 + 8) = v49[2];
                    *(float *)(v78 + 12) = v49[3];
                    *(_BYTE *)(v78 + 23) = -1;
                    v21 = rf_vector_dot(v48, v167);
                    *(float *)(v78 + 24) = v21 / v63 + 0.5;
                    v22 = rf_vector_dot(v48, v168);
                    *(float *)(v78 + 28) = v22 / v63 + 0.5;
                    *(float *)(v78 + 32) = *(float *)(*(_DWORD *)(v71 + 44)
                                                    + 16 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v68))
                                         * 4.0;
                    *(float *)(v78 + 36) = *(float *)(*(_DWORD *)(v71 + 44)
                                                    + 16 * *(__int16 *)(*((_DWORD *)v72 + 1) + 2 * v68)
                                                    + 4)
                                         * 4.0;
                    *(_DWORD *)(v78 + 16) = v64;
                    ++v68;
                    v78 += 40;
                    ++v79;
                  }
                  v61 = v77;
                  v70 = v77 + 1;
                  v68 = 0;
                  while ( v68 < *(__int16 *)v72 - 2 )
                  {
                    v69 = v70 + 1;
                    *v76 = v61;
                    v76[1] = v70;
                    v76[2] = v69;
                    v70 = v69;
                    ++v68;
                    v76 += 3;
                    v82 += 3;
                  }
                  v77 += *(__int16 *)v72;
                }
              }
LABEL_267:
              ++v179;
              ++v170;
              v72 += 7;
              continue;
            }
          }
          break;
        }
        (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1DAEDB0 + 48))(dword_1DAEDB0, dword_1DAEDB0);
        (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 48))(dword_1DAEDB4);
        (*(void (__thiscall **)(int, int, int, _DWORD, int, _DWORD, int))(*(_DWORD *)dword_1DAEDC4 + 284))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          4,
          dword_18CCFBC,
          v79,
          unk_18CCFC0,
          v82 / 3);
        dword_18CCFBC += v79;
        unk_18CCFC0 += v82;
      }
      ++ii;
      goto LABEL_244;
    }
  }
  unk_1E014E6 = 0;
  rf_light_clear_active_world_list();
}

