// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2610 rf_motion_sample_buffer_insert_and_extend_curve
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer plus EIGHT stackargs(entity,positionVector,EulerVector,offsetVector,velocityVector,inputVector,timestampWORD,floatParameter),RET32,SEH frame. Records arrival delta from scaled clock(1000),using0 when old1336<0;calls clock AGAIN tostore1336. Duplicate incoming timestamp equal last when count>0 increments player-net DWORD536 but STILL inserts (no dedup/rejection). Normal count<20 appends five12-byte vectors at arrays0/240/480/720/960,arrivalDWORD1340,timeWORD1280,floatParameter1200 then incrementscount. Count>=20 shifts exactly19 entries in allfive arrays/arrival/time/parameter and writes index19 WITHOUT correctingcount;corrupt count>20 remains>20. Signed sum
// arrival[0..count-1]/count storedF32 mean1420,no count0/negative guard. For count>=2,uses asymmetric65535/5000 time difference D(incoming,cursor) from3570. If ORDERED mean1420*globalF32 662D50+globalF32 7B4DD4<D OR flag1320 bit1 set,sets WORD cursor=incoming-int(mean*gain+lag),clearsbit1,setsbit2,and increments player-net DWORD540 if resolved. ORDERED distance(entityCOMMON60,incomingPosition)>=2.5 also setsbit2. With count>=2,constructs21 no-op vector locals and local physics-state wrapper;copies count stored positions to local points. Snapshots entity bounds400/412,matrices156/192,positions228/240,ONLY predictedmatrix288 into local P116,velocities324/336/348,force360/torque372,flags424/428,time432,and full68-bytecontact436. Then temporarily current228=lastsamplePosition,velocity324=lastsampleVelocity,time432=mean*float0.001,clears physics424 bit0x8000;for entitytype copies last input
// array960 into1812 WITHOUT saving old1812. Executes physics work batch containingentity with mode0,appends resulting predicted240 as local point[count],then restores explicit snapshots. NATIVE RESTORE MISMATCH: copies currentmatrix252 from local P152 at EBP-0x1104,whose constructor is no-op and whose nine floats were never populated;the saved predicted288 at local P116 is NOT copied back. Thus current252 receives unwritten local matrix storage and predicted288 remains delegate-modified. Does NOT restore common72/position60,view/Euler fields1812/2016/2148+ or arbitrary physics-step/global side effects. Restores fullcontact436 and enumerated force/flags/time fields,then rebuilds curve1424 with count+1 points including extrapolated endpoint;destroys local collection helpers. This is NOT a complete rollback or side-effect-free prediction. No own pointer/capacity/finite/negative
// count/denominator protection;sample append/counters precede speculative physics and persist.
void __thiscall rf_motion_sample_buffer_insert_and_extend_curve(
        int this,
        int a2,
        float *rhs,
        float *source,
        float *a5,
        float *a6,
        float *a7,
        __int16 a8,
        float a9)
{
  float *v9; // eax
  float v11[3]; // [esp+Ch] [ebp-1474h] BYREF
  float v12[3]; // [esp+18h] [ebp-1468h] BYREF
  float v13[3]; // [esp+24h] [ebp-145Ch] BYREF
  float v14[3]; // [esp+30h] [ebp-1450h] BYREF
  float v15[3]; // [esp+3Ch] [ebp-1444h] BYREF
  float v16[3]; // [esp+48h] [ebp-1438h] BYREF
  float v17[3]; // [esp+54h] [ebp-142Ch] BYREF
  float v18[3]; // [esp+60h] [ebp-1420h] BYREF
  float v19[3]; // [esp+6Ch] [ebp-1414h] BYREF
  float v20[3]; // [esp+78h] [ebp-1408h] BYREF
  float v21[3]; // [esp+84h] [ebp-13FCh] BYREF
  float v22[3]; // [esp+90h] [ebp-13F0h] BYREF
  float v23[3]; // [esp+9Ch] [ebp-13E4h] BYREF
  float v24[3]; // [esp+A8h] [ebp-13D8h] BYREF
  float v25[3]; // [esp+B4h] [ebp-13CCh] BYREF
  float v26[3]; // [esp+C0h] [ebp-13C0h] BYREF
  float v27[3]; // [esp+CCh] [ebp-13B4h] BYREF
  float v28[3]; // [esp+D8h] [ebp-13A8h] BYREF
  float v29[3]; // [esp+E4h] [ebp-139Ch] BYREF
  float v30[3]; // [esp+F0h] [ebp-1390h] BYREF
  float v31[3]; // [esp+FCh] [ebp-1384h] BYREF
  float v32[3]; // [esp+108h] [ebp-1378h] BYREF
  float v33[3]; // [esp+114h] [ebp-136Ch] BYREF
  float out_vector[3]; // [esp+120h] [ebp-1360h] BYREF
  float v35[3]; // [esp+12Ch] [ebp-1354h] BYREF
  float v36[3]; // [esp+138h] [ebp-1348h] BYREF
  float v37[3]; // [esp+144h] [ebp-133Ch] BYREF
  float v38[3]; // [esp+150h] [ebp-1330h] BYREF
  float v39[3]; // [esp+15Ch] [ebp-1324h] BYREF
  float v40[3]; // [esp+168h] [ebp-1318h] BYREF
  float v41[3]; // [esp+174h] [ebp-130Ch] BYREF
  float v42[3]; // [esp+180h] [ebp-1300h] BYREF
  float v43[3]; // [esp+18Ch] [ebp-12F4h] BYREF
  float v44[3]; // [esp+198h] [ebp-12E8h] BYREF
  float v45[3]; // [esp+1A4h] [ebp-12DCh] BYREF
  float v46[3]; // [esp+1B0h] [ebp-12D0h] BYREF
  float v47[3]; // [esp+1BCh] [ebp-12C4h] BYREF
  float v48[3]; // [esp+1C8h] [ebp-12B8h] BYREF
  float copy_result[4]; // [esp+1D4h] [ebp-12ACh] BYREF
  float destination[64]; // [esp+1E4h] [ebp-129Ch] BYREF
  void *v51[5]; // [esp+2E4h] [ebp-119Ch] BYREF
  float v52[9]; // [esp+2F8h] [ebp-1188h] BYREF
  float v53[9]; // [esp+31Ch] [ebp-1164h] BYREF
  float v54[3]; // [esp+340h] [ebp-1140h] BYREF
  float v55[3]; // [esp+34Ch] [ebp-1134h] BYREF
  float v56[9]; // [esp+358h] [ebp-1128h] BYREF
  float v57[9]; // [esp+37Ch] [ebp-1104h] BYREF
  float v58[3]; // [esp+3A0h] [ebp-10E0h] BYREF
  float v59[3]; // [esp+3ACh] [ebp-10D4h] BYREF
  float v60[3]; // [esp+3B8h] [ebp-10C8h] BYREF
  float v61[3]; // [esp+3C4h] [ebp-10BCh] BYREF
  float v62[7]; // [esp+3D0h] [ebp-10B0h] BYREF
  float v63[3]; // [esp+3ECh] [ebp-1094h] BYREF
  float v64[3]; // [esp+3F8h] [ebp-1088h] BYREF
  int v65; // [esp+404h] [ebp-107Ch]
  int v66; // [esp+408h] [ebp-1078h]
  float v67; // [esp+40Ch] [ebp-1074h]
  float v68[17]; // [esp+410h] [ebp-1070h] BYREF
  _DWORD v69[1026]; // [esp+454h] [ebp-102Ch] BYREF
  _DWORD *v70; // [esp+145Ch] [ebp-24h]
  int v71; // [esp+1460h] [ebp-20h]
  _DWORD *v72; // [esp+1464h] [ebp-1Ch]
  int v73; // [esp+1468h] [ebp-18h]
  int i; // [esp+146Ch] [ebp-14h]
  int v75; // [esp+1470h] [ebp-10h]
  int v76; // [esp+147Ch] [ebp-4h]

  v73 = 0;
  if ( *(int *)(this + 1336) >= 0 )
    v73 = rf_performance_clock_elapsed_scaled(1000) - *(_DWORD *)(this + 1336);
  *(_DWORD *)(this + 1336) = rf_performance_clock_elapsed_scaled(1000);
  if ( *(int *)(this + 1332) > 0
    && *(unsigned __int16 *)(this + 2 * *(_DWORD *)(this + 1332) + 1278) == (unsigned __int16)a8 )
  {
    v72 = sub_4DD720(*(_DWORD *)(a2 + 44));
    if ( v72 )
    {
      if ( v72[1152] )
        ++*(_DWORD *)(v72[1152] + 536);
    }
  }
  if ( *(int *)(this + 1332) >= 20 )
  {
    for ( i = 0; i < 19; ++i )
    {
      rf_vector_copy((float *)(this + 12 * i), v44, (const float *)(this + 12 * (i + 1)));
      rf_vector_copy((float *)(this + 12 * i + 240), v43, (const float *)(this + 12 * (i + 1) + 240));
      rf_vector_copy((float *)(this + 12 * i + 480), v42, (const float *)(this + 12 * (i + 1) + 480));
      rf_vector_copy((float *)(this + 12 * i + 720), v41, (const float *)(this + 12 * (i + 1) + 720));
      rf_vector_copy((float *)(this + 12 * i + 960), v40, (const float *)(this + 12 * (i + 1) + 960));
      *(_DWORD *)(this + 4 * i + 1340) = *(_DWORD *)(this + 4 * i + 1344);
      *(_WORD *)(this + 2 * i + 1280) = *(_WORD *)(this + 2 * i + 1282);
      *(float *)(this + 4 * i + 1200) = *(float *)(this + 4 * i + 1204);
    }
    rf_vector_copy((float *)(this + 228), v39, rhs);
    rf_vector_copy((float *)(this + 468), v38, source);
    rf_vector_copy((float *)(this + 708), v37, a5);
    rf_vector_copy((float *)(this + 948), v36, a6);
    rf_vector_copy((float *)(this + 1188), v35, a7);
    *(_DWORD *)(this + 1416) = v73;
    *(_WORD *)(this + 1318) = a8;
    *(float *)(this + 1276) = a9;
  }
  else
  {
    rf_vector_copy((float *)(this + 12 * *(_DWORD *)(this + 1332)), copy_result, rhs);
    rf_vector_copy((float *)(this + 12 * *(_DWORD *)(this + 1332) + 240), v48, source);
    rf_vector_copy((float *)(this + 12 * *(_DWORD *)(this + 1332) + 480), v47, a5);
    rf_vector_copy((float *)(this + 12 * *(_DWORD *)(this + 1332) + 720), v46, a6);
    rf_vector_copy((float *)(this + 12 * *(_DWORD *)(this + 1332) + 960), v45, a7);
    *(_DWORD *)(this + 4 * *(_DWORD *)(this + 1332) + 1340) = v73;
    *(_WORD *)(this + 2 * *(_DWORD *)(this + 1332) + 1280) = a8;
    *(float *)(this + 4 * (*(_DWORD *)(this + 1332))++ + 1200) = a9;
  }
  v75 = 0;
  for ( i = 0; i < *(_DWORD *)(this + 1332); ++i )
    v75 += *(_DWORD *)(this + 4 * i + 1340);
  *(float *)(this + 1420) = (double)v75 / (double)*(int *)(this + 1332);
  if ( *(int *)(this + 1332) >= 2 )
  {
    if ( 0xFFFF - (unsigned __int16)a8 >= 5000 || *(unsigned __int16 *)(this + 1324) >= 0x1388u )
    {
      if ( 0xFFFF - *(unsigned __int16 *)(this + 1324) >= 5000 || (unsigned __int16)a8 >= 0x1388u )
        v71 = (unsigned __int16)a8 - *(unsigned __int16 *)(this + 1324);
      else
        v71 = (unsigned __int16)a8 + 0xFFFF - *(unsigned __int16 *)(this + 1324);
    }
    else
    {
      v71 = *(unsigned __int16 *)(this + 1324) + (unsigned __int16)a8 - 0xFFFF;
    }
    if ( *(float *)(this + 1420) * flt_662D50 + unk_7B4DD4 < (double)v71 || (*(_DWORD *)(this + 1320) & 1) != 0 )
    {
      *(_WORD *)(this + 1324) = a8 - (int)(*(float *)(this + 1420) * flt_662D50 + unk_7B4DD4);
      *(_DWORD *)(this + 1320) &= ~1u;
      *(_DWORD *)(this + 1320) |= 2u;
      v70 = sub_4DD720(*(_DWORD *)(a2 + 44));
      if ( v70 )
      {
        if ( v70[1152] )
          ++*(_DWORD *)(v70[1152] + 540);
      }
    }
    v9 = rf_vector_subtract((const float *)(a2 + 60), out_vector, rhs);
    if ( rf_vector3_length(v9) >= 2.5 )
      *(_DWORD *)(this + 1320) |= 2u;
  }
  if ( *(int *)(this + 1332) >= 2 )
  {
    rf_vector_construct_no_unwind((char *)destination, 0xCu, 21, rf_vector3_default_construct_noop);
    rf_embedded_array_construct_count_only_51ebe0(v69);
    v76 = 0;
    rf_physics_state_construct_empty_sphere_collection((char *)v51);
    LOBYTE(v76) = 1;
    for ( i = 0; i < *(_DWORD *)(this + 1332); ++i )
      rf_vector_copy(&destination[3 * i], v33, (const float *)(this + 12 * i));
    rf_vector_copy(v63, v32, (const float *)(a2 + 400));
    rf_vector_copy(v64, v31, (const float *)(a2 + 412));
    rf_matrix3_copy(v52, (const float *)(a2 + 156));
    rf_matrix3_copy(v53, (const float *)(a2 + 192));
    rf_vector_copy(v54, v30, (const float *)(a2 + 228));
    rf_vector_copy(v55, v29, (const float *)(a2 + 240));
    rf_matrix3_copy(v56, (const float *)(a2 + 288));
    rf_vector_copy(v58, v28, (const float *)(a2 + 324));
    rf_vector_copy(v59, v27, (const float *)(a2 + 336));
    rf_vector_copy(v60, v26, (const float *)(a2 + 348));
    rf_vector_copy(v61, v25, (const float *)(a2 + 360));
    rf_vector_copy(v62, v24, (const float *)(a2 + 372));
    v65 = *(_DWORD *)(a2 + 424);
    v66 = *(_DWORD *)(a2 + 428);
    v67 = *(float *)(a2 + 432);
    rf_physics_hit_record68_copy_fields(v68, (float *)(a2 + 436));
    rf_vector_copy((float *)(a2 + 228), v23, (const float *)(this + 12 * (*(_DWORD *)(this + 1332) - 1)));
    rf_vector_copy((float *)(a2 + 324), v22, (const float *)(this + 12 * (*(_DWORD *)(this + 1332) - 1) + 720));
    *(float *)(a2 + 432) = *(float *)(this + 1420) * 0.001000000047497451;
    *(_DWORD *)(a2 + 424) &= ~0x8000u;
    if ( rf_object_is_entity(a2) )
    {
      LODWORD(copy_result[3]) = a2;
      rf_vector_copy((float *)(a2 + 1812), v21, (const float *)(this + 12 * (*(_DWORD *)(this + 1332) - 1) + 960));
    }
    rf_pointer_array_clear_count_keep_storage(v69);
    rf_physics_work_batch_append(v69, a2);
    rf_physics_work_batch_execute((int)v69, 0);
    rf_vector_copy(&destination[3 * *(_DWORD *)(this + 1332)], v20, (const float *)(a2 + 240));
    rf_vector_copy((float *)(a2 + 400), v19, v63);
    rf_vector_copy((float *)(a2 + 412), v18, v64);
    rf_matrix3_copy((float *)(a2 + 156), v52);
    rf_matrix3_copy((float *)(a2 + 192), v53);
    rf_vector_copy((float *)(a2 + 228), v17, v54);
    rf_vector_copy((float *)(a2 + 240), v16, v55);
    rf_matrix3_copy((float *)(a2 + 252), v57);
    rf_vector_copy((float *)(a2 + 324), v15, v58);
    rf_vector_copy((float *)(a2 + 336), v14, v59);
    rf_vector_copy((float *)(a2 + 348), v13, v60);
    rf_vector_copy((float *)(a2 + 360), v12, v61);
    rf_vector_copy((float *)(a2 + 372), v11, v62);
    *(_DWORD *)(a2 + 424) = v65;
    *(_DWORD *)(a2 + 428) = v66;
    *(float *)(a2 + 432) = v67;
    rf_physics_hit_record68_copy_fields((float *)(a2 + 436), v68);
    rf_catmull_rom32_set_points_with_end_padding(this + 1424, *(_DWORD *)(this + 1332) + 1, (int)destination);
    LOBYTE(v76) = 0;
    rf_common_embedded_destroy_pointer_array(v51);
    v76 = -1;
    rf_shared_noop_destructor_4580d0();
  }
}

