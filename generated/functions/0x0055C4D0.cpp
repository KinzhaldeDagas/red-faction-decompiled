// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C4D0 rf_orientation_step_with_axis_velocity_limits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(target,current,currentAngularVelocity,dt,outMatrix,outAngularVelocity,maxSpeedXYZ,accelerationXYZ,clampStoppingSpeed). Relative=target*transpose(current) through REVERSED-factor helper413070, rebuilds relative basis55B770, extracts axis-angle and errorVector=axis*angle. For angle>=float1e-7, applies signed scalar profiles55CD20/55CE30 independently per error component, mirrors negative-axis step/output velocity signs, then unchecked-normalizes step vector returning step angle. If computed step vector exactly equals error vector, copies target directly; else delta=axisAngle(step), out=delta*current and rebuilds basis. Angle below threshold copies target and zeros output velocity. Zero
// nonarrival step can reach unchecked zero-axis normalization; no dt/limit/finite validation, no guaranteed unit matrix or uniform EAX return pointer.
float *__cdecl rf_orientation_step_with_axis_velocity_limits(
        const float *a1,
        const float *a2,
        const float *a3,
        float a4,
        float *a5,
        float *a6,
        const float *a7,
        const float *a8,
        int a9)
{
  const float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v13; // eax
  float v14; // [esp+0h] [ebp-120h]
  float v15; // [esp+0h] [ebp-120h]
  float v16; // [esp+0h] [ebp-120h]
  float v17; // [esp+0h] [ebp-120h]
  float v18; // [esp+0h] [ebp-120h]
  float v19; // [esp+0h] [ebp-120h]
  float v20; // [esp+8h] [ebp-118h]
  float v21; // [esp+8h] [ebp-118h]
  float v22; // [esp+8h] [ebp-118h]
  float v23[9]; // [esp+1Ch] [ebp-104h] BYREF
  float v24[3]; // [esp+40h] [ebp-E0h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+58h] [ebp-C8h] BYREF
  float v27[9]; // [esp+64h] [ebp-BCh] BYREF
  _BYTE v28[36]; // [esp+88h] [ebp-98h] BYREF
  float v29[9]; // [esp+ACh] [ebp-74h] BYREF
  float scalar; // [esp+D0h] [ebp-50h] BYREF
  float destination; // [esp+D4h] [ebp-4Ch] BYREF
  float v32; // [esp+D8h] [ebp-48h]
  float v33; // [esp+DCh] [ebp-44h]
  float v34[9]; // [esp+E0h] [ebp-40h] BYREF
  float vector[3]; // [esp+104h] [ebp-1Ch] BYREF
  float source; // [esp+110h] [ebp-10h] BYREF
  float v37; // [esp+114h] [ebp-Ch]
  float v38; // [esp+118h] [ebp-8h]
  float v39; // [esp+11Ch] [ebp-4h]

  rf_matrix3_construct((char *)v29);
  rf_matrix3_construct((char *)v34);
  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(&destination);
  rf_vector3_default_construct_noop(&source);
  v9 = (const float *)rf_matrix3_transpose_to_output((float *)a2, (int)v28);
  v10 = rf_matrix3_argument_times_receiver_to_output(v9, v27, a1);
  rf_matrix3_copy(v29, v10);
  rf_matrix3_rebuild_basis_from_forward_in_place(v29);
  rf_matrix3_extract_axis_angle(v29, vector, &scalar);
  v11 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  rf_vector_copy(&destination, copy_result, v11);
  if ( scalar >= 0.0000001000000011686097 )
  {
    rf_vector3_zero_return_destination(&source);
    if ( destination <= 0.0 )
    {
      if ( destination >= 0.0 )
      {
        if ( *a3 >= 0.0 )
        {
          v15 = -*a3;
          v39 = rf_motion_profile_step_reversing_velocity(v15, *a7, destination, *a8, a4, a6, a9);
          source = -v39;
          *a6 = -*a6;
        }
        else
        {
          v39 = rf_motion_profile_step_reversing_velocity(*a3, *a7, destination, *a8, a4, a6, a9);
          source = v39;
        }
      }
      else
      {
        v20 = -destination;
        v14 = -*a3;
        if ( *a3 > 0.0 )
          v39 = rf_motion_profile_step_reversing_velocity(v14, *a7, v20, *a8, a4, a6, a9);
        else
          v39 = rf_motion_profile_step_toward_distance(v14, *a7, v20, *a8, a4, a6, a9);
        source = -v39;
        *a6 = -*a6;
      }
    }
    else
    {
      if ( *a3 < 0.0 )
        v39 = rf_motion_profile_step_reversing_velocity(*a3, *a7, destination, *a8, a4, a6, a9);
      else
        v39 = rf_motion_profile_step_toward_distance(*a3, *a7, destination, *a8, a4, a6, a9);
      source = v39;
    }
    if ( v32 <= 0.0 )
    {
      if ( v32 >= 0.0 )
      {
        if ( a3[1] >= 0.0 )
        {
          v17 = -a3[1];
          v39 = rf_motion_profile_step_reversing_velocity(v17, a7[1], v32, a8[1], a4, a6 + 1, a9);
          v37 = -v39;
          a6[1] = -a6[1];
        }
        else
        {
          v39 = rf_motion_profile_step_reversing_velocity(a3[1], a7[1], v32, a8[1], a4, a6 + 1, a9);
          v37 = v39;
        }
      }
      else
      {
        v21 = -v32;
        v16 = -a3[1];
        if ( a3[1] > 0.0 )
          v39 = rf_motion_profile_step_reversing_velocity(v16, a7[1], v21, a8[1], a4, a6 + 1, a9);
        else
          v39 = rf_motion_profile_step_toward_distance(v16, a7[1], v21, a8[1], a4, a6 + 1, a9);
        v37 = -v39;
        a6[1] = -a6[1];
      }
    }
    else
    {
      if ( a3[1] < 0.0 )
        v39 = rf_motion_profile_step_reversing_velocity(a3[1], a7[1], v32, a8[1], a4, a6 + 1, a9);
      else
        v39 = rf_motion_profile_step_toward_distance(a3[1], a7[1], v32, a8[1], a4, a6 + 1, a9);
      v37 = v39;
    }
    if ( v33 <= 0.0 )
    {
      if ( v33 >= 0.0 )
      {
        if ( a3[2] >= 0.0 )
        {
          v19 = -a3[2];
          v39 = rf_motion_profile_step_reversing_velocity(v19, a7[2], v33, a8[2], a4, a6 + 2, a9);
          v38 = -v39;
          a6[2] = -a6[2];
        }
        else
        {
          v39 = rf_motion_profile_step_reversing_velocity(a3[2], a7[2], v33, a8[2], a4, a6 + 2, a9);
          v38 = v39;
        }
      }
      else
      {
        v22 = -v33;
        v18 = -a3[2];
        if ( a3[2] > 0.0 )
          v39 = rf_motion_profile_step_reversing_velocity(v18, a7[2], v22, a8[2], a4, a6 + 2, a9);
        else
          v39 = rf_motion_profile_step_toward_distance(v18, a7[2], v22, a8[2], a4, a6 + 2, a9);
        v38 = -v39;
        a6[2] = -a6[2];
      }
    }
    else
    {
      if ( a3[2] < 0.0 )
        v39 = rf_motion_profile_step_reversing_velocity(a3[2], a7[2], v33, a8[2], a4, a6 + 2, a9);
      else
        v39 = rf_motion_profile_step_toward_distance(a3[2], a7[2], v33, a8[2], a4, a6 + 2, a9);
      v38 = v39;
    }
    rf_vector_copy(vector, v24, &source);
    scalar = rf_vector3_normalize_return_length(vector);
    if ( destination == source && v32 == v37 && v33 == v38 )
    {
      return (float *)rf_matrix3_copy(a5, a1);
    }
    else
    {
      rf_matrix3_set_axis_angle_unchecked_axis(v34, vector, scalar);
      v13 = rf_matrix3_argument_times_receiver_to_output(a2, v23, v34);
      rf_matrix3_copy(a5, v13);
      return (float *)rf_matrix3_rebuild_basis_from_forward_in_place(a5);
    }
  }
  else
  {
    rf_matrix3_copy(a5, a1);
    return rf_vector3_zero_return_destination(a6);
  }
}

