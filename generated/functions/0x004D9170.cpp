// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D9170 rf_physics_body_finalize_step
// UNREALRED VERIFIED [trigger-geometry-20261020] Partial-step finalization computes predicted-current, advances current by the earliest collision fraction (with source backoff), and consumes residual time. RF trigger motion samples can differ from UE final movement; the new UnrealRed adapter explicitly captures UE movement-update segments, not guessed velocities or a promise of identical physics scheduling.
float *__cdecl rf_physics_body_finalize_step(int a1)
{
  float *v1; // eax
  float *result; // eax
  float v3[9]; // [esp+8h] [ebp-84h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-60h] BYREF
  int v5; // [esp+38h] [ebp-54h]
  int v6; // [esp+3Ch] [ebp-50h]
  float out_vector[3]; // [esp+40h] [ebp-4Ch] BYREF
  float v8[9]; // [esp+4Ch] [ebp-40h] BYREF
  float v9; // [esp+70h] [ebp-1Ch]
  float source; // [esp+74h] [ebp-18h] BYREF
  float v11; // [esp+78h] [ebp-14h]
  float v12; // [esp+7Ch] [ebp-10h]
  float v13; // [esp+80h] [ebp-Ch]
  float v14; // [esp+84h] [ebp-8h]
  float v15; // [esp+88h] [ebp-4h]

  v15 = *(float *)(a1 + 432) * *(float *)(a1 + 460);
  v14 = *(float *)(a1 + 432) - v15;
  if ( *(float *)(a1 + 460) >= 1.0 )
  {
    result = rf_physics_body_commit_full_step(a1);
    *(float *)(a1 + 432) = 0.0;
  }
  else
  {
    rf_vector_subtract((const float *)(a1 + 240), out_vector, (const float *)(a1 + 228));
    v9 = rf_vector3_length(out_vector);
    v13 = (v9 * *(float *)(a1 + 460) - 0.05000000074505806) / v9;
    if ( v13 >= 0.0 )
      *(float *)(a1 + 460) = v13;
    else
      *(float *)(a1 + 460) = 0.0;
    rf_vector3_scale_in_place_return_self(out_vector, *(float *)(a1 + 460));
    rf_vector_accumulate((float *)(a1 + 228), out_vector);
    rf_vector_multiply_scalar((const float *)(a1 + 336), &source, *(float *)(a1 + 432));
    rf_matrix3_inverse_rotate_vector(&source, (float *)(a1 + 252));
    if ( (*(_DWORD *)(a1 + 424) & 0x4000) != 0 && !*(_DWORD *)(a1 + 36) )
    {
      v6 = a1;
      rf_vector_copy((float *)(a1 + 2160), copy_result, &source);
    }
    v9 = rf_vector3_length(&source);
    if ( v9 > 0.0 )
    {
      source = source / v9;
      v11 = v11 / v9;
      v12 = v12 / v9;
    }
    rf_matrix3_construct_from_axis_angle((int)v8, &source, v9);
    v1 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 252), v3, v8);
    rf_matrix3_copy((float *)(a1 + 252), v1);
    rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 252));
    rf_physics_state_rebuild_rotated_tensor(a1 + 136);
    if ( (*(_DWORD *)(a1 + 424) & 0x20000000) != 0 )
    {
      *(_DWORD *)(a1 + 424) &= ~0x20000000u;
      *(float *)(a1 + 432) = *(float *)(a1 + 432) - v15;
      return (float *)a1;
    }
    else
    {
      v5 = rf_object_contact_response_dispatch((_DWORD *)a1);
      if ( v5 )
      {
        if ( v5 == 2 )
          rf_physics_body_resolve_world_contact(a1);
        *(float *)(a1 + 432) = *(float *)(a1 + 432) - v15;
      }
      else
      {
        *(float *)(a1 + 432) = 0.0;
      }
      *(_DWORD *)(a1 + 424) |= 0x10000000u;
      return (float *)a1;
    }
  }
  return result;
}

