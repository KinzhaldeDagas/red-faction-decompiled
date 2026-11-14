// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF5B0 rf_v3c_asset_collide_skinned_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Thiscall(asset,characterInstance,query,hit,resetByte). ANY nonzero reset byte sets fraction1/tag0. Prepares working start80/delta92 from input48/60: flags2 copies directly,otherwise subtracts reference position0 and row-transforms through matrix12 into WORKING fields only;does not set flags2 or alter input fields. Calls5CF6A0. No validation,output point/normal world conversion or restored scratch state.
char __thiscall rf_v3c_asset_collide_skinned_wrapper(void *this, void *a2, void *rhs, void *a4, unsigned __int8 a5)
{
  float *v5; // eax
  float *v6; // eax
  float v9[3]; // [esp+4h] [ebp-4Ch] BYREF
  float v10[3]; // [esp+10h] [ebp-40h] BYREF
  float v11[3]; // [esp+1Ch] [ebp-34h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-28h] BYREF
  float v13[3]; // [esp+34h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+40h] [ebp-10h] BYREF
  char v15; // [esp+4Fh] [ebp-1h]

  v15 = 0;
  if ( a5 )
  {
    *(float *)a4 = 1.0;
    *((_DWORD *)a4 + 7) = 0;
  }
  if ( (*((_DWORD *)rhs + 19) & 2) != 0 )
  {
    rf_vector_copy((float *)rhs + 20, copy_result, (const float *)rhs + 12);
    rf_vector_copy((float *)rhs + 23, v13, (const float *)rhs + 15);
  }
  else
  {
    v5 = rf_vector_subtract((const float *)rhs + 12, out_vector, (const float *)rhs);
    rf_vector_copy((float *)rhs + 20, v11, v5);
    rf_matrix3_inverse_rotate_vector((float *)rhs + 20, (float *)rhs + 3);
    v6 = rf_vector3_transform_by_matrix_rows((float *)rhs + 15, v10, (float *)rhs + 3);
    rf_vector_copy((float *)rhs + 23, v9, v6);
  }
  return rf_v3c_asset_collide_skinned_meshes(this, a2, rhs, a4);
}

