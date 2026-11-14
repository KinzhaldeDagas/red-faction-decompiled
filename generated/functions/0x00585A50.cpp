// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00585A50 rf_character_blend_local_transforms
// UNREALRED VERIFIED [animation-mix-decode]: Blends weighted translation and ordered quaternion contributions for one local transform.
void __cdecl rf_character_blend_local_transforms(float *a1, float *a2, float *vector, int a4, float *a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *scalar; // [esp+Ch] [ebp-98h]
  float v9; // [esp+10h] [ebp-94h]
  float v10[3]; // [esp+18h] [ebp-8Ch] BYREF
  float copy_result[3]; // [esp+24h] [ebp-80h] BYREF
  float sum_result[3]; // [esp+30h] [ebp-74h] BYREF
  float scaled_result[3]; // [esp+3Ch] [ebp-68h] BYREF
  float v14[3]; // [esp+48h] [ebp-5Ch] BYREF
  float v15[4]; // [esp+54h] [ebp-50h] BYREF
  float v16; // [esp+64h] [ebp-40h]
  float v17[3]; // [esp+68h] [ebp-3Ch] BYREF
  int v18[4]; // [esp+74h] [ebp-30h] BYREF
  int i; // [esp+84h] [ebp-20h]
  int v20[4]; // [esp+88h] [ebp-1Ch] BYREF
  float destination[3]; // [esp+98h] [ebp-Ch] BYREF

  if ( a4 == 1 )
  {
    rf_affine3x4_set_quaternion_translation(a1, a2, vector);
  }
  else if ( a4 == 2 )
  {
    rf_float4_construct_zero_zero_zero_one((float *)v20);
    rf_quaternion_interpolate((float *)v20, a2, a2 + 4, a5[1]);
    rf_vector3_default_construct_noop(destination);
    scalar = rf_vector_multiply_scalar(vector + 3, scaled_result, a5[1]);
    v5 = rf_vector_multiply_scalar(vector, v14, *a5);
    v6 = rf_vector_add(v5, sum_result, scalar);
    rf_vector_copy(destination, copy_result, v6);
    rf_affine3x4_set_quaternion_translation(a1, (float *)v20, destination);
  }
  else
  {
    rf_vector3_set_components_return_destination(v17, 0.0, 0.0, 0.0);
    for ( i = 0; i < a4; ++i )
    {
      v7 = rf_vector_multiply_scalar(&vector[3 * i], v10, a5[i]);
      rf_vector_accumulate(v17, v7);
    }
    rf_float4_construct_zero_zero_zero_one((float *)v18);
    rf_float4_construct_components(v15, 0.0, 0.0, 0.0, 1.0);
    v16 = 0.0;
    for ( i = 0; i < a4; ++i )
    {
      v16 = v16 + a5[i];
      v9 = a5[i] / v16;
      rf_quaternion_interpolate((float *)v18, v15, &a2[4 * i], v9);
      rf_float4_copy_return_destination(v15, (float *)v18);
    }
    rf_affine3x4_set_quaternion_translation(a1, (float *)v18, v17);
    if ( *a1 == 0.0 )
      *a1 = 0.000001;
  }
}

