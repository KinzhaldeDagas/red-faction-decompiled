// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5F60 rf_scene_model_instance_update_geometry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall152-byte model state ECX and one stack float timeline15, RET4; no EDX input. Sole caller5B5F40/scene update uses effects, not EAX; declared void because old pointer return was path-dependent register residue. Definition pointer0; output center4,aux dimensions16/20,attachment handle24,packed flags28,attachment translation32/matrix44,render translation80/matrix92,owned vertex128/UV132,active BYTE144. Computes float-rounded f=(timeline15/15.0-definition.start168)*FPS14 from WORD136>>2. For FINITE values accepts CLOSED interval0<=f<=signed frameCount164. Raw lower gate TEST AH,5/JNP and upper TEST AH,41h/JNZ also accept unordered x87 comparison status; no NaN/finite validation before floor/int
// conversion. Outside interval sets active144=0 only and returns, retaining prior geometry/UV/dimensions. Inside: current=floor(f),next=current+1,weight=float(f-floor(f)); definition flags276 mask2 forces weight0 but leaves indices, visibility choice and keyed time unchanged. Interpolation branch only when next<frameCount; all final-frame interval values including f==frameCount select endpoint branch using last frameCount-1 (zero frame count can therefore index-1). GEOMETRY MODES, priority: flag4 vertex animation, else WORD136 bit1 keyed transforms, else per-frame poses. Vertex animation interpolates current/next frame40 origins+8 and individually unpacks signed16 triples using each frame pointer+4,origin+8,scale+20, then blends decoded positions. Dimensions16/20 linearly interpolate frame fields32/36 UNCONDITIONALLY in this mode, even when reader did not populate fade fields. Endpoint
// copies last origin,unpacks last vertices and copies last32/36. Keyed mode uses frame0 packed geometry and TWO transforms in strict order: component-scale by definition base scale256,rotate by quaternion240 matrix,add base translation228; then component-scale by sampled scale,rotate by sampled quaternion matrix,add sampled translation. Applies same sequence to frame0 origin for center. Key samplers use track20 pointer224: WORD0 selects vector0,WORD2 quaternion(final sampler argument0),WORD4 vector2. Absent channel falls back to old pose220 translation0/quaternion12/scale28, NOT zero/identity nor only base transform. Modern keyed readers may leave old pose220 NULL; no fallback-pointer check here. Interior key time is trunc((timeline15/15)*30*160)-trunc(start168*30*160), TWO independent truncations; not trunc of relative seconds. Endpoint samples
// trunc((frameCount/FPS14+start)*30*160)-trunc(start*30*160), using count/FPS rather than(count-1)/FPS and ignoring actual input within final interval; no FPS-zero guard. Static unkeyed mode transforms frame0 origin/each decoded vertex independently through current and next pose40(scale28,quaternion12,translation0), then linearly blends TRANSFORMED POSITIONS; it does NOT slerp/interpolate quaternions or matrices. Endpoint uses last pose only. For static/keyed modes, if definition flags&801h and frame0 field32 compares ordered nonnegative, updates dimensions16/20 with abs(baseFade32*scaleX),abs(baseFade36*scaleZ); keyed scale factors are baseScale*sampleScale, static interior uses interpolated pose scale, endpoint last scale. Fade guard C0-bit test rejects unordered, unlike main time gate. Otherwise dimensions retain prior values. VISIBILITY: interpolation branch active144 comes from NEXT
// frame DWORD0 bit31 even when step flag made weight0; endpoint uses LAST frame bit31. This visibility choice does not stop remaining UV/attachment work. UV flag100h blends current/next six floats per face into UV132; endpoint copies last slice. Without flag100h copies first UV slice every call. No UV wrap/clamp/material evaluation. FINAL ATTACHMENT: state flags28 bit30 has priority, rotates every output vertex and center by matrix44 then adds translation32. Else bit29 queries model-node transform with handle24 and low29-bit index, ignores query result, builds affine and transforms vertices/center. Bit31 suppresses drawing elsewhere but does NOT suppress this update. No pointer/count/allocation/finite checks, normal calculation, bounds/radius recompute or buffer resizing here. Nonkeyed pose mode blends transformed points; keyed quaternion sampling/interpolation is delegated to the existing
// sampler. Float-pointer results of vector helpers and reused argument-stack slots account for COERCE_FLOAT temporaries in pseudocode; these are bit reinterpretation artifacts, not numeric pointer-to-float conversion.
void __thiscall rf_scene_model_instance_update_geometry(char *self, float timeline15)
{
  double v2; // st7
  float *v3; // eax
  int v4; // ecx
  double v5; // st7
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
  float v27[2]; // [esp-1Ch] [ebp-560h] BYREF
  float v28; // [esp-14h] [ebp-558h] BYREF
  float v29; // [esp-10h] [ebp-554h] BYREF
  float v30; // [esp-Ch] [ebp-550h] BYREF
  float v31; // [esp-8h] [ebp-54Ch] BYREF
  float *v32; // [esp-4h] [ebp-548h]
  float scale_x; // [esp+0h] [ebp-544h] BYREF
  float *v34; // [esp+4h] [ebp-540h]
  float value; // [esp+8h] [ebp-53Ch]
  float v36; // [esp+10h] [ebp-534h]
  float v37; // [esp+14h] [ebp-530h]
  float v38; // [esp+18h] [ebp-52Ch]
  float v39; // [esp+1Ch] [ebp-528h]
  float v40; // [esp+20h] [ebp-524h]
  float v41; // [esp+24h] [ebp-520h]
  float v42; // [esp+28h] [ebp-51Ch]
  float v43; // [esp+2Ch] [ebp-518h]
  float v44; // [esp+30h] [ebp-514h]
  float v45; // [esp+34h] [ebp-510h]
  float v46; // [esp+38h] [ebp-50Ch]
  float v47; // [esp+3Ch] [ebp-508h]
  float v48; // [esp+40h] [ebp-504h]
  int v49; // [esp+44h] [ebp-500h]
  int v50; // [esp+48h] [ebp-4FCh]
  int v51; // [esp+4Ch] [ebp-4F8h]
  float *v52; // [esp+50h] [ebp-4F4h]
  float v53[3]; // [esp+54h] [ebp-4F0h] BYREF
  float v54[3]; // [esp+60h] [ebp-4E4h] BYREF
  float v55[3]; // [esp+6Ch] [ebp-4D8h] BYREF
  float v56[3]; // [esp+78h] [ebp-4CCh] BYREF
  float v57[3]; // [esp+84h] [ebp-4C0h] BYREF
  float v58[3]; // [esp+90h] [ebp-4B4h] BYREF
  float v59[3]; // [esp+9Ch] [ebp-4A8h] BYREF
  float v60[3]; // [esp+A8h] [ebp-49Ch] BYREF
  float v61[3]; // [esp+B4h] [ebp-490h] BYREF
  float v62[3]; // [esp+C0h] [ebp-484h] BYREF
  float v63[5]; // [esp+CCh] [ebp-478h] BYREF
  float v64[3]; // [esp+E0h] [ebp-464h] BYREF
  float v65[3]; // [esp+ECh] [ebp-458h] BYREF
  float v66[3]; // [esp+F8h] [ebp-44Ch] BYREF
  float v67[3]; // [esp+104h] [ebp-440h] BYREF
  float v68[3]; // [esp+110h] [ebp-434h] BYREF
  float v69[3]; // [esp+11Ch] [ebp-428h] BYREF
  float v70[3]; // [esp+128h] [ebp-41Ch] BYREF
  float v71[5]; // [esp+134h] [ebp-410h] BYREF
  float v72[3]; // [esp+148h] [ebp-3FCh] BYREF
  float v73[3]; // [esp+154h] [ebp-3F0h] BYREF
  float v74[3]; // [esp+160h] [ebp-3E4h] BYREF
  float v75[3]; // [esp+16Ch] [ebp-3D8h] BYREF
  float v76[3]; // [esp+178h] [ebp-3CCh] BYREF
  float v77[3]; // [esp+184h] [ebp-3C0h] BYREF
  float v78[3]; // [esp+190h] [ebp-3B4h] BYREF
  float v79[3]; // [esp+19Ch] [ebp-3A8h] BYREF
  float v80[3]; // [esp+1A8h] [ebp-39Ch] BYREF
  float v81[3]; // [esp+1B4h] [ebp-390h] BYREF
  float origin_x[5]; // [esp+1C0h] [ebp-384h] BYREF
  float v83[3]; // [esp+1D4h] [ebp-370h] BYREF
  float v84[5]; // [esp+1E0h] [ebp-364h] BYREF
  float v85[3]; // [esp+1F4h] [ebp-350h] BYREF
  float sum_result[3]; // [esp+200h] [ebp-344h] BYREF
  float scaled_result[3]; // [esp+20Ch] [ebp-338h] BYREF
  float v88[3]; // [esp+218h] [ebp-32Ch] BYREF
  float v89[3]; // [esp+224h] [ebp-320h] BYREF
  float v90[5]; // [esp+230h] [ebp-314h] BYREF
  float v91[3]; // [esp+244h] [ebp-300h] BYREF
  float v92[3]; // [esp+250h] [ebp-2F4h] BYREF
  float v93[3]; // [esp+25Ch] [ebp-2E8h] BYREF
  float v94[3]; // [esp+268h] [ebp-2DCh] BYREF
  float v95[5]; // [esp+274h] [ebp-2D0h] BYREF
  float v96[3]; // [esp+288h] [ebp-2BCh] BYREF
  float v97[3]; // [esp+294h] [ebp-2B0h] BYREF
  float v98[3]; // [esp+2A0h] [ebp-2A4h] BYREF
  float v99[3]; // [esp+2ACh] [ebp-298h] BYREF
  float v100[3]; // [esp+2B8h] [ebp-28Ch] BYREF
  float v101[3]; // [esp+2C4h] [ebp-280h] BYREF
  float v102[3]; // [esp+2D0h] [ebp-274h] BYREF
  float scale_y[3]; // [esp+2DCh] [ebp-268h] BYREF
  float out_vertex[5]; // [esp+2E8h] [ebp-25Ch] BYREF
  float copy_result[3]; // [esp+2FCh] [ebp-248h] BYREF
  float v106[12]; // [esp+308h] [ebp-23Ch] BYREF
  float v107[9]; // [esp+338h] [ebp-20Ch] BYREF
  float v108[3]; // [esp+35Ch] [ebp-1E8h] BYREF
  float v109; // [esp+368h] [ebp-1DCh]
  float v110; // [esp+36Ch] [ebp-1D8h]
  float v111; // [esp+370h] [ebp-1D4h]
  float v112; // [esp+374h] [ebp-1D0h]
  float v113[3]; // [esp+378h] [ebp-1CCh] BYREF
  float v114[9]; // [esp+384h] [ebp-1C0h] BYREF
  float v115; // [esp+3A8h] [ebp-19Ch] BYREF
  float v116; // [esp+3ACh] [ebp-198h]
  float v117; // [esp+3B0h] [ebp-194h]
  float source; // [esp+3B4h] [ebp-190h] BYREF
  float v119; // [esp+3B8h] [ebp-18Ch]
  float v120; // [esp+3BCh] [ebp-188h]
  float v121[3]; // [esp+3C0h] [ebp-184h] BYREF
  float v122[9]; // [esp+3CCh] [ebp-178h] BYREF
  float vector[3]; // [esp+3F0h] [ebp-154h] BYREF
  float v124[4]; // [esp+3FCh] [ebp-148h] BYREF
  float v125; // [esp+40Ch] [ebp-138h] BYREF
  float v126; // [esp+410h] [ebp-134h]
  float v127; // [esp+414h] [ebp-130h]
  float v128[3]; // [esp+418h] [ebp-12Ch] BYREF
  float v129[9]; // [esp+424h] [ebp-120h] BYREF
  int v130; // [esp+448h] [ebp-FCh]
  float v131[9]; // [esp+44Ch] [ebp-F8h] BYREF
  int v132; // [esp+470h] [ebp-D4h]
  float v133[3]; // [esp+474h] [ebp-D0h] BYREF
  float v134; // [esp+480h] [ebp-C4h] BYREF
  float v135; // [esp+484h] [ebp-C0h]
  float v136; // [esp+488h] [ebp-BCh]
  float v137[4]; // [esp+48Ch] [ebp-B8h] BYREF
  float v138[4]; // [esp+49Ch] [ebp-A8h] BYREF
  float v139; // [esp+4ACh] [ebp-98h] BYREF
  float v140; // [esp+4B0h] [ebp-94h]
  float v141; // [esp+4B4h] [ebp-90h]
  float v142[9]; // [esp+4B8h] [ebp-8Ch] BYREF
  int v143; // [esp+4DCh] [ebp-68h]
  int v144; // [esp+4E0h] [ebp-64h]
  float v145[3]; // [esp+4E4h] [ebp-60h] BYREF
  float scale_z[3]; // [esp+4F0h] [ebp-54h] BYREF
  float v147[9]; // [esp+4FCh] [ebp-48h] BYREF
  float destination; // [esp+520h] [ebp-24h] BYREF
  float v149; // [esp+524h] [ebp-20h]
  float v150; // [esp+528h] [ebp-1Ch]
  int j; // [esp+52Ch] [ebp-18h]
  float v152; // [esp+530h] [ebp-14h]
  int v153; // [esp+534h] [ebp-10h]
  int i; // [esp+538h] [ebp-Ch]
  int v155; // [esp+53Ch] [ebp-8h]
  float v156; // [esp+540h] [ebp-4h]

  v52 = (float *)self;
  v2 = timeline15 / 15.0 - *(float *)(*(_DWORD *)self + 168);
  v51 = (*(_WORD *)(*(_DWORD *)self + 136) >> 2) & 0x3FFF;
  v152 = v2 * (double)v51;
  if ( v152 >= 0.0 && v152 <= (double)*(int *)(*(_DWORD *)v52 + 164) )
  {
    v155 = (int)rf_floor_float(v152);
    v153 = v155 + 1;
    v50 = (int)rf_floor_float(v152);
    v156 = v152 - (double)v50;
    if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 2) != 0 )
      v156 = 0.0;
    if ( v153 < *(_DWORD *)(*(_DWORD *)v52 + 164) )
    {
      if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 4) != 0 )
      {
        value = COERCE_FLOAT(
                  rf_vector_multiply_scalar(
                    (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 8),
                    scaled_result,
                    v156));
        v34 = sum_result;
        v44 = 1.0 - v156;
        v10 = rf_vector_multiply_scalar((const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 8), v88, v44);
        v11 = rf_vector_add(v10, sum_result, (const float *)LODWORD(value));
        rf_vector_copy(v52 + 1, v85, v11);
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
        {
          value = v156;
          v34 = v81;
          rf_vector3_copy_return_destination(&v31, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 20));
          rf_vector3_copy_return_destination(&v28, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 8));
          v12 = rf_scene_unpack_signed_vertex(
                  origin_x,
                  (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 4) + 6 * i),
                  v28,
                  v29,
                  v30,
                  v31,
                  *(float *)&v32,
                  scale_x);
          value = COERCE_FLOAT(rf_vector_multiply_scalar(v12, v34, value));
          v34 = v80;
          v43 = 1.0 - v156;
          scale_x = v43;
          v32 = v83;
          rf_vector3_copy_return_destination(&v29, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 20));
          rf_vector3_copy_return_destination(v27, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 8));
          v13 = rf_scene_unpack_signed_vertex(
                  v84,
                  (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 4) + 6 * i),
                  v27[0],
                  v27[1],
                  v28,
                  v29,
                  v30,
                  v31);
          v14 = rf_vector_multiply_scalar(v13, v32, scale_x);
          v15 = rf_vector_add(v14, v34, (const float *)LODWORD(value));
          rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v79, v15);
        }
        v52[4] = (1.0 - v156) * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 32)
               + *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 32) * v156;
        v52[5] = (1.0 - v156) * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v155 + 36)
               + *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153 + 36) * v156;
      }
      else if ( ((*(_WORD *)(*(_DWORD *)v52 + 136) >> 1) & 1) != 0 )
      {
        v132 = (int)(timeline15 / 15.0 * 30.0 * 160.0);
        v130 = (int)(*(float *)(*(_DWORD *)v52 + 168) * 30.0 * 160.0);
        rf_vector3_copy_return_destination(v133, (float *)(*(_DWORD *)v52 + 228));
        rf_matrix3_construct((char *)v129);
        rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)v52 + 240), v129);
        rf_vector3_copy_return_destination(&v125, (float *)(*(_DWORD *)v52 + 256));
        rf_vector3_default_construct_noop(v128);
        if ( **(_WORD **)(*(_DWORD *)v52 + 224) )
        {
          v16 = rf_scene_key_tracks_sample_vector0(*(unsigned __int16 **)(*(_DWORD *)v52 + 224), v78, v132 - v130);
          rf_vector_copy(v128, v77, v16);
        }
        else
        {
          rf_vector_copy(v128, v76, *(const float **)(*(_DWORD *)v52 + 220));
        }
        rf_matrix3_construct((char *)v131);
        if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)v52 + 224) + 2) )
        {
          rf_scene_key_tracks_sample_quaternion(*(_DWORD *)(*(_DWORD *)v52 + 224), v124, v132 - v130, 0);
          rf_quaternion_to_matrix3_rows(v124, v131);
        }
        else
        {
          rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 12), v131);
        }
        rf_vector3_default_construct_noop(&v134);
        if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)v52 + 224) + 4) )
        {
          v17 = rf_scene_key_tracks_sample_vector2(*(_DWORD *)(*(_DWORD *)v52 + 224), v75, v132 - v130);
          rf_vector_copy(&v134, v74, v17);
        }
        else
        {
          rf_vector_copy(&v134, v73, (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 28));
        }
        rf_vector_copy(v52 + 1, v72, (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
        v52[1] = v52[1] * v125;
        v52[2] = v52[2] * v126;
        v52[3] = v52[3] * v127;
        rf_vector_rotate_by_matrix3(v52 + 1, v129);
        rf_vector_accumulate(v52 + 1, v133);
        v52[1] = v52[1] * v134;
        v52[2] = v52[2] * v135;
        v52[3] = v52[3] * v136;
        rf_vector_rotate_by_matrix3(v52 + 1, v131);
        rf_vector_accumulate(v52 + 1, v128);
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
        {
          rf_vector3_copy_return_destination(&scale_x, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 20));
          rf_vector3_copy_return_destination(&v30, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
          v18 = rf_scene_unpack_signed_vertex(
                  v71,
                  (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 4) + 6 * i),
                  v30,
                  v31,
                  *(float *)&v32,
                  scale_x,
                  *(float *)&v34,
                  value);
          rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v70, v18);
          *(float *)(12 * i + *((_DWORD *)v52 + 32)) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i) * v125;
          *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) * v126;
          *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) * v127;
          rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v129);
          rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), v133);
          *(float *)(12 * i + *((_DWORD *)v52 + 32)) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i) * v134;
          *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) * v135;
          *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) * v136;
          rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v131);
          rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), v128);
        }
        if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 0x801) != 0
          && *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) >= 0.0 )
        {
          v42 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) * v125 * v134);
          v52[4] = v42;
          v41 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 36) * v127 * v136);
          v52[5] = v41;
        }
      }
      else
      {
        rf_matrix3_construct((char *)v122);
        rf_matrix3_construct((char *)v114);
        rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155 + 12), v122);
        rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153 + 12), v114);
        rf_vector3_copy_return_destination(v121, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155 + 28));
        rf_vector3_copy_return_destination(vector, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153 + 28));
        if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 0x801) != 0
          && *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) >= 0.0 )
        {
          value = COERCE_FLOAT(rf_vector_multiply_scalar(vector, v68, v156));
          v40 = 1.0 - v156;
          v19 = rf_vector_multiply_scalar(v121, v69, v40);
          rf_vector_add(v19, v113, (const float *)LODWORD(value));
          v39 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) * v113[0]);
          v52[4] = v39;
          v38 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 36) * v113[2]);
          v52[5] = v38;
        }
        rf_vector3_copy_return_destination(&source, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
        rf_vector3_copy_return_destination(&v115, &source);
        source = source * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155 + 28);
        v119 = v119 * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155 + 32);
        v120 = v120 * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155 + 36);
        v115 = v115 * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153 + 28);
        v116 = v116 * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153 + 32);
        v117 = v117 * *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153 + 36);
        rf_vector_rotate_by_matrix3(&source, v122);
        rf_vector_rotate_by_matrix3(&v115, v114);
        rf_vector_accumulate(&source, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155));
        rf_vector_accumulate(&v115, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153));
        value = COERCE_FLOAT(rf_vector_multiply_scalar(&v115, v66, v156));
        v37 = 1.0 - v156;
        v20 = rf_vector_multiply_scalar(&source, v67, v37);
        v21 = rf_vector_add(v20, v65, (const float *)LODWORD(value));
        rf_vector_copy(v52 + 1, v64, v21);
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
        {
          rf_vector3_copy_return_destination(&scale_x, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 20));
          rf_vector3_copy_return_destination(&v30, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
          v22 = rf_scene_unpack_signed_vertex(
                  v63,
                  (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 4) + 6 * i),
                  v30,
                  v31,
                  *(float *)&v32,
                  scale_x,
                  *(float *)&v34,
                  value);
          rf_vector_copy(&source, v62, v22);
          rf_vector_copy(&v115, v61, &source);
          source = source * v121[0];
          v119 = v119 * v121[1];
          v120 = v120 * v121[2];
          v115 = v115 * vector[0];
          v116 = v116 * vector[1];
          v117 = v117 * vector[2];
          rf_vector_rotate_by_matrix3(&source, v122);
          rf_vector_rotate_by_matrix3(&v115, v114);
          rf_vector_accumulate(&source, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v155));
          rf_vector_accumulate(&v115, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * v153));
          value = COERCE_FLOAT(rf_vector_multiply_scalar(&v115, v59, v156));
          v34 = v58;
          v36 = 1.0 - v156;
          v23 = rf_vector_multiply_scalar(&source, v60, v36);
          v24 = rf_vector_add(v23, v34, (const float *)LODWORD(value));
          rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v57, v24);
        }
      }
      *((_BYTE *)v52 + 144) = *(int *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * v153) < 0;
    }
    else
    {
      if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 4) != 0 )
      {
        rf_vector_copy(
          v52 + 1,
          copy_result,
          (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 8));
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
        {
          rf_vector3_copy_return_destination(
            &scale_x,
            (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 20));
          rf_vector3_copy_return_destination(
            &v30,
            (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 8));
          v3 = rf_scene_unpack_signed_vertex(
                 out_vertex,
                 (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204)
                                             + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1)
                                             + 4)
                                 + 6 * i),
                 v30,
                 v31,
                 *(float *)&v32,
                 scale_x,
                 *(float *)&v34,
                 value);
          rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), scale_y, v3);
        }
        v52[4] = *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 32);
        v52[5] = *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 36);
      }
      else
      {
        rf_vector3_default_construct_noop(scale_z);
        rf_matrix3_construct((char *)v147);
        rf_vector3_default_construct_noop(&destination);
        if ( ((*(_WORD *)(*(_DWORD *)v52 + 136) >> 1) & 1) != 0 )
        {
          v4 = *(_DWORD *)v52;
          v5 = (double)*(int *)(*(_DWORD *)v52 + 164);
          v49 = (*(_WORD *)(*(_DWORD *)v52 + 136) >> 2) & 0x3FFF;
          v144 = (int)((v5 / (double)v49 + *(float *)(v4 + 168)) * 30.0 * 160.0);
          v143 = (int)(*(float *)(*(_DWORD *)v52 + 168) * 30.0 * 160.0);
          rf_vector3_copy_return_destination(v145, (float *)(*(_DWORD *)v52 + 228));
          rf_matrix3_construct((char *)v142);
          rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)v52 + 240), v142);
          rf_vector3_copy_return_destination(&v139, (float *)(*(_DWORD *)v52 + 256));
          if ( **(_WORD **)(*(_DWORD *)v52 + 224) )
          {
            v6 = rf_scene_key_tracks_sample_vector0(*(unsigned __int16 **)(*(_DWORD *)v52 + 224), v102, v144 - v143);
            rf_vector_copy(scale_z, v101, v6);
          }
          else
          {
            rf_vector_copy(scale_z, v100, *(const float **)(*(_DWORD *)v52 + 220));
          }
          if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)v52 + 224) + 2) )
          {
            rf_scene_key_tracks_sample_quaternion(*(_DWORD *)(*(_DWORD *)v52 + 224), v138, v144 - v143, 0);
            rf_quaternion_to_matrix3_rows(v138, v147);
          }
          else
          {
            rf_quaternion_to_matrix3_rows((float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 12), v147);
          }
          if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)v52 + 224) + 4) )
          {
            v7 = rf_scene_key_tracks_sample_vector2(*(_DWORD *)(*(_DWORD *)v52 + 224), v99, v144 - v143);
            rf_vector_copy(&destination, v98, v7);
          }
          else
          {
            rf_vector_copy(&destination, v97, (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 28));
          }
          rf_vector_copy(v52 + 1, v96, (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
          v52[1] = v52[1] * v139;
          v52[2] = v52[2] * v140;
          v52[3] = v52[3] * v141;
          rf_vector_rotate_by_matrix3(v52 + 1, v142);
          rf_vector_accumulate(v52 + 1, v145);
          v52[1] = v52[1] * destination;
          v52[2] = v52[2] * v149;
          v52[3] = v52[3] * v150;
          rf_vector_rotate_by_matrix3(v52 + 1, v147);
          rf_vector_accumulate(v52 + 1, scale_z);
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
          {
            rf_vector3_copy_return_destination(&scale_x, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 20));
            rf_vector3_copy_return_destination(&v30, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
            v8 = rf_scene_unpack_signed_vertex(
                   v95,
                   (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 4) + 6 * i),
                   v30,
                   v31,
                   *(float *)&v32,
                   scale_x,
                   *(float *)&v34,
                   value);
            rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v94, v8);
            *(float *)(12 * i + *((_DWORD *)v52 + 32)) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i) * v139;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) * v140;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) * v141;
            rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v142);
            rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), v145);
            *(float *)(12 * i + *((_DWORD *)v52 + 32)) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i) * destination;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) * v149;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) * v150;
            rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v147);
            rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), scale_z);
          }
          if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 0x801) != 0
            && *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) >= 0.0 )
          {
            v48 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) * v139 * destination);
            v52[4] = v48;
            v47 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 36) * v141 * v150);
            v52[5] = v47;
          }
        }
        else
        {
          rf_vector_copy(
            scale_z,
            v93,
            (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1)));
          rf_float4_assign_components_return_this(
            v137,
            (float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 12));
          rf_quaternion_to_matrix3_rows(v137, v147);
          rf_vector_copy(
            &destination,
            v92,
            (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 220) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1) + 28));
          rf_vector_copy(v52 + 1, v91, (const float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
          v52[1] = v52[1] * destination;
          v52[2] = v52[2] * v149;
          v52[3] = v52[3] * v150;
          rf_vector_rotate_by_matrix3(v52 + 1, v147);
          rf_vector_accumulate(v52 + 1, scale_z);
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
          {
            rf_vector3_copy_return_destination(&scale_x, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 20));
            rf_vector3_copy_return_destination(&v30, (float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 8));
            v9 = rf_scene_unpack_signed_vertex(
                   v90,
                   (const __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 4) + 6 * i),
                   v30,
                   v31,
                   *(float *)&v32,
                   scale_x,
                   *(float *)&v34,
                   value);
            rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v89, v9);
            *(float *)(12 * i + *((_DWORD *)v52 + 32)) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i) * destination;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 4) * v149;
            *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) = *(float *)(*((_DWORD *)v52 + 32) + 12 * i + 8) * v150;
            rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v147);
            rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), scale_z);
          }
          if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 0x801) != 0
            && *(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) >= 0.0 )
          {
            v46 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 32) * destination);
            v52[4] = v46;
            v45 = fabs(*(float *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 36) * v150);
            v52[5] = v45;
          }
        }
      }
      *((_BYTE *)v52 + 144) = *(int *)(*(_DWORD *)(*(_DWORD *)v52 + 204) + 40 * (*(_DWORD *)(*(_DWORD *)v52 + 164) - 1)) < 0;
    }
    if ( (*(_DWORD *)(*(_DWORD *)v52 + 276) & 0x100) != 0 )
    {
      if ( v153 < *(_DWORD *)(*(_DWORD *)v52 + 164) )
      {
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 180); ++i )
        {
          for ( j = 0; j < 3; ++j )
          {
            v111 = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212) + 4 * v155) + 24 * i + 4 * j);
            v109 = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212) + 4 * v153) + 24 * i + 4 * j);
            v112 = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212) + 4 * v155) + 24 * i + 4 * j + 12);
            v110 = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212) + 4 * v153) + 24 * i + 4 * j + 12);
            *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j) = (1.0 - v156) * v111 + v109 * v156;
            *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j + 12) = (1.0 - v156) * v112 + v110 * v156;
          }
        }
      }
      else
      {
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 180); ++i )
        {
          for ( j = 0; j < 3; ++j )
          {
            *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j) = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212)
                                                                                      + 4
                                                                                      * *(_DWORD *)(*(_DWORD *)v52 + 164)
                                                                                      - 4)
                                                                          + 24 * i
                                                                          + 4 * j);
            *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j + 12) = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v52 + 212)
                                                                                           + 4
                                                                                           * *(_DWORD *)(*(_DWORD *)v52 + 164)
                                                                                           - 4)
                                                                               + 24 * i
                                                                               + 4 * j
                                                                               + 12);
          }
        }
      }
    }
    else
    {
      for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 180); ++i )
      {
        for ( j = 0; j < 3; ++j )
        {
          *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j) = *(float *)(**(_DWORD **)(*(_DWORD *)v52 + 212)
                                                                        + 24 * i
                                                                        + 4 * j);
          *(float *)(*((_DWORD *)v52 + 33) + 24 * i + 4 * j + 12) = *(float *)(**(_DWORD **)(*(_DWORD *)v52 + 212)
                                                                             + 24 * i
                                                                             + 4 * j
                                                                             + 12);
        }
      }
    }
    if ( ((*((_DWORD *)v52 + 7) >> 30) & 1) != 0 )
    {
      for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
      {
        rf_vector_rotate_by_matrix3((float *)(*((_DWORD *)v52 + 32) + 12 * i), v52 + 11);
        rf_vector_accumulate((float *)(*((_DWORD *)v52 + 32) + 12 * i), v52 + 8);
      }
      rf_vector_rotate_by_matrix3(v52 + 1, v52 + 11);
      rf_vector_accumulate(v52 + 1, v52 + 8);
    }
    else if ( ((*((_DWORD *)v52 + 7) >> 29) & 1) != 0 )
    {
      rf_vector3_default_construct_noop(v108);
      rf_matrix3_construct((char *)v107);
      rf_model_handle_get_node_transform_adapter(*((_DWORD **)v52 + 6), v108, v107, (_DWORD)v52[7] & 0x1FFFFFFF);
      rf_affine3x4_set_rotation_translation(v106, v108, v107);
      for ( i = 0; i < *(_DWORD *)(*(_DWORD *)v52 + 176); ++i )
      {
        v25 = rf_affine3x4_transform_point(v106, v56, (float *)(*((_DWORD *)v52 + 32) + 12 * i));
        rf_vector_copy((float *)(*((_DWORD *)v52 + 32) + 12 * i), v55, v25);
      }
      v26 = rf_affine3x4_transform_point(v106, v54, v52 + 1);
      rf_vector_copy(v52 + 1, v53, v26);
    }
  }
  else
  {
    *((_BYTE *)v52 + 144) = 0;
  }
}

