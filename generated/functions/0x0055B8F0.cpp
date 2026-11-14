// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B8F0 rf_matrix3_repair_basis_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): In-place counterpart of55B420: normalize/reconstruct forward, select/reconstruct up using nonzero lengths and per-axis near-equality, normalize right=up cross forward, recompute up=forward cross right. Equality predicate does not catch opposite/other collinear axes. All-zero matrix does not yield identity and unchecked normalization can produce NaNs. Final EAX comes from copy into UP ROW at receiver+12, not necessarily matrix base.
float *__thiscall rf_matrix3_repair_basis_in_place(float *this)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v7[3]; // [esp+10h] [ebp-6Ch] BYREF
  float v8[3]; // [esp+1Ch] [ebp-60h] BYREF
  float v9[3]; // [esp+28h] [ebp-54h] BYREF
  float v10[3]; // [esp+34h] [ebp-48h] BYREF
  float v11[3]; // [esp+40h] [ebp-3Ch] BYREF
  float v12[3]; // [esp+4Ch] [ebp-30h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-24h] BYREF
  float v14[3]; // [esp+64h] [ebp-18h] BYREF
  float v15; // [esp+70h] [ebp-Ch]
  float v16; // [esp+74h] [ebp-8h]
  float v17; // [esp+78h] [ebp-4h]

  v17 = rf_vector3_length(this + 6);
  v15 = rf_vector3_length(this + 3);
  v16 = rf_vector3_length(this);
  if ( v17 > 0.0 )
  {
    rf_vector_normalize_reciprocal_sqrt(this + 6);
  }
  else if ( v15 <= 0.0 || v16 <= 0.0 || rf_vector3_near_equal_per_axis_strict(this + 3, this) )
  {
    if ( v15 > 0.0 )
    {
      if ( *(this + 3) == 0.0 && *(this + 4) == 0.0 && *(this + 5) != 0.0 )
        rf_vector3_set_components_thiscall(this + 6, 1.0, 0.0, 0.0);
      else
        rf_vector3_set_components_thiscall(this + 6, 0.0, 0.0, 1.0);
    }
  }
  else
  {
    v1 = rf_vector_cross(this + 3, v14, this);
    rf_vector_copy(this + 6, copy_result, v1);
    rf_vector_normalize_reciprocal_sqrt(this + 6);
  }
  if ( v15 <= 0.0 || rf_vector3_near_equal_per_axis_strict(this + 6, this + 3) )
  {
    if ( v16 <= 0.0 || rf_vector3_near_equal_per_axis_strict(this + 6, this) )
    {
      if ( *(this + 6) == 0.0 && *(this + 7) != 0.0 && *(this + 8) == 0.0 )
        rf_vector3_set_components_thiscall(this + 3, 0.0, 0.0, -1.0);
      else
        rf_vector3_set_components_thiscall(this + 3, 0.0, 1.0, 0.0);
    }
    else
    {
      v2 = rf_vector_cross(this + 6, v12, this);
      rf_vector_copy(this + 3, v11, v2);
      rf_vector_normalize_reciprocal_sqrt(this + 3);
    }
  }
  else
  {
    rf_vector_normalize_reciprocal_sqrt(this + 3);
  }
  v3 = rf_vector_cross(this + 3, v10, this + 6);
  rf_vector_copy(this, v9, v3);
  rf_vector_normalize_reciprocal_sqrt(this);
  v4 = rf_vector_cross(this + 6, v8, this);
  return rf_vector_copy(this + 3, v7, v4);
}

