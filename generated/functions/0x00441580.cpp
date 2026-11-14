// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441580 rf_player_build_control_vectors_from_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Five cdecl slots(player pointer,input-state pointer,output pointer,LOWBYTE flagA,LOWBYTE flagB). NULL output
// returns untouched incoming EAX with no queries/stores; otherwise final EAX is output POINTER, not bool. No input/player NULL, size/alias/finite/zero-divisor guard. All described
// memory float stores round to F32; expressions between stores retain native x87 evaluation. Let Q(k)=451DB0(input,k), a potentially consuming input query, not a cached pure value.
// Exact order: Q14 thenQ13, store output12=F32(first-second); Q15 thenQ16 tooutput16; Q11 thenQ12 tooutput20. The first of each pair is spilled F64 before second call. If flagA
// ANYnonzero, queryQ3 and overwrite16=F32(Q3+current16). If flagB ANYnonzero, queryQ4 and overwrite16=F32(current16-Q4). NextQ18 thenQ17 toF32 local u, thenQ20 thenQ19 toF32 local v,
// again first-result F64 spills. Q's own native helper includes451F70, press/time/click queries and per-add F32 accumulation; do not combine or reorder these calls.  Update shared
// Gx=FLOAT6E6AB8 toF32(u/DOUBLE8+oldGx), thenGy=FLOAT6E6AB4 toF32(v/8+oldGy). Clamp Gx thenGy to[-1,1] using40D620, which leaves NaN unchanged. Then reset Gx to+0 iff ORDERED u==0 OR
// ORDERED u*Gx<0; same Gy/v. Unordered comparisons do not reset. Store output0=F32(Gx/DOUBLE2),output4=Gy,output8=+0. Seed local dx,dy,dz and extra-output12-addend to+0.
// Call452220(input,&fourDWORDlocal) once; consume its first two DWORDs as signed mouse deltas X,Y. Helper also writes input+8 and builds four mapped/inverted deltas; no reread/cached
// substitute.  If output BYTE24==EXACT1, M=F32(inputFLOAT0*DOUBLE0.009999999776482582). Query4EAE70(player) once. Only FIRST result ORDERED>1 causes a SECOND zoom query;
// factor=F32((secondResult-DOUBLE1)/DOUBLE11*DOUBLE30). Only factor ORDERED>1 divides M byfactor and storesF32. That branch never applies the quarter-speed fallback, even if second
// result/factor is NaN or<=1. If FIRST result<=1 OR UNORDERED, player BYTE4016==EXACT1 scales M byDOUBLE0.25 toF32. Zoom query is stateful (can reset alternate-zoom state), so two
// calls cannot be folded.  In this BYTE24==1 branch, shared BYTE6E6AB0 ANYnonzero selects nonlinear curve. Convert signed X toF32 x, then signed Y toF32 y separately. Let T be
// current FLOAT661578 (original PE initializer10.0f; reloaded by native tests/arithmetic), H=T/DOUBLE2. For each axis use the SAME F32 stack local f, uninitialized before X: ordered
// x<H AND ordered x>=0 assigns f=F32(x*x/T); else ordered x<0 AND ordered x>-H assigns f=F32(-(x*x/T)); else ordered x>=H assigns f=F32(x-T/DOUBLE4); else ordered x<=-H assigns
// f=F32(x-T/DOUBLE4); otherwise f is LEFT UNCHANGED. Both outer branches subtract T/4, including NEGATIVE outer values: preserve that asymmetry. Store output28=F32(fX*M), then run
// same curve forY reusing f and store output32=F32((-fY)*M), FCHS before multiplication. With finite positiveT, quadratic intervals are[0,T/2) and(-T/2,0), boundaries are outer.
// There is no T positivity/finite check: NaNT makes all assignments fail, so X reads uninitialized f and Y reuses that same value; do not substitute a zero/default curve. If
// BYTE6E6AB0==0 instead, output28=F32(exact signedX*M); output32=F32(signed32_wrap_NEG(Y)*M). Linear Y negation is integer32, so INT_MIN remains negative; nonlinear path first rounds
// signedY toF32 and uses floating FCHS. In either BYTE24==1 subcase the local dx/dy/dz remain+0.  If output BYTE24!=1, first output28=output32=+0.
// M=F32(inputFLOAT0*DOUBLE100/frameFLOATseconds663EC8), without a zero/NaN guard. Then dx=F32(exact signedX*M+initial+0),dy=F32(initial+0-exact signedY*M),dz remains+0; this
// subtraction does NOT use integer NEG. Common suffix for both modes: divide dx,dy,dz each byDOUBLE65536 with separate F32 stores, then dy byDOUBLE2 with another F32 store; clamp
// dx,dy,dz in that order to[-1,1], retaining NaNs. Sequentially store output0=F32(current0+dy),output4=F32(current4+dx),output8=F32(current8+dz),output12=F32(current12+local+0). The
// last add/store really occurs (NaN/zero semantics), with no final combined-vector clamp. BYTE24 is read but never initialized here. Output/input/shared-global aliases are not
// protected: native query/store order and partial mutations are observable; no rollback.
int __cdecl rf_player_build_control_vectors_from_input(int a1, float *a2, int a3, char a4, char a5)
{
  int result; // eax
  double v6; // [esp+Ch] [ebp-60h]
  double v7; // [esp+14h] [ebp-58h]
  double v8; // [esp+1Ch] [ebp-50h]
  double v9; // [esp+24h] [ebp-48h]
  double v10; // [esp+2Ch] [ebp-40h]
  float v11; // [esp+34h] [ebp-38h]
  float v12; // [esp+38h] [ebp-34h]
  float v13; // [esp+38h] [ebp-34h]
  float v14; // [esp+3Ch] [ebp-30h]
  int v15; // [esp+44h] [ebp-28h] BYREF
  float v16; // [esp+48h] [ebp-24h]
  int v17; // [esp+4Ch] [ebp-20h] BYREF
  int v18; // [esp+50h] [ebp-1Ch] BYREF
  float v19; // [esp+54h] [ebp-18h]
  float v20; // [esp+58h] [ebp-14h]
  int v21; // [esp+5Ch] [ebp-10h] BYREF
  int v22; // [esp+60h] [ebp-Ch]

  if ( a3 )
  {
    v10 = rf_input_binding_active_time_sum_clamped((int)a2, 14);
    *(float *)(a3 + 12) = v10 - rf_input_binding_active_time_sum_clamped((int)a2, 13);
    v9 = rf_input_binding_active_time_sum_clamped((int)a2, 15);
    *(float *)(a3 + 16) = v9 - rf_input_binding_active_time_sum_clamped((int)a2, 16);
    v8 = rf_input_binding_active_time_sum_clamped((int)a2, 11);
    *(float *)(a3 + 20) = v8 - rf_input_binding_active_time_sum_clamped((int)a2, 12);
    if ( a4 )
      *(float *)(a3 + 16) = rf_input_binding_active_time_sum_clamped((int)a2, 3) + *(float *)(a3 + 16);
    if ( a5 )
      *(float *)(a3 + 16) = *(float *)(a3 + 16) - rf_input_binding_active_time_sum_clamped((int)a2, 4);
    v7 = rf_input_binding_active_time_sum_clamped((int)a2, 18);
    v19 = v7 - rf_input_binding_active_time_sum_clamped((int)a2, 17);
    v6 = rf_input_binding_active_time_sum_clamped((int)a2, 20);
    v20 = v6 - rf_input_binding_active_time_sum_clamped((int)a2, 19);
    flt_6E6AB8 = v19 / 8.0 + flt_6E6AB8;
    flt_6E6AB4 = v20 / 8.0 + flt_6E6AB4;
    rf_float_clamp_in_place(&flt_6E6AB8, -1.0, 1.0);
    rf_float_clamp_in_place(&flt_6E6AB4, -1.0, 1.0);
    if ( v19 == 0.0 || v19 * flt_6E6AB8 < 0.0 )
      flt_6E6AB8 = 0.0;
    if ( v20 == 0.0 || v20 * flt_6E6AB4 < 0.0 )
      flt_6E6AB4 = 0.0;
    *(float *)a3 = flt_6E6AB8 / 2.0;
    *(float *)(a3 + 4) = flt_6E6AB4;
    *(float *)(a3 + 8) = 0.0;
    *(float *)&v15 = 0.0;
    *(float *)&v17 = 0.0;
    *(float *)&v18 = 0.0;
    rf_input_binding_map_relative_mouse_axes((int)a2, (int)&v21);
    if ( *(_BYTE *)(a3 + 24) == 1 )
    {
      v16 = *a2 * 0.009999999776482582;
      if ( rf_player_query_alt_zoom_factor(a1) <= 1.0 )
      {
        if ( *(_BYTE *)(a1 + 4016) == 1 )
          v16 = v16 * 0.25;
      }
      else
      {
        v14 = (rf_player_query_alt_zoom_factor(a1) - 1.0) / 11.0 * 30.0;
        if ( v14 > 1.0 )
          v16 = v16 / v14;
      }
      if ( unk_6E6AB0 )
      {
        v12 = (float)v21;
        if ( v12 >= flt_661578 / 2.0 || v12 < 0.0 )
        {
          if ( v12 >= 0.0 || v12 <= -flt_661578 / 2.0 )
          {
            if ( v12 < flt_661578 / 2.0 )
            {
              if ( v12 <= -flt_661578 / 2.0 )
                v11 = v12 - flt_661578 / 4.0;
            }
            else
            {
              v11 = v12 - flt_661578 / 4.0;
            }
          }
          else
          {
            v11 = -(v12 * v12 / flt_661578);
          }
        }
        else
        {
          v11 = v12 * v12 / flt_661578;
        }
        *(float *)(a3 + 28) = v11 * v16;
        v13 = (float)v22;
        if ( v13 >= flt_661578 / 2.0 || v13 < 0.0 )
        {
          if ( v13 >= 0.0 || v13 <= -flt_661578 / 2.0 )
          {
            if ( v13 < flt_661578 / 2.0 )
            {
              if ( v13 <= -flt_661578 / 2.0 )
                v11 = v13 - flt_661578 / 4.0;
            }
            else
            {
              v11 = v13 - flt_661578 / 4.0;
            }
          }
          else
          {
            v11 = -(v13 * v13 / flt_661578);
          }
        }
        else
        {
          v11 = v13 * v13 / flt_661578;
        }
        *(float *)(a3 + 32) = -v11 * v16;
      }
      else
      {
        *(float *)(a3 + 28) = (double)v21 * v16;
        *(float *)(a3 + 32) = (double)-v22 * v16;
      }
    }
    else
    {
      *(float *)(a3 + 28) = 0.0;
      *(float *)(a3 + 32) = 0.0;
      v16 = *a2 * 100.0 / rf_frame_delta_seconds;
      *(float *)&v15 = (double)v21 * v16 + *(float *)&v15;
      *(float *)&v17 = *(float *)&v17 - (double)v22 * v16;
    }
    *(float *)&v15 = *(float *)&v15 / 65536.0;
    *(float *)&v17 = *(float *)&v17 / 65536.0;
    *(float *)&v18 = *(float *)&v18 / 65536.0;
    *(float *)&v17 = *(float *)&v17 / 2.0;
    rf_float_clamp_in_place((float *)&v15, -1.0, 1.0);
    rf_float_clamp_in_place((float *)&v17, -1.0, 1.0);
    rf_float_clamp_in_place((float *)&v18, -1.0, 1.0);
    *(float *)a3 = *(float *)a3 + *(float *)&v17;
    *(float *)(a3 + 4) = *(float *)(a3 + 4) + *(float *)&v15;
    *(float *)(a3 + 8) = *(float *)(a3 + 8) + *(float *)&v18;
    *(float *)(a3 + 12) = *(float *)(a3 + 12) + (float)0.0;
    return a3;
  }
  return result;
}

