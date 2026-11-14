// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405330 rf_ai_update_authored_yaw_sweep
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block. Signed wrapping difference DWORD+684 - DWORD+688: >180 calls410920(owner,owner COMMON position+60 +100*FIRST
// orientation row+72), not forward row+96. Difference<=0 no effects. Positive<=180: deadline+680 nonelapsed ->zero owner vector+336 only. Elapsed ->select signed angle endpoint+684
// if flags+1328 mask0x400 set else+688; radians=float32(endpoint*DOUBLE3.1415927410125732/DOUBLE180). Build axis-angle about(0,1,0), inverse-rotate copied owner vector+5048,
// normalize it, form target=owner retained point+2004+100*direction, call410920 discardingST0. Then normalizes ABSOLUTE target-point local (unused afterwards), not a new relative
// delta. Dot(owner vector+2040,direction) roundedfloat32 ordered>=DOUBLE0.99 ->arm+680 with4000ms and toggle mask0x400. NaN rejects; no angle wrap/clamp, source normalization guard
// or role test.
void __cdecl rf_ai_update_authored_yaw_sweep(int *a1)
{
  float *v1; // eax
  double v2; // st7
  float *v3; // eax
  float *v4; // eax
  unsigned int v5; // eax
  float v6[3]; // [esp+Ch] [ebp-9Ch] BYREF
  float v7[3]; // [esp+18h] [ebp-90h] BYREF
  float v8[3]; // [esp+24h] [ebp-84h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-78h] BYREF
  float scaled_result[3]; // [esp+3Ch] [ebp-6Ch] BYREF
  float destination[3]; // [esp+48h] [ebp-60h] BYREF
  float target_point[3]; // [esp+54h] [ebp-54h] BYREF
  float v13[9]; // [esp+60h] [ebp-48h] BYREF
  int v14[3]; // [esp+84h] [ebp-24h] BYREF
  float v15; // [esp+90h] [ebp-18h]
  float v16; // [esp+94h] [ebp-14h]
  float sum_result[3]; // [esp+98h] [ebp-10h] BYREF
  int v18; // [esp+A4h] [ebp-4h]

  v18 = a1[171] - a1[172];
  if ( v18 <= 180 )
  {
    if ( v18 > 0 )
    {
      if ( rf_replicator_has_elapsed(a1 + 170) )
      {
        rf_vector3_default_construct_noop(destination);
        rf_vector3_default_construct_noop(target_point);
        if ( (a1[332] & 0x400) != 0 )
          v2 = (double)a1[171] * 3.141592741012573 / 180.0;
        else
          v2 = (double)a1[172] * 3.141592741012573 / 180.0;
        v15 = v2;
        rf_matrix3_construct((char *)v13);
        rf_vector3_default_construct_noop(v14);
        rf_vector3_set_components_thiscall((float *)v14, 0.0, 1.0, 0.0);
        rf_matrix3_set_axis_angle_unchecked_axis(v13, (float *)v14, v15);
        rf_vector_copy(destination, copy_result, (const float *)(*a1 + 5048));
        rf_matrix3_inverse_rotate_vector(destination, v13);
        rf_vector_normalize_reciprocal_sqrt(destination);
        v3 = rf_vector_multiply_scalar(destination, v8, 100.0);
        v4 = rf_vector_add((const float *)(*a1 + 2004), v7, v3);
        rf_vector_copy(target_point, v6, v4);
        sub_410920(*a1, target_point);
        rf_vector_normalize_reciprocal_sqrt(target_point);
        v16 = rf_vector_dot((float *)(*a1 + 2040), destination);
        if ( v16 >= 0.99 )
        {
          rf_replicator_arm_milliseconds(a1 + 170, 4000);
          if ( (a1[332] & 0x400) != 0 )
            v5 = a1[332] & 0xFFFFFBFF;
          else
            v5 = a1[332] | 0x400;
          a1[332] = v5;
        }
      }
      else
      {
        rf_vector3_zero_return_destination((float *)(*a1 + 336));
      }
    }
  }
  else
  {
    v1 = rf_vector_multiply_scalar((const float *)(*a1 + 72), scaled_result, 100.0);
    rf_vector_add((const float *)(*a1 + 60), sum_result, v1);
    sub_410920(*a1, sum_result);
  }
}

