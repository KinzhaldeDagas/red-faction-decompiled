// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B420 rf_matrix3_repair_basis_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX source plus output, RET4. Copies source locally; normalizes nonzero forward, otherwise reconstructs from up cross right when usable, or chooses +X/+Z from up orientation. All-zero/insufficient-row case can leave forward zero. Uses per-axis near-equality to reject SAME directions, not general parallel/antiparallel detection. Builds/normalizes up from forward/right or fallback(-Z for pureY forward,else+Y), normalizes right=cross(up,forward), recomputes up=cross(forward,right), copies to output. Unchecked normalizers can produce NaNs on degenerate/opposite directions. No identity fallback guarantee.
float *__thiscall rf_matrix3_repair_basis_to_output(const float *this, float *a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+10h] [ebp-90h] BYREF
  float v8[3]; // [esp+1Ch] [ebp-84h] BYREF
  float v9[3]; // [esp+28h] [ebp-78h] BYREF
  float v10[3]; // [esp+34h] [ebp-6Ch] BYREF
  float v11[3]; // [esp+40h] [ebp-60h] BYREF
  float v12[3]; // [esp+4Ch] [ebp-54h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-48h] BYREF
  float v14[3]; // [esp+64h] [ebp-3Ch] BYREF
  float v15[3]; // [esp+70h] [ebp-30h] BYREF
  float v16[3]; // [esp+7Ch] [ebp-24h] BYREF
  float destination[3]; // [esp+88h] [ebp-18h] BYREF
  float v18; // [esp+94h] [ebp-Ch]
  float v19; // [esp+98h] [ebp-8h]
  float v20; // [esp+9Ch] [ebp-4h]

  rf_matrix3_copy_construct((int)v15, this);
  v20 = rf_vector3_length(destination);
  v18 = rf_vector3_length(v16);
  v19 = rf_vector3_length(v15);
  if ( v20 > 0.0 )
  {
    rf_vector_normalize_reciprocal_sqrt(destination);
  }
  else if ( v18 <= 0.0 || v19 <= 0.0 || rf_vector3_near_equal_per_axis_strict(v16, v15) )
  {
    if ( v18 > 0.0 )
    {
      if ( v16[0] == 0.0 && v16[1] == 0.0 && v16[2] != 0.0 )
        rf_vector3_set_components_thiscall(destination, 1.0, 0.0, 0.0);
      else
        rf_vector3_set_components_thiscall(destination, 0.0, 0.0, 1.0);
    }
  }
  else
  {
    v2 = rf_vector_cross(v16, v14, v15);
    rf_vector_copy(destination, copy_result, v2);
    rf_vector_normalize_reciprocal_sqrt(destination);
  }
  if ( v18 <= 0.0 || rf_vector3_near_equal_per_axis_strict(destination, v16) )
  {
    if ( v19 <= 0.0 || rf_vector3_near_equal_per_axis_strict(destination, v15) )
    {
      if ( destination[0] == 0.0 && destination[1] != 0.0 && destination[2] == 0.0 )
        rf_vector3_set_components_thiscall(v16, 0.0, 0.0, -1.0);
      else
        rf_vector3_set_components_thiscall(v16, 0.0, 1.0, 0.0);
    }
    else
    {
      v3 = rf_vector_cross(destination, v12, v15);
      rf_vector_copy(v16, v11, v3);
      rf_vector_normalize_reciprocal_sqrt(v16);
    }
  }
  else
  {
    rf_vector_normalize_reciprocal_sqrt(v16);
  }
  v4 = rf_vector_cross(v16, v10, destination);
  rf_vector_copy(v15, v9, v4);
  rf_vector_normalize_reciprocal_sqrt(v15);
  v5 = rf_vector_cross(destination, v8, v15);
  rf_vector_copy(v16, v7, v5);
  rf_matrix3_copy_construct((int)a2, v15);
  return a2;
}

