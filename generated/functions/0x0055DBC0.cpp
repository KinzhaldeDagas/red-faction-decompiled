// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055DBC0 rf_orientation_symmetric_accel_limits_for_duration
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(startMatrix,endMatrix,duration,outAccelerationXYZ,outPeakSpeedXYZ). Relative=end*transpose(start), rebuilds basis, extracts axis-angle,errorXYZ=axis*angle. If duration>float1e-5:accel_i=4*abs(error_i)/duration^2,peakSpeed_i=accel_i*duration/2. Otherwise zeros both outputs. Returns outAcceleration on normal branch, outPeakSpeed on fallback. Not a motion integrator; independent per-axis symmetric triangular-profile limits, no shortest-quaternion correction beyond extractor.
float *__cdecl rf_orientation_symmetric_accel_limits_for_duration(
        const float *a1,
        const float *a2,
        float a3,
        float *a4,
        float *a5)
{
  const float *v5; // eax
  float *v6; // eax
  float v8; // [esp+Ch] [ebp-B8h]
  float v9; // [esp+10h] [ebp-B4h]
  float v10; // [esp+14h] [ebp-B0h]
  float v11[9]; // [esp+18h] [ebp-ACh] BYREF
  _BYTE v12[36]; // [esp+3Ch] [ebp-88h] BYREF
  float v13[9]; // [esp+60h] [ebp-64h] BYREF
  float v14; // [esp+84h] [ebp-40h] BYREF
  float v15; // [esp+88h] [ebp-3Ch] BYREF
  float v16; // [esp+8Ch] [ebp-38h]
  float v17; // [esp+90h] [ebp-34h]
  float v18[9]; // [esp+94h] [ebp-30h] BYREF
  float v19[3]; // [esp+B8h] [ebp-Ch] BYREF

  rf_matrix3_construct((char *)v18);
  rf_matrix3_construct((char *)v13);
  rf_vector3_default_construct_noop(v19);
  rf_vector3_default_construct_noop(&v15);
  v5 = (const float *)rf_matrix3_transpose_to_output((float *)a1, (int)v12);
  rf_matrix3_copy(v18, v5);
  v6 = rf_matrix3_argument_times_receiver_to_output(v18, v11, a2);
  rf_matrix3_copy(v13, v6);
  rf_matrix3_rebuild_basis_from_forward_in_place(v13);
  rf_matrix3_extract_axis_angle(v13, v19, &v14);
  v15 = v14 * v19[0];
  v16 = v14 * v19[1];
  v17 = v14 * v19[2];
  if ( a3 > 0.000009999999747378752 )
  {
    v10 = fabs(v15);
    *a4 = v10 * 4.0 / (a3 * a3);
    v9 = fabs(v16);
    a4[1] = v9 * 4.0 / (a3 * a3);
    v8 = fabs(v17);
    a4[2] = v8 * 4.0 / (a3 * a3);
    *a5 = *a4 * a3 / 2.0;
    a5[1] = a4[1] * a3 / 2.0;
    a5[2] = a4[2] * a3 / 2.0;
    return a4;
  }
  else
  {
    rf_vector3_set_components_thiscall(a4, 0.0, 0.0, 0.0);
    return rf_vector3_set_components_thiscall(a5, 0.0, 0.0, 0.0);
  }
}

