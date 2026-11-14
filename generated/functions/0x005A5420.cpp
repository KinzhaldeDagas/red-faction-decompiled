// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5420 rf_hermite3_evaluate_segment_derivative
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall object,destination,float t,segment index. Same point/tangent slots as0x5A5270,weights6t^2-6t,-6t^2+6t,3t^2-4t+1,3t^2-2t. Produces derivative with respect to LOCAL t,not time-normalized velocity or unit direction. No count/segment/t/pointer validation or normalization. Returns final vector-copy helper result.
float *__thiscall rf_hermite3_evaluate_segment_derivative(const float *this, float *a2, float a3, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v13[3]; // [esp+8h] [ebp-D0h] BYREF
  float v14[3]; // [esp+14h] [ebp-C4h] BYREF
  float v15[3]; // [esp+20h] [ebp-B8h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-ACh] BYREF
  float v17[3]; // [esp+38h] [ebp-A0h] BYREF
  float v18[3]; // [esp+44h] [ebp-94h] BYREF
  float v19[3]; // [esp+50h] [ebp-88h] BYREF
  float v20[3]; // [esp+5Ch] [ebp-7Ch] BYREF
  float v21[3]; // [esp+68h] [ebp-70h] BYREF
  float v22[3]; // [esp+74h] [ebp-64h] BYREF
  float copy_result[3]; // [esp+80h] [ebp-58h] BYREF
  float scaled_result[3]; // [esp+8Ch] [ebp-4Ch] BYREF
  float v25; // [esp+98h] [ebp-40h]
  float v26; // [esp+9Ch] [ebp-3Ch]
  float rhs[3]; // [esp+A0h] [ebp-38h] BYREF
  float v28; // [esp+ACh] [ebp-2Ch]
  float v29[3]; // [esp+B0h] [ebp-28h] BYREF
  float v30[3]; // [esp+BCh] [ebp-1Ch] BYREF
  float destination[3]; // [esp+C8h] [ebp-10h] BYREF
  float scalar; // [esp+D4h] [ebp-4h]

  scalar = a3 * 6.0 * a3 - a3 * 6.0;
  v28 = a3 * -6.0 * a3 + a3 * 6.0;
  v25 = a3 * 3.0 * a3 - a3 * 4.0 + 1.0;
  v26 = a3 * 3.0 * a3 - a3 * 2.0;
  rf_vector3_default_construct_noop(destination);
  v4 = rf_vector_multiply_scalar(this + 3 * a4, scaled_result, scalar);
  rf_vector_copy(destination, copy_result, v4);
  rf_vector3_default_construct_noop(rhs);
  v5 = rf_vector_multiply_scalar(this + 3 * a4 + 3, v22, v28);
  rf_vector_copy(rhs, v21, v5);
  rf_vector3_default_construct_noop(v29);
  v6 = rf_vector_multiply_scalar(this + 3 * a4 + 9, v20, v25);
  rf_vector_copy(v29, v19, v6);
  rf_vector3_default_construct_noop(v30);
  v7 = rf_vector_multiply_scalar(this + 3 * a4 + 12, v18, v26);
  rf_vector_copy(v30, v17, v7);
  v8 = rf_vector_add(destination, sum_result, rhs);
  v9 = rf_vector_add(v8, v15, v29);
  v10 = rf_vector_add(v9, v14, v30);
  return rf_vector_copy(a2, v13, v10);
}

