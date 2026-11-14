// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DA5E0 rf_renderer_draw_screen_tapered_world_segment
// UNREALRED VERIFIED [renderer-mesh-20261028]: Sixarguments worldendpointA,floatwidthA,worldendpointB,floatwidthB,packedstate,maxscreenlength; current widths appearint in decompiler but addresses passed tofloatwidth helper0x581AC0. Transforms/projects both endpoints,rejects projectionflagbit2 or sharedoutcodeANDnonzero. Converts widths topixels using cameraZ. Computes screenlength; if maxlength>1 and maxlength<length,truncates screenendpointB and interpolates itswidth,without changing originalcameraXYZ/reciprocal. Returnvalue=max(0,mean endpointcameraZ*0x18CD294),not renderedlength or success. Effectivewidth=max(widthA,widthB,1). If screenlength>=effectivewidth,usesangle0x567850(dy,dx) and originalwidths; else expandslength toeffectivewidth,expands eachwidth bymissinglength capped ateffectivewidth,and uses atan2(dy,dx),except abs(dx)<=0.01 selectsangle0. Clamps bothwidths>=1. Builds four
// preprojected48-byte vertices aroundscreenmidpoint,with endpointcameraXYZ/reciprocal copied,fullUV,whiteRGBA and projectedflag1. Submits4vertices mask13 via0x573220; ignoresdrawresult. No explicit clipping of generatedscreenquad,finitewidth or negativesize checks.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Prototype correction ONLY:width arguments2/4 are FLOAT world widths,not char. Verified wrapper57EAE0 FLD/FSTP passes full4-byte values;this callee passes ADDRESSES of these stack slots to width-to-pixels helper581AC0,which dereferences float. Six arguments endpointA,widthA,endpointB,widthB,state,maxScreenLength. Existing complete geometry/return behavior annotation preserved. Fix prevents false SLOBYTE truncation at callers;returns floating scaled mean-camera-depth metric,not boolean/drawn length.
double __cdecl rf_renderer_draw_screen_tapered_world_segment(
        const float *a1,
        float a2,
        const float *a3,
        float a4,
        unsigned int a5,
        float a6)
{
  float v7; // [esp+8h] [ebp-1D0h]
  float v8; // [esp+Ch] [ebp-1CCh]
  float X; // [esp+10h] [ebp-1C8h]
  float Y; // [esp+14h] [ebp-1C4h]
  float v11; // [esp+18h] [ebp-1C0h]
  double v12; // [esp+1Ch] [ebp-1BCh]
  float v13; // [esp+24h] [ebp-1B4h]
  float v14; // [esp+28h] [ebp-1B0h]
  float v15[3]; // [esp+2Ch] [ebp-1ACh] BYREF
  float v16[3]; // [esp+38h] [ebp-1A0h] BYREF
  float v17[3]; // [esp+44h] [ebp-194h] BYREF
  float copy_result[3]; // [esp+50h] [ebp-188h] BYREF
  float v19; // [esp+5Ch] [ebp-17Ch]
  float v20; // [esp+60h] [ebp-178h]
  float v21; // [esp+64h] [ebp-174h]
  float source[5]; // [esp+68h] [ebp-170h] BYREF
  float v23; // [esp+7Ch] [ebp-15Ch]
  unsigned __int8 v24; // [esp+80h] [ebp-158h]
  char v25; // [esp+81h] [ebp-157h]
  float v26; // [esp+98h] [ebp-140h]
  float v27; // [esp+9Ch] [ebp-13Ch]
  float v28; // [esp+A0h] [ebp-138h]
  float v29; // [esp+A4h] [ebp-134h]
  float v30; // [esp+A8h] [ebp-130h]
  float v31; // [esp+ACh] [ebp-12Ch]
  float v32; // [esp+B0h] [ebp-128h]
  void *v33[4]; // [esp+B4h] [ebp-124h] BYREF
  float v34; // [esp+C4h] [ebp-114h]
  float v35; // [esp+C8h] [ebp-110h]
  float v36[5]; // [esp+CCh] [ebp-10Ch] BYREF
  float v37; // [esp+E0h] [ebp-F8h]
  unsigned __int8 v38; // [esp+E4h] [ebp-F4h]
  char v39; // [esp+E5h] [ebp-F3h]
  float v40; // [esp+FCh] [ebp-DCh]
  float v41; // [esp+100h] [ebp-D8h]
  float v42; // [esp+104h] [ebp-D4h]
  float v43; // [esp+108h] [ebp-D0h]
  float v44; // [esp+10Ch] [ebp-CCh]
  float destination[6]; // [esp+110h] [ebp-C8h] BYREF
  char v46; // [esp+129h] [ebp-AFh]
  float v47; // [esp+12Ch] [ebp-ACh]
  float v48; // [esp+130h] [ebp-A8h]
  char v49; // [esp+13Ch] [ebp-9Ch]
  char v50; // [esp+13Dh] [ebp-9Bh]
  char v51; // [esp+13Eh] [ebp-9Ah]
  char v52; // [esp+13Fh] [ebp-99h]
  float v53[6]; // [esp+140h] [ebp-98h] BYREF
  char v54; // [esp+159h] [ebp-7Fh]
  float v55; // [esp+15Ch] [ebp-7Ch]
  float v56; // [esp+160h] [ebp-78h]
  char v57; // [esp+16Ch] [ebp-6Ch]
  char v58; // [esp+16Dh] [ebp-6Bh]
  char v59; // [esp+16Eh] [ebp-6Ah]
  char v60; // [esp+16Fh] [ebp-69h]
  float v61[6]; // [esp+170h] [ebp-68h] BYREF
  char v62; // [esp+189h] [ebp-4Fh]
  float v63; // [esp+18Ch] [ebp-4Ch]
  float v64; // [esp+190h] [ebp-48h]
  char v65; // [esp+19Ch] [ebp-3Ch]
  char v66; // [esp+19Dh] [ebp-3Bh]
  char v67; // [esp+19Eh] [ebp-3Ah]
  char v68; // [esp+19Fh] [ebp-39h]
  float v69[6]; // [esp+1A0h] [ebp-38h] BYREF
  char v70; // [esp+1B9h] [ebp-1Fh]
  float v71; // [esp+1BCh] [ebp-1Ch]
  float v72; // [esp+1C0h] [ebp-18h]
  char v73; // [esp+1CCh] [ebp-Ch]
  char v74; // [esp+1CDh] [ebp-Bh]
  char v75; // [esp+1CEh] [ebp-Ah]
  char v76; // [esp+1CFh] [ebp-9h]
  float v77; // [esp+1D4h] [ebp-4h]

  rf_vector_prefix_construct_noop(source);
  rf_vector_prefix_construct_noop(v36);
  rf_renderer_transform_world_point_backend_wrapper((int)source, (float *)a1);
  rf_renderer_project_clip_vertex_backend_wrapper((int)source);
  if ( (v25 & 2) != 0 )
    return 0.0;
  rf_renderer_transform_world_point_backend_wrapper((int)v36, (float *)a3);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v36);
  if ( (v39 & 2) != 0 )
    return 0.0;
  if ( (v38 & v24) != 0 )
    return 0.0;
  v28 = source[3];
  v20 = source[4];
  v41 = rf_renderer_project_world_width_to_pixels((int)source, &a2);
  v30 = v36[3];
  v35 = v36[4];
  v42 = rf_renderer_project_world_width_to_pixels((int)v36, &a4);
  v14 = (v30 - v28) * (v30 - v28) + (v35 - v20) * (v35 - v20);
  v26 = rf_sqrt_float(v14);
  if ( a6 > 1.0 && a6 < (double)v26 )
  {
    v19 = a6 / v26;
    v30 = (v30 - v28) * v19 + v28;
    v35 = (v35 - v20) * v19 + v20;
    v42 = (v42 - v41) * v19 + v41;
    v13 = (v30 - v28) * (v30 - v28) + (v35 - v20) * (v35 - v20);
    v26 = rf_sqrt_float(v13);
  }
  v12 = rf_renderer_vertex_scaled_camera_depth((int)source);
  v21 = (rf_renderer_vertex_scaled_camera_depth((int)v36) + v12) * 0.5;
  v27 = v41;
  if ( v41 < (double)v42 )
    v27 = v42;
  if ( v27 < 1.0 )
    v27 = 1.0;
  if ( v27 <= (double)v26 )
  {
    v8 = v30 - v28;
    v7 = v35 - v20;
    v43 = rf_atan_ratio_with_negative_x_pi_adjustment(v7, v8);
    v77 = v26;
    v40 = v41;
    v44 = v42;
  }
  else
  {
    v40 = v27 - v26 + v41;
    if ( v27 < (double)v40 )
      v40 = v27;
    v44 = v27 - v26 + v42;
    if ( v27 < (double)v44 )
      v44 = v27;
    v26 = v27;
    v11 = fabs(v30 - v28);
    if ( v11 <= 0.009999999776482582 )
    {
      v43 = 0.0;
    }
    else
    {
      Y = v30 - v28;
      X = v35 - v20;
      v43 = atan2f(X, Y);
    }
    v77 = v26;
  }
  v31 = (v30 + v28) / 2.0;
  v32 = (v35 + v20) / 2.0;
  if ( v40 < 1.0 )
    v40 = 1.0;
  if ( v44 < 1.0 )
    v44 = 1.0;
  rf_vector_construct_no_unwind((char *)destination, 0x30u, 4, rf_vector_prefix_construct_noop);
  v33[0] = v69;
  v33[1] = v61;
  v33[2] = v53;
  v33[3] = destination;
  v34 = rf_sin_float(v43);
  v29 = rf_cos_float(v43);
  if ( v21 < 0.0 )
    v21 = 0.0;
  destination[3] = -v77 / 2.0 * v29 + -v40 / 2.0 * v34 + v31;
  destination[4] = -v77 / 2.0 * v34 - -v40 / 2.0 * v29 + v32;
  rf_vector_copy(destination, copy_result, source);
  destination[5] = v23;
  v47 = 0.0;
  v48 = 0.0;
  v49 = -1;
  v50 = -1;
  v51 = -1;
  v52 = -1;
  v46 = 1;
  v53[3] = v77 / 2.0 * v29 + -v44 / 2.0 * v34 + v31;
  v53[4] = v77 / 2.0 * v34 - -v44 / 2.0 * v29 + v32;
  rf_vector_copy(v53, v17, v36);
  v53[5] = v37;
  v55 = 1.0;
  v56 = 0.0;
  v57 = -1;
  v58 = -1;
  v59 = -1;
  v60 = -1;
  v54 = 1;
  v61[3] = v77 / 2.0 * v29 + v44 / 2.0 * v34 + v31;
  v61[4] = v77 / 2.0 * v34 - v44 / 2.0 * v29 + v32;
  rf_vector_copy(v61, v16, v36);
  v61[5] = v37;
  v63 = 1.0;
  v64 = 1.0;
  v65 = -1;
  v66 = -1;
  v67 = -1;
  v68 = -1;
  v62 = 1;
  v69[3] = -v77 / 2.0 * v29 + v40 / 2.0 * v34 + v31;
  v69[4] = -v77 / 2.0 * v34 - v40 / 2.0 * v29 + v32;
  rf_vector_copy(v69, v15, source);
  v69[5] = v23;
  v71 = 0.0;
  v72 = 1.0;
  v73 = -1;
  v74 = -1;
  v75 = -1;
  v76 = -1;
  v70 = 1;
  rf_renderer_draw_preprojected_polygon_backend_wrapper(4, v33, 0xDu, a5);
  return v21;
}

