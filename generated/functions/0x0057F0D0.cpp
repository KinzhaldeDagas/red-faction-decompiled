// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057F0D0 rf_debug_draw_oriented_wire_box
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Inputs center vec3, matrix3 axes, FULL dimensions vec3, packed render state. Halves dimensions, constructs8 corners center +/- axis0*halfwidth +/- axis1*halfheight +/- axis2*halfdepth. Emits12 edge calls via0x57E740 (two four-edge loops and four connectors), returns1 unconditionally even if backend wrapper declines drawing. No normalization or extent checks.
char __cdecl rf_debug_draw_oriented_wire_box(float *lhs, float *a2, float *vector, int a4)
{
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
  float *v37; // [esp+8h] [ebp-318h]
  float *v38; // [esp+8h] [ebp-318h]
  float *v39; // [esp+8h] [ebp-318h]
  float *v40; // [esp+8h] [ebp-318h]
  float *v41; // [esp+8h] [ebp-318h]
  float *v42; // [esp+8h] [ebp-318h]
  float *v43; // [esp+8h] [ebp-318h]
  float *v44; // [esp+8h] [ebp-318h]
  float *scalar; // [esp+10h] [ebp-310h]
  float *scalara; // [esp+10h] [ebp-310h]
  float *scalarb; // [esp+10h] [ebp-310h]
  float *scalarc; // [esp+10h] [ebp-310h]
  float *scalard; // [esp+10h] [ebp-310h]
  float *scalare; // [esp+10h] [ebp-310h]
  float *scalarf; // [esp+10h] [ebp-310h]
  float *scalarg; // [esp+10h] [ebp-310h]
  float v53[3]; // [esp+14h] [ebp-30Ch] BYREF
  float v54[3]; // [esp+20h] [ebp-300h] BYREF
  float v55[3]; // [esp+2Ch] [ebp-2F4h] BYREF
  float v56[3]; // [esp+38h] [ebp-2E8h] BYREF
  float v57[3]; // [esp+44h] [ebp-2DCh] BYREF
  float v58[3]; // [esp+50h] [ebp-2D0h] BYREF
  float v59[3]; // [esp+5Ch] [ebp-2C4h] BYREF
  float v60[3]; // [esp+68h] [ebp-2B8h] BYREF
  float v61[3]; // [esp+74h] [ebp-2ACh] BYREF
  float v62[3]; // [esp+80h] [ebp-2A0h] BYREF
  float v63[3]; // [esp+8Ch] [ebp-294h] BYREF
  float v64[3]; // [esp+98h] [ebp-288h] BYREF
  float v65[3]; // [esp+A4h] [ebp-27Ch] BYREF
  float v66[3]; // [esp+B0h] [ebp-270h] BYREF
  float v67[3]; // [esp+BCh] [ebp-264h] BYREF
  float v68[3]; // [esp+C8h] [ebp-258h] BYREF
  float v69[3]; // [esp+D4h] [ebp-24Ch] BYREF
  float v70[3]; // [esp+E0h] [ebp-240h] BYREF
  float v71[3]; // [esp+ECh] [ebp-234h] BYREF
  float v72[3]; // [esp+F8h] [ebp-228h] BYREF
  float v73[3]; // [esp+104h] [ebp-21Ch] BYREF
  float v74[3]; // [esp+110h] [ebp-210h] BYREF
  float v75[3]; // [esp+11Ch] [ebp-204h] BYREF
  float v76[3]; // [esp+128h] [ebp-1F8h] BYREF
  float v77[3]; // [esp+134h] [ebp-1ECh] BYREF
  float v78[3]; // [esp+140h] [ebp-1E0h] BYREF
  float v79[3]; // [esp+14Ch] [ebp-1D4h] BYREF
  float v80[3]; // [esp+158h] [ebp-1C8h] BYREF
  float v81[3]; // [esp+164h] [ebp-1BCh] BYREF
  float v82[3]; // [esp+170h] [ebp-1B0h] BYREF
  float v83[3]; // [esp+17Ch] [ebp-1A4h] BYREF
  float v84[3]; // [esp+188h] [ebp-198h] BYREF
  float v85[3]; // [esp+194h] [ebp-18Ch] BYREF
  float v86[3]; // [esp+1A0h] [ebp-180h] BYREF
  float v87[3]; // [esp+1ACh] [ebp-174h] BYREF
  float v88[3]; // [esp+1B8h] [ebp-168h] BYREF
  float v89[3]; // [esp+1C4h] [ebp-15Ch] BYREF
  float v90[3]; // [esp+1D0h] [ebp-150h] BYREF
  float v91[3]; // [esp+1DCh] [ebp-144h] BYREF
  float v92[3]; // [esp+1E8h] [ebp-138h] BYREF
  float v93[3]; // [esp+1F4h] [ebp-12Ch] BYREF
  float v94[3]; // [esp+200h] [ebp-120h] BYREF
  float v95[3]; // [esp+20Ch] [ebp-114h] BYREF
  float v96[3]; // [esp+218h] [ebp-108h] BYREF
  float v97[3]; // [esp+224h] [ebp-FCh] BYREF
  float v98[3]; // [esp+230h] [ebp-F0h] BYREF
  float v99[3]; // [esp+23Ch] [ebp-E4h] BYREF
  float sum_result[3]; // [esp+248h] [ebp-D8h] BYREF
  float v101[3]; // [esp+254h] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+260h] [ebp-C0h] BYREF
  float v103[3]; // [esp+26Ch] [ebp-B4h] BYREF
  float v104[3]; // [esp+278h] [ebp-A8h] BYREF
  float v105[3]; // [esp+284h] [ebp-9Ch] BYREF
  float v106[3]; // [esp+290h] [ebp-90h] BYREF
  float out_vector[3]; // [esp+29Ch] [ebp-84h] BYREF
  float v108[3]; // [esp+2A8h] [ebp-78h] BYREF
  float scaled_result; // [esp+2B4h] [ebp-6Ch] BYREF
  float v110; // [esp+2B8h] [ebp-68h]
  float v111; // [esp+2BCh] [ebp-64h]
  float destination[3]; // [esp+2C0h] [ebp-60h] BYREF
  float v113[3]; // [esp+2CCh] [ebp-54h] BYREF
  float v114[3]; // [esp+2D8h] [ebp-48h] BYREF
  float v115[3]; // [esp+2E4h] [ebp-3Ch] BYREF
  float v116[3]; // [esp+2F0h] [ebp-30h] BYREF
  float v117[3]; // [esp+2FCh] [ebp-24h] BYREF
  float v118[3]; // [esp+308h] [ebp-18h] BYREF
  float v119[3]; // [esp+314h] [ebp-Ch] BYREF

  rf_vector_construct_no_unwind((char *)destination, 0xCu, 8, rf_vector3_default_construct_noop);
  rf_vector_multiply_scalar(vector, &scaled_result, 0.5);
  scalar = rf_vector_multiply_scalar(a2 + 6, v104, v111);
  v37 = rf_vector_multiply_scalar(a2 + 3, v106, v110);
  v4 = rf_vector_multiply_scalar(a2, v108, scaled_result);
  v5 = rf_vector_subtract(lhs, out_vector, v4);
  v6 = rf_vector_subtract(v5, v105, v37);
  v7 = rf_vector_subtract(v6, v103, scalar);
  rf_vector_copy(destination, copy_result, v7);
  scalara = rf_vector_multiply_scalar(a2 + 6, v97, v111);
  v38 = rf_vector_multiply_scalar(a2 + 3, v99, v110);
  v8 = rf_vector_multiply_scalar(a2, v101, scaled_result);
  v9 = rf_vector_add(lhs, sum_result, v8);
  v10 = rf_vector_subtract(v9, v98, v38);
  v11 = rf_vector_subtract(v10, v96, scalara);
  rf_vector_copy(v113, v95, v11);
  scalarb = rf_vector_multiply_scalar(a2 + 6, v90, v111);
  v39 = rf_vector_multiply_scalar(a2 + 3, v92, v110);
  v12 = rf_vector_multiply_scalar(a2, v94, scaled_result);
  v13 = rf_vector_add(lhs, v93, v12);
  v14 = rf_vector_subtract(v13, v91, v39);
  v15 = rf_vector_add(v14, v89, scalarb);
  rf_vector_copy(v114, v88, v15);
  scalarc = rf_vector_multiply_scalar(a2 + 6, v83, v111);
  v40 = rf_vector_multiply_scalar(a2 + 3, v85, v110);
  v16 = rf_vector_multiply_scalar(a2, v87, scaled_result);
  v17 = rf_vector_subtract(lhs, v86, v16);
  v18 = rf_vector_subtract(v17, v84, v40);
  v19 = rf_vector_add(v18, v82, scalarc);
  rf_vector_copy(v115, v81, v19);
  scalard = rf_vector_multiply_scalar(a2 + 6, v76, v111);
  v41 = rf_vector_multiply_scalar(a2 + 3, v78, v110);
  v20 = rf_vector_multiply_scalar(a2, v80, scaled_result);
  v21 = rf_vector_subtract(lhs, v79, v20);
  v22 = rf_vector_add(v21, v77, v41);
  v23 = rf_vector_subtract(v22, v75, scalard);
  rf_vector_copy(v116, v74, v23);
  scalare = rf_vector_multiply_scalar(a2 + 6, v69, v111);
  v42 = rf_vector_multiply_scalar(a2 + 3, v71, v110);
  v24 = rf_vector_multiply_scalar(a2, v73, scaled_result);
  v25 = rf_vector_add(lhs, v72, v24);
  v26 = rf_vector_add(v25, v70, v42);
  v27 = rf_vector_subtract(v26, v68, scalare);
  rf_vector_copy(v117, v67, v27);
  scalarf = rf_vector_multiply_scalar(a2 + 6, v62, v111);
  v43 = rf_vector_multiply_scalar(a2 + 3, v64, v110);
  v28 = rf_vector_multiply_scalar(a2, v66, scaled_result);
  v29 = rf_vector_add(lhs, v65, v28);
  v30 = rf_vector_add(v29, v63, v43);
  v31 = rf_vector_add(v30, v61, scalarf);
  rf_vector_copy(v118, v60, v31);
  scalarg = rf_vector_multiply_scalar(a2 + 6, v55, v111);
  v44 = rf_vector_multiply_scalar(a2 + 3, v57, v110);
  v32 = rf_vector_multiply_scalar(a2, v59, scaled_result);
  v33 = rf_vector_subtract(lhs, v58, v32);
  v34 = rf_vector_add(v33, v56, v44);
  v35 = rf_vector_add(v34, v54, scalarg);
  rf_vector_copy(v119, v53, v35);
  rf_debug_draw_world_line_backend_dispatch(destination, v113, a4);
  rf_debug_draw_world_line_backend_dispatch(v113, v114, a4);
  rf_debug_draw_world_line_backend_dispatch(v114, v115, a4);
  rf_debug_draw_world_line_backend_dispatch(v115, destination, a4);
  rf_debug_draw_world_line_backend_dispatch(v116, v117, a4);
  rf_debug_draw_world_line_backend_dispatch(v117, v118, a4);
  rf_debug_draw_world_line_backend_dispatch(v118, v119, a4);
  rf_debug_draw_world_line_backend_dispatch(v119, v116, a4);
  rf_debug_draw_world_line_backend_dispatch(destination, v116, a4);
  rf_debug_draw_world_line_backend_dispatch(v113, v117, a4);
  rf_debug_draw_world_line_backend_dispatch(v114, v118, a4);
  rf_debug_draw_world_line_backend_dispatch(v115, v119, a4);
  return 1;
}

