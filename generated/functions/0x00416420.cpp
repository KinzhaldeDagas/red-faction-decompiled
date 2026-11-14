// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416420 rf_clutter_render_three_clock_hands
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl clutter pointer,ALresult of FINAL polygon submission only. No own NULL/class/is_clock/visibility/backend/texture/finite/radius guard. Let P=common60,F=commonforwardrow96,U=commonuprow84,R=-commonrightrow72,N=-F. B=P+F*float0.02500000037252903,with native per-vector-helper F32 staging. Samples globalF32 counter6FC42C THREE independently:__ftol2_sse,lowEAX sign-extended byCDQ,signed IDIV remainders modulo60/3600/216000 (negative remainders preserved). Each handangle isF32((signedRemainder/DOUBLEperiod)*DOUBLE6.2831854820251465);no wall-clock/time-unit normalization inferred. Texture globals666B68/666B80/666B70 correspond original clock_seconds/minutes/hours files. For hands
// respectively widthF32(0.02500000037252903,0.05000000074505806,0.05000000074505806),lengthfactor(0.75,0.75,0.5)*commonradius120. H=(R*F32.5)*width,V=(U*radius)*lengthfactor,each helper stage roundsF32;unrotated verticesB+H,(B+H)-V,(B-H)-V,B-H. Rotates EACH of four vertices about pivotP/axisN via559BD0(storedangle);that helper uses negative physical right-handed angle relative toN. Submits each4-vertex quad with UV(0,0),(1,0),(1,1),(0,1),whiteRGBA255,and packed render tuple(2,2,3,3,1,3). All3 submissions occur regardless prior returnvalues;final hours result alone returned. Constructor iterators use XYZstride12/count4 and UVstride8/count4 but callback is no-op vector constructor,so NO12-byte UV writes/overrun;all coordinates/UVs assigned explicitly. Stack-only scratch,no owned allocation. Native conversion behavior for nonfinite/out-of-range counter delegated,not sanitized.
char __cdecl rf_clutter_render_three_clock_hands(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
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
  float *v28; // eax
  float *v29; // eax
  float *v30; // eax
  float *v31; // eax
  float *v32; // eax
  float *v33; // eax
  float *v34; // eax
  float *v35; // eax
  float *v36; // eax
  float *v37; // eax
  float *v38; // eax
  float *v39; // eax
  float *v40; // eax
  float *v41; // eax
  float *v42; // eax
  float *v43; // eax
  float *v44; // eax
  float *v45; // eax
  float *v46; // eax
  float *v47; // eax
  float *v48; // eax
  float *v49; // eax
  float *scalar; // [esp+10h] [ebp-3B8h]
  float *scalara; // [esp+10h] [ebp-3B8h]
  float *scalarb; // [esp+10h] [ebp-3B8h]
  float *scalarc; // [esp+10h] [ebp-3B8h]
  float *scalard; // [esp+10h] [ebp-3B8h]
  float *scalare; // [esp+10h] [ebp-3B8h]
  float v57[3]; // [esp+14h] [ebp-3B4h] BYREF
  float v58[3]; // [esp+20h] [ebp-3A8h] BYREF
  float v59[3]; // [esp+2Ch] [ebp-39Ch] BYREF
  float v60[3]; // [esp+38h] [ebp-390h] BYREF
  float v61[3]; // [esp+44h] [ebp-384h] BYREF
  float v62[3]; // [esp+50h] [ebp-378h] BYREF
  float v63[3]; // [esp+5Ch] [ebp-36Ch] BYREF
  float v64[3]; // [esp+68h] [ebp-360h] BYREF
  float v65[3]; // [esp+74h] [ebp-354h] BYREF
  float v66[3]; // [esp+80h] [ebp-348h] BYREF
  float v67[3]; // [esp+8Ch] [ebp-33Ch] BYREF
  float v68[3]; // [esp+98h] [ebp-330h] BYREF
  float v69[3]; // [esp+A4h] [ebp-324h] BYREF
  float v70[3]; // [esp+B0h] [ebp-318h] BYREF
  float v71[3]; // [esp+BCh] [ebp-30Ch] BYREF
  float v72[3]; // [esp+C8h] [ebp-300h] BYREF
  float v73[3]; // [esp+D4h] [ebp-2F4h] BYREF
  float v74[3]; // [esp+E0h] [ebp-2E8h] BYREF
  float v75[3]; // [esp+ECh] [ebp-2DCh] BYREF
  float v76[3]; // [esp+F8h] [ebp-2D0h] BYREF
  float v77[3]; // [esp+104h] [ebp-2C4h] BYREF
  float v78[3]; // [esp+110h] [ebp-2B8h] BYREF
  float v79[3]; // [esp+11Ch] [ebp-2ACh] BYREF
  float v80[3]; // [esp+128h] [ebp-2A0h] BYREF
  float v81[3]; // [esp+134h] [ebp-294h] BYREF
  float v82[3]; // [esp+140h] [ebp-288h] BYREF
  float v83[3]; // [esp+14Ch] [ebp-27Ch] BYREF
  float v84[3]; // [esp+158h] [ebp-270h] BYREF
  float v85[3]; // [esp+164h] [ebp-264h] BYREF
  float v86[3]; // [esp+170h] [ebp-258h] BYREF
  float v87[3]; // [esp+17Ch] [ebp-24Ch] BYREF
  float v88[3]; // [esp+188h] [ebp-240h] BYREF
  float v89[3]; // [esp+194h] [ebp-234h] BYREF
  float v90[3]; // [esp+1A0h] [ebp-228h] BYREF
  float v91[3]; // [esp+1ACh] [ebp-21Ch] BYREF
  float v92[3]; // [esp+1B8h] [ebp-210h] BYREF
  float v93[3]; // [esp+1C4h] [ebp-204h] BYREF
  float v94[3]; // [esp+1D0h] [ebp-1F8h] BYREF
  float v95[3]; // [esp+1DCh] [ebp-1ECh] BYREF
  float v96[3]; // [esp+1E8h] [ebp-1E0h] BYREF
  float v97[3]; // [esp+1F4h] [ebp-1D4h] BYREF
  float v98[3]; // [esp+200h] [ebp-1C8h] BYREF
  float v99[3]; // [esp+20Ch] [ebp-1BCh] BYREF
  float v100[3]; // [esp+218h] [ebp-1B0h] BYREF
  float v101[3]; // [esp+224h] [ebp-1A4h] BYREF
  float v102[3]; // [esp+230h] [ebp-198h] BYREF
  float v103[3]; // [esp+23Ch] [ebp-18Ch] BYREF
  float v104[3]; // [esp+248h] [ebp-180h] BYREF
  float v105[3]; // [esp+254h] [ebp-174h] BYREF
  float v106[3]; // [esp+260h] [ebp-168h] BYREF
  float v107[3]; // [esp+26Ch] [ebp-15Ch] BYREF
  float v108[3]; // [esp+278h] [ebp-150h] BYREF
  float v109[3]; // [esp+284h] [ebp-144h] BYREF
  float v110[3]; // [esp+290h] [ebp-138h] BYREF
  float v111[3]; // [esp+29Ch] [ebp-12Ch] BYREF
  float v112[3]; // [esp+2A8h] [ebp-120h] BYREF
  float out_vector[3]; // [esp+2B4h] [ebp-114h] BYREF
  float v114[3]; // [esp+2C0h] [ebp-108h] BYREF
  float v115[3]; // [esp+2CCh] [ebp-FCh] BYREF
  float v116[3]; // [esp+2D8h] [ebp-F0h] BYREF
  float v117[3]; // [esp+2E4h] [ebp-E4h] BYREF
  float v118[3]; // [esp+2F0h] [ebp-D8h] BYREF
  float copy_result[3]; // [esp+2FCh] [ebp-CCh] BYREF
  float sum_result[3]; // [esp+308h] [ebp-C0h] BYREF
  float v121[3]; // [esp+314h] [ebp-B4h] BYREF
  float v122[3]; // [esp+320h] [ebp-A8h] BYREF
  float scaled_result[3]; // [esp+32Ch] [ebp-9Ch] BYREF
  float lhs[3]; // [esp+338h] [ebp-90h] BYREF
  int v125; // [esp+344h] [ebp-84h]
  float vector[3]; // [esp+348h] [ebp-80h] BYREF
  float v127; // [esp+354h] [ebp-74h] BYREF
  float v128; // [esp+358h] [ebp-70h]
  float v129; // [esp+35Ch] [ebp-6Ch]
  float v130; // [esp+360h] [ebp-68h]
  float v131; // [esp+364h] [ebp-64h]
  float v132; // [esp+368h] [ebp-60h]
  float v133; // [esp+36Ch] [ebp-5Ch]
  float v134; // [esp+370h] [ebp-58h]
  int v135; // [esp+374h] [ebp-54h] BYREF
  int v136; // [esp+378h] [ebp-50h]
  int v137; // [esp+37Ch] [ebp-4Ch]
  int v138[3]; // [esp+380h] [ebp-48h] BYREF
  char v139[4]; // [esp+38Ch] [ebp-3Ch] BYREF
  float v140; // [esp+390h] [ebp-38h]
  float v141; // [esp+394h] [ebp-34h]
  float destination[3]; // [esp+398h] [ebp-30h] BYREF
  float v143[3]; // [esp+3A4h] [ebp-24h] BYREF
  float v144[3]; // [esp+3B0h] [ebp-18h] BYREF
  float v145[3]; // [esp+3BCh] [ebp-Ch] BYREF

  v139[0] = -1;
  v139[1] = -1;
  v139[2] = -1;
  v139[3] = -1;
  rf_vector3_copy_return_destination(lhs, (float *)(a1 + 60));
  v1 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, 0.025);
  rf_vector_accumulate(lhs, v1);
  v140 = *(float *)(a1 + 120);
  rf_render_state_pack(&v135, 2, 2, 3, 3, 1, 3);
  rf_vector_negate((float *)(a1 + 96), (float *)v138);
  rf_vector_negate((float *)(a1 + 72), vector);
  rf_vector_construct_no_unwind((char *)destination, 0xCu, 4, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind((char *)&v127, 8u, 4, rf_vector3_default_construct_noop);
  v136 = (int)unk_6FC42C % 60;
  v137 = (int)unk_6FC42C % 3600;
  v125 = (int)unk_6FC42C % 216000;
  v141 = (double)v136 / 60.0 * 6.283185482025146;
  v2 = rf_vector_multiply_scalar(vector, v122, 0.5);
  v3 = rf_vector_multiply_scalar(v2, v121, 0.025);
  v4 = rf_vector_add(lhs, sum_result, v3);
  rf_vector_copy(destination, copy_result, v4);
  v127 = 0.0;
  v128 = 0.0;
  v5 = rf_vector_multiply_scalar((const float *)(a1 + 84), v115, v140);
  scalar = rf_vector_multiply_scalar(v5, v114, 0.75);
  v6 = rf_vector_multiply_scalar(vector, v118, 0.5);
  v7 = rf_vector_multiply_scalar(v6, v117, 0.025);
  v8 = rf_vector_add(lhs, v116, v7);
  v9 = rf_vector_subtract(v8, out_vector, scalar);
  rf_vector_copy(v143, v112, v9);
  v129 = 1.0;
  v130 = 0.0;
  v10 = rf_vector_multiply_scalar((const float *)(a1 + 84), v108, v140);
  scalara = rf_vector_multiply_scalar(v10, v107, 0.75);
  v11 = rf_vector_multiply_scalar(vector, v111, 0.5);
  v12 = rf_vector_multiply_scalar(v11, v110, 0.025);
  v13 = rf_vector_subtract(lhs, v109, v12);
  v14 = rf_vector_subtract(v13, v106, scalara);
  rf_vector_copy(v144, v105, v14);
  v131 = 1.0;
  v132 = 1.0;
  v15 = rf_vector_multiply_scalar(vector, v104, 0.5);
  v16 = rf_vector_multiply_scalar(v15, v103, 0.025);
  v17 = rf_vector_subtract(lhs, v102, v16);
  rf_vector_copy(v145, v101, v17);
  v133 = 0.0;
  v134 = 1.0;
  rf_point_rotate_about_axis_pivot((int)destination, (int)destination, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v143, (int)v143, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v144, (int)v144, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v145, (int)v145, v141, a1 + 60, (int)v138);
  rf_renderer_submit_textured_world_polygon_color4_dispatch(dword_666B68, 4, (int)destination, (int)&v127, v135, v139);
  v141 = (double)v137 / 3600.0 * 6.283185482025146;
  v18 = rf_vector_multiply_scalar(vector, v100, 0.5);
  v19 = rf_vector_multiply_scalar(v18, v99, 0.050000001);
  v20 = rf_vector_add(lhs, v98, v19);
  rf_vector_copy(destination, v97, v20);
  v127 = 0.0;
  v128 = 0.0;
  v21 = rf_vector_multiply_scalar((const float *)(a1 + 84), v93, v140);
  scalarb = rf_vector_multiply_scalar(v21, v92, 0.75);
  v22 = rf_vector_multiply_scalar(vector, v96, 0.5);
  v23 = rf_vector_multiply_scalar(v22, v95, 0.050000001);
  v24 = rf_vector_add(lhs, v94, v23);
  v25 = rf_vector_subtract(v24, v91, scalarb);
  rf_vector_copy(v143, v90, v25);
  v129 = 1.0;
  v130 = 0.0;
  v26 = rf_vector_multiply_scalar((const float *)(a1 + 84), v86, v140);
  scalarc = rf_vector_multiply_scalar(v26, v85, 0.75);
  v27 = rf_vector_multiply_scalar(vector, v89, 0.5);
  v28 = rf_vector_multiply_scalar(v27, v88, 0.050000001);
  v29 = rf_vector_subtract(lhs, v87, v28);
  v30 = rf_vector_subtract(v29, v84, scalarc);
  rf_vector_copy(v144, v83, v30);
  v131 = 1.0;
  v132 = 1.0;
  v31 = rf_vector_multiply_scalar(vector, v82, 0.5);
  v32 = rf_vector_multiply_scalar(v31, v81, 0.050000001);
  v33 = rf_vector_subtract(lhs, v80, v32);
  rf_vector_copy(v145, v79, v33);
  v133 = 0.0;
  v134 = 1.0;
  rf_point_rotate_about_axis_pivot((int)destination, (int)destination, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v143, (int)v143, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v144, (int)v144, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v145, (int)v145, v141, a1 + 60, (int)v138);
  rf_renderer_submit_textured_world_polygon_color4_dispatch(dword_666B80, 4, (int)destination, (int)&v127, v135, v139);
  v141 = (double)v125 / 216000.0 * 6.283185482025146;
  v34 = rf_vector_multiply_scalar(vector, v78, 0.5);
  v35 = rf_vector_multiply_scalar(v34, v77, 0.050000001);
  v36 = rf_vector_add(lhs, v76, v35);
  rf_vector_copy(destination, v75, v36);
  v127 = 0.0;
  v128 = 0.0;
  v37 = rf_vector_multiply_scalar((const float *)(a1 + 84), v71, v140);
  scalard = rf_vector_multiply_scalar(v37, v70, 0.5);
  v38 = rf_vector_multiply_scalar(vector, v74, 0.5);
  v39 = rf_vector_multiply_scalar(v38, v73, 0.050000001);
  v40 = rf_vector_add(lhs, v72, v39);
  v41 = rf_vector_subtract(v40, v69, scalard);
  rf_vector_copy(v143, v68, v41);
  v129 = 1.0;
  v130 = 0.0;
  v42 = rf_vector_multiply_scalar((const float *)(a1 + 84), v64, v140);
  scalare = rf_vector_multiply_scalar(v42, v63, 0.5);
  v43 = rf_vector_multiply_scalar(vector, v67, 0.5);
  v44 = rf_vector_multiply_scalar(v43, v66, 0.050000001);
  v45 = rf_vector_subtract(lhs, v65, v44);
  v46 = rf_vector_subtract(v45, v62, scalare);
  rf_vector_copy(v144, v61, v46);
  v131 = 1.0;
  v132 = 1.0;
  v47 = rf_vector_multiply_scalar(vector, v60, 0.5);
  v48 = rf_vector_multiply_scalar(v47, v59, 0.050000001);
  v49 = rf_vector_subtract(lhs, v58, v48);
  rf_vector_copy(v145, v57, v49);
  v133 = 0.0;
  v134 = 1.0;
  rf_point_rotate_about_axis_pivot((int)destination, (int)destination, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v143, (int)v143, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v144, (int)v144, v141, a1 + 60, (int)v138);
  rf_point_rotate_about_axis_pivot((int)v145, (int)v145, v141, a1 + 60, (int)v138);
  return rf_renderer_submit_textured_world_polygon_color4_dispatch(
           dword_666B70,
           4,
           (int)destination,
           (int)&v127,
           v135,
           v139);
}

