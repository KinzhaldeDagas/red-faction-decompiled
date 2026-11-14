// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4210 rf_entity_apply_buffered_orientation_sample
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity. If buffer632NULL,returns entity pointer bits with no entity-field writes. Otherwise copies shared vector17F10B0 into angular336 through local scratch;passes low16-bit sample time buffer1324 to stdcall4B3D70(entity,time,outMatrix,outEuler,outOffset). Child writes all outputs through current-state/interpolated/last-sample fallbacks;helper return ignored. Stores Euler2148,offset2172,current matrix252;zeroes1828/1832,input1800,delta2160/2184;copies current252 to predicted288 andcommon72;clears torque372. Does NOT rebuild rotated tensorP56,advance time432 or copy position. Constructors of local vectors/matrix do not zero them;output validity comes from child writes. No interpolation-success boolean
// is returned;final helper EAX bits on processed path.
float *__cdecl rf_entity_apply_buffered_orientation_sample(int a1)
{
  float *result; // eax
  float v2[3]; // [esp+0h] [ebp-78h] BYREF
  float v3[3]; // [esp+Ch] [ebp-6Ch] BYREF
  float v4[3]; // [esp+18h] [ebp-60h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-54h] BYREF
  float destination[3]; // [esp+30h] [ebp-48h] BYREF
  float source[3]; // [esp+3Ch] [ebp-3Ch] BYREF
  float v8[3]; // [esp+48h] [ebp-30h] BYREF
  float v9[9]; // [esp+54h] [ebp-24h] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(source);
  rf_vector3_default_construct_noop(v8);
  rf_matrix3_construct((char *)v9);
  result = (float *)a1;
  if ( *(_DWORD *)(a1 + 632) )
  {
    rf_vector_copy(destination, copy_result, flt_17F10B0);
    rf_entity_sample_buffered_euler_and_offset(a1, *(_WORD *)(*(_DWORD *)(a1 + 632) + 1324), v9, source, v8);
    rf_vector_copy((float *)(a1 + 336), v4, destination);
    rf_vector_copy((float *)(a1 + 2148), v3, source);
    rf_vector_copy((float *)(a1 + 2172), v2, v8);
    rf_matrix3_copy((float *)(a1 + 252), v9);
    *(float *)(a1 + 1828) = 0.0;
    *(float *)(a1 + 1832) = 0.0;
    rf_vector3_zero_return_destination((float *)(a1 + 1800));
    rf_vector3_zero_return_destination((float *)(a1 + 2160));
    rf_vector3_zero_return_destination((float *)(a1 + 2184));
    rf_matrix3_copy((float *)(a1 + 288), (const float *)(a1 + 252));
    rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
    return rf_vector3_zero_return_destination((float *)(a1 + 372));
  }
  return result;
}

