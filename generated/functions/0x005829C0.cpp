// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005829C0 rf_quaternion_hamilton_product_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Thiscall sourceA,stack output/sourceB. Snapshots xyz vectors and w values;out.xyz=A.xyz*B.w+B.xyz*A.w+cross(A.xyz,B.xyz),out.w=A.w*B.w-dot(A.xyz,B.xyz). Writes local quaternion to destination and returns destination. Hamilton A*B order,not componentwise product or B*A. No normalization/shortest-path sign selection. Input snapshots/local result permit output aliasing either input.
float *__thiscall rf_quaternion_hamilton_product_to_destination(float *this, float *a2, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float *scalar; // [esp+8h] [ebp-84h]
  double v7; // [esp+14h] [ebp-78h]
  float sum_result[3]; // [esp+20h] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-60h] BYREF
  float v11[3]; // [esp+38h] [ebp-54h] BYREF
  float v12[4]; // [esp+44h] [ebp-48h] BYREF
  float v13; // [esp+54h] [ebp-38h]
  float v14; // [esp+58h] [ebp-34h]
  float v15[3]; // [esp+5Ch] [ebp-30h] BYREF
  float vector[3]; // [esp+68h] [ebp-24h] BYREF
  float rhs[3]; // [esp+74h] [ebp-18h] BYREF
  float v18[3]; // [esp+80h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(v15);
  vector[0] = *this;
  vector[1] = *(this + 1);
  vector[2] = *(this + 2);
  v15[0] = *a3;
  v15[1] = a3[1];
  v15[2] = a3[2];
  v13 = *(this + 3);
  v14 = a3[3];
  rf_vector_cross(vector, rhs, v15);
  scalar = rf_vector_multiply_scalar(vector, scaled_result, v14);
  v3 = rf_vector_multiply_scalar(v15, v11, v13);
  v4 = rf_vector_add(v3, sum_result, scalar);
  rf_vector_add(v4, v18, rhs);
  rf_float4_construct_zero_zero_zero_one(v12);
  v7 = v13 * v14;
  v12[3] = v7 - rf_vector_dot(vector, v15);
  v12[0] = v18[0];
  v12[1] = v18[1];
  v12[2] = v18[2];
  rf_float4_assign_components_return_this(a2, v12);
  return a2;
}

