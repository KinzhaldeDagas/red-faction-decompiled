// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582AC0 rf_quaternion_s16_hamilton_product_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Signed16 A inECX,output and signed16 B on stack. Decodes all8 components via exact literal0.00006103888154029846 into float locals,computes Hamilton A*B using cross and scalar dot,then multiplies components by16383.0,truncates via integer conversion and stores low16bits. No saturation,normalization,w reconstruction or unit-input guard. Uses local result so output can alias inputs. Returns output.
_WORD *__thiscall rf_quaternion_s16_hamilton_product_to_destination(__int16 *this, _WORD *a2, __int16 *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *scalar; // [esp+8h] [ebp-BCh]
  double v7; // [esp+14h] [ebp-B0h]
  float v8; // [esp+1Ch] [ebp-A8h]
  float v9; // [esp+24h] [ebp-A0h]
  float v10; // [esp+2Ch] [ebp-98h]
  float v11; // [esp+34h] [ebp-90h]
  float v12; // [esp+3Ch] [ebp-88h]
  float v13; // [esp+44h] [ebp-80h]
  float v14; // [esp+4Ch] [ebp-78h]
  float v15; // [esp+54h] [ebp-70h]
  float sum_result[3]; // [esp+60h] [ebp-64h] BYREF
  float scaled_result[3]; // [esp+6Ch] [ebp-58h] BYREF
  float v19[3]; // [esp+78h] [ebp-4Ch] BYREF
  _WORD v20[4]; // [esp+84h] [ebp-40h] BYREF
  float v21; // [esp+8Ch] [ebp-38h]
  float v22; // [esp+90h] [ebp-34h]
  float v23[3]; // [esp+94h] [ebp-30h] BYREF
  float vector[3]; // [esp+A0h] [ebp-24h] BYREF
  float rhs[3]; // [esp+ACh] [ebp-18h] BYREF
  float v26[3]; // [esp+B8h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(v23);
  v15 = (double)*this * 0.00006103888154029846;
  vector[0] = v15;
  v14 = (double)*(this + 1) * 0.00006103888154029846;
  vector[1] = v14;
  v13 = (double)*(this + 2) * 0.00006103888154029846;
  vector[2] = v13;
  v12 = (double)*a3 * 0.00006103888154029846;
  v23[0] = v12;
  v11 = (double)a3[1] * 0.00006103888154029846;
  v23[1] = v11;
  v10 = (double)a3[2] * 0.00006103888154029846;
  v23[2] = v10;
  v9 = (double)*(this + 3) * 0.00006103888154029846;
  v21 = v9;
  v8 = (double)a3[3] * 0.00006103888154029846;
  v22 = v8;
  rf_vector_cross(vector, rhs, v23);
  scalar = rf_vector_multiply_scalar(vector, scaled_result, v8);
  v3 = rf_vector_multiply_scalar(v23, v19, v21);
  v4 = rf_vector_add(v3, sum_result, scalar);
  rf_vector_add(v4, v26, rhs);
  rf_short_quaternion_construct_0001(v20);
  v7 = v21 * v22;
  v20[3] = (int)((v7 - rf_vector_dot(vector, v23)) * 16383.0);
  v20[0] = (int)(v26[0] * 16383.0);
  v20[1] = (int)(v26[1] * 16383.0);
  v20[2] = (int)(v26[2] * 16383.0);
  rf_short_quaternion_assign_words_return_this(a2, v20);
  return a2;
}

