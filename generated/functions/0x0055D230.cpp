// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055D230 rf_orientation_step_toward_forward_and_bank
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(targetForward,currentMatrix,currentAngularVelocity,dt,bankDegrees,outMatrix,outAngularVelocity,maxSpeedXYZ,accelXYZ,clampStoppingSpeed). Cross(current.forward,target), clamp cross length at1, angle=ASIN(length) from mislabeled55EA80, with pi-angle when dot<0. Tiny cross<~1e-20 selects pi/current.right for nonpositive dot,else0. Transforms axis by current matrix rows, controls X/Y error components via signed scalar profiles. Bank component separately uses bankDegrees*0.01745299994945526. If bankDegrees,maxSpeedZ,accelZ all0, skips Z profile and leaves outAngularVelocity.z untouched before later transform. Normalizes step axis only if length>float1e-7; length<threshold copies current matrix
// and returns without velocity-frame transform. Otherwise out=delta*current, rebuilds basis, inverse-rotates output velocity by delta. Exact threshold equality skips normalization but still constructs delta. No input-forward normalization or dt/finite guards.
float *__cdecl rf_orientation_step_toward_forward_and_bank(
        const float *a1,
        const float *source,
        const float *a3,
        float a4,
        float a5,
        float *a6,
        float *a7,
        const float *a8,
        const float *a9,
        int a10)
{
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v14; // eax
  float v15; // [esp+0h] [ebp-124h]
  float v16; // [esp+0h] [ebp-124h]
  float v17; // [esp+0h] [ebp-124h]
  float v18; // [esp+0h] [ebp-124h]
  float v19; // [esp+0h] [ebp-124h]
  float v20; // [esp+0h] [ebp-124h]
  float v21; // [esp+8h] [ebp-11Ch]
  float v22; // [esp+8h] [ebp-11Ch]
  float v23; // [esp+8h] [ebp-11Ch]
  float v24; // [esp+1Ch] [ebp-108h]
  BOOL v25; // [esp+20h] [ebp-104h]
  float v26; // [esp+24h] [ebp-100h]
  float v27[9]; // [esp+28h] [ebp-FCh] BYREF
  float v28[3]; // [esp+4Ch] [ebp-D8h] BYREF
  float v29[3]; // [esp+58h] [ebp-CCh] BYREF
  float scaled_result[3]; // [esp+64h] [ebp-C0h] BYREF
  float v31[3]; // [esp+70h] [ebp-B4h] BYREF
  float v32[3]; // [esp+7Ch] [ebp-A8h] BYREF
  float v33[3]; // [esp+88h] [ebp-9Ch] BYREF
  float copy_result[3]; // [esp+94h] [ebp-90h] BYREF
  float v35[3]; // [esp+A0h] [ebp-84h] BYREF
  float scalar; // [esp+ACh] [ebp-78h]
  float v37; // [esp+B0h] [ebp-74h]
  float v38; // [esp+B4h] [ebp-70h]
  float vector[3]; // [esp+B8h] [ebp-6Ch] BYREF
  float v40; // [esp+C4h] [ebp-60h] BYREF
  float v41; // [esp+C8h] [ebp-5Ch]
  BOOL v42; // [esp+D0h] [ebp-54h]
  float v43[9]; // [esp+D4h] [ebp-50h] BYREF
  float v44; // [esp+F8h] [ebp-2Ch]
  _BYTE v45[12]; // [esp+FCh] [ebp-28h] BYREF
  float destination[3]; // [esp+108h] [ebp-1Ch] BYREF
  float v47; // [esp+114h] [ebp-10h] BYREF
  float v48; // [esp+118h] [ebp-Ch]
  float v49; // [esp+11Ch] [ebp-8h]
  float v50; // [esp+120h] [ebp-4h]
  float v51; // [esp+13Ch] [ebp+18h]

  rf_matrix3_construct((char *)v43);
  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(&v40);
  rf_vector3_default_construct_noop(&v47);
  rf_vector3_default_construct_noop(v45);
  v10 = rf_vector_cross((float *)source + 6, v35, (float *)a1);
  rf_vector_copy(destination, copy_result, v10);
  v37 = rf_vector3_length(destination);
  if ( v37 > 1.0 )
    v37 = 1.0;
  v38 = rf_vector_dot((float *)source + 6, (float *)a1);
  if ( v37 >= 9.999999682655225e-21 )
  {
    scalar = rf_asin_float(v37);
    v26 = 1.0 / v37;
    rf_vector3_scale_in_place_return_self(destination, v26);
    if ( v38 < 0.0 )
      scalar = 3.141592741012573 - scalar;
  }
  else if ( v38 <= 0.0 )
  {
    scalar = 3.1415927;
    rf_vector_copy(destination, v33, source);
  }
  else
  {
    scalar = 0.0;
  }
  v11 = rf_vector3_transform_by_matrix_rows(destination, v32, (float *)source);
  rf_vector_copy(vector, v31, v11);
  v12 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  rf_vector_copy(&v40, v29, v12);
  rf_vector3_zero_return_destination(&v47);
  if ( v40 <= 0.0 )
  {
    if ( v40 >= 0.0 )
    {
      if ( *a3 >= 0.0 )
      {
        v16 = -*a3;
        v50 = rf_motion_profile_step_reversing_velocity(v16, *a8, v40, *a9, a4, a7, a10);
        v47 = -v50;
        *a7 = -*a7;
      }
      else
      {
        v50 = rf_motion_profile_step_reversing_velocity(*a3, *a8, v40, *a9, a4, a7, a10);
        v47 = v50;
      }
    }
    else
    {
      v21 = -v40;
      v15 = -*a3;
      if ( *a3 > 0.0 )
        v50 = rf_motion_profile_step_reversing_velocity(v15, *a8, v21, *a9, a4, a7, a10);
      else
        v50 = rf_motion_profile_step_toward_distance(v15, *a8, v21, *a9, a4, a7, a10);
      v47 = -v50;
      *a7 = -*a7;
    }
  }
  else
  {
    if ( *a3 < 0.0 )
      v50 = rf_motion_profile_step_reversing_velocity(*a3, *a8, v40, *a9, a4, a7, a10);
    else
      v50 = rf_motion_profile_step_toward_distance(*a3, *a8, v40, *a9, a4, a7, a10);
    v47 = v50;
  }
  if ( v41 <= 0.0 )
  {
    if ( v41 >= 0.0 )
    {
      if ( a3[1] >= 0.0 )
      {
        v18 = -a3[1];
        v50 = rf_motion_profile_step_reversing_velocity(v18, a8[1], v41, a9[1], a4, a7 + 1, a10);
        v48 = -v50;
        a7[1] = -a7[1];
      }
      else
      {
        v50 = rf_motion_profile_step_reversing_velocity(a3[1], a8[1], v41, a9[1], a4, a7 + 1, a10);
        v48 = v50;
      }
    }
    else
    {
      v22 = -v41;
      v17 = -a3[1];
      if ( a3[1] > 0.0 )
        v50 = rf_motion_profile_step_reversing_velocity(v17, a8[1], v22, a9[1], a4, a7 + 1, a10);
      else
        v50 = rf_motion_profile_step_toward_distance(v17, a8[1], v22, a9[1], a4, a7 + 1, a10);
      v48 = -v50;
      a7[1] = -a7[1];
    }
  }
  else
  {
    if ( a3[1] < 0.0 )
      v50 = rf_motion_profile_step_reversing_velocity(a3[1], a8[1], v41, a9[1], a4, a7 + 1, a10);
    else
      v50 = rf_motion_profile_step_toward_distance(a3[1], a8[1], v41, a9[1], a4, a7 + 1, a10);
    v48 = v50;
  }
  v25 = a5 == 0.0 && a8[2] == 0.0 && a9[2] == 0.0;
  v42 = v25;
  v44 = 0.0;
  if ( !v25 )
  {
    v51 = a5 * 0.01745299994945526;
    if ( v51 <= 0.0 )
    {
      if ( v51 >= 0.0 )
      {
        if ( a3[2] >= 0.0 )
        {
          v20 = -a3[2];
          v50 = rf_motion_profile_step_reversing_velocity(v20, a8[2], v51, a9[2], a4, a7 + 2, a10);
          v44 = -v50;
          a7[2] = -a7[2];
        }
        else
        {
          v50 = rf_motion_profile_step_reversing_velocity(a3[2], a8[2], v51, a9[2], a4, a7 + 2, a10);
          v44 = v50;
        }
      }
      else
      {
        v23 = -v51;
        v19 = -a3[2];
        if ( a3[2] > 0.0 )
          v50 = rf_motion_profile_step_reversing_velocity(v19, a8[2], v23, a9[2], a4, a7 + 2, a10);
        else
          v50 = rf_motion_profile_step_toward_distance(v19, a8[2], v23, a9[2], a4, a7 + 2, a10);
        v44 = -v50;
        a7[2] = -a7[2];
      }
    }
    else
    {
      if ( a3[2] < 0.0 )
        v50 = rf_motion_profile_step_reversing_velocity(a3[2], a8[2], v51, a9[2], a4, a7 + 2, a10);
      else
        v50 = rf_motion_profile_step_toward_distance(a3[2], a8[2], v51, a9[2], a4, a7 + 2, a10);
      v44 = v50;
    }
  }
  v49 = v44;
  rf_vector_copy(destination, v28, &v47);
  scalar = rf_vector3_length(destination);
  if ( scalar > 0.0000001000000011686097 )
  {
    v24 = 1.0 / scalar;
    rf_vector3_scale_in_place_return_self(destination, v24);
  }
  if ( scalar < 0.0000001000000011686097 )
    return (float *)rf_matrix3_copy(a6, source);
  rf_matrix3_set_axis_angle_unchecked_axis(v43, destination, scalar);
  v14 = rf_matrix3_argument_times_receiver_to_output(source, v27, v43);
  rf_matrix3_copy(a6, v14);
  rf_matrix3_rebuild_basis_from_forward_in_place(a6);
  return rf_matrix3_inverse_rotate_vector(a7, v43);
}

