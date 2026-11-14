// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005844D0 rf_quaternion_s16_squad_to_float_wrapped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered cdecl(floatOut,A16,B16,C16,D16,t). Packed interpolations Q=(A,D,t),R=(B,C,t),S=(Q,R,2*(1-t)*t) through584060;decodes final xyz and nonzero w by exact scale0.00006103888154029846. If packed w==0,stores float w~1e-6 and returnsNULL despite filled output;nonzero-w path returns output. No final normalization,saturation or independent t clamp;inherits wrapped packed interpolation behavior. Inputs s16[4],OUTPUT FLOAT[4],not packed output.
float *__cdecl rf_quaternion_s16_squad_to_float_wrapped(
        float *a1,
        const __int16 *a2,
        const __int16 *a3,
        const __int16 *a4,
        const __int16 *a5,
        float a6)
{
  float *result; // eax
  float v7; // [esp+4h] [ebp-3Ch]
  float v8; // [esp+Ch] [ebp-34h]
  float v9; // [esp+14h] [ebp-2Ch]
  float v10; // [esp+1Ch] [ebp-24h]
  float v11; // [esp+24h] [ebp-1Ch]
  __int16 v12[4]; // [esp+28h] [ebp-18h] BYREF
  __int16 v13[4]; // [esp+30h] [ebp-10h] BYREF
  __int16 v14[3]; // [esp+38h] [ebp-8h] BYREF
  __int16 v15; // [esp+3Eh] [ebp-2h]

  rf_short_quaternion_construct_0001(v12);
  rf_short_quaternion_construct_0001(v13);
  rf_short_quaternion_construct_0001(v14);
  rf_short_quaternion_interpolate_wrapped(v12, (__int16 *)a2, a5, a6);
  rf_short_quaternion_interpolate_wrapped(v13, (__int16 *)a3, a4, a6);
  v11 = (1.0 - a6) * 2.0 * a6;
  rf_short_quaternion_interpolate_wrapped(v14, v12, v13, v11);
  v10 = (double)v14[0] * 0.00006103888154029846;
  *a1 = v10;
  v9 = (double)v14[1] * 0.00006103888154029846;
  a1[1] = v9;
  v8 = (double)v14[2] * 0.00006103888154029846;
  a1[2] = v8;
  result = (float *)v15;
  if ( v15 )
  {
    v7 = (double)v15 * 0.00006103888154029846;
    a1[3] = v7;
    return a1;
  }
  else
  {
    a1[3] = 0.000001;
  }
  return result;
}

