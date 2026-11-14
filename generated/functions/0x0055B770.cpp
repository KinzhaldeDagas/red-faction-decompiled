// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B770 rf_matrix3_rebuild_basis_from_forward_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Same basis policy as55B2A0 using temporaries, then copies back to receiver: unchecked-normalized forward, preferred normalized original up or forward cross original right, fallback+Z for pureY forward else+Y; right=up cross forward, up=forward cross right. Final right/up not normalized. Can retain sin-angle scale or produce zero/NaN basis. Returns matrix-copy destination bits.
int __thiscall rf_matrix3_rebuild_basis_from_forward_in_place(float *this)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v8[3]; // [esp+10h] [ebp-A4h] BYREF
  float v9[3]; // [esp+1Ch] [ebp-98h] BYREF
  float v10[3]; // [esp+28h] [ebp-8Ch] BYREF
  float v11[3]; // [esp+34h] [ebp-80h] BYREF
  float v12[3]; // [esp+40h] [ebp-74h] BYREF
  float v13[3]; // [esp+4Ch] [ebp-68h] BYREF
  float v14[3]; // [esp+58h] [ebp-5Ch] BYREF
  float v15[3]; // [esp+64h] [ebp-50h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-44h] BYREF
  float v17[3]; // [esp+7Ch] [ebp-38h] BYREF
  float v18[3]; // [esp+88h] [ebp-2Ch] BYREF
  float v19[3]; // [esp+94h] [ebp-20h] BYREF
  float destination[3]; // [esp+A0h] [ebp-14h] BYREF
  float v21; // [esp+ACh] [ebp-8h]
  float v22; // [esp+B0h] [ebp-4h]

  rf_matrix3_construct((char *)v18);
  v1 = rf_vector3_normalized_copy_unchecked(this + 6, v17);
  rf_vector_copy(destination, copy_result, v1);
  v21 = rf_vector3_length(this + 3);
  v22 = rf_vector3_length(this);
  if ( v21 > 0.0 )
  {
    v3 = rf_vector3_normalized_copy_unchecked(this + 3, v13);
    rf_vector_copy(v19, v12, v3);
  }
  else if ( v22 > 0.0 )
  {
    v2 = rf_vector_cross(destination, v15, this);
    rf_vector_copy(v19, v14, v2);
  }
  else if ( destination[0] == 0.0 && destination[2] == 0.0 && destination[1] != 0.0 )
  {
    rf_vector3_set_components_thiscall(v19, 0.0, 0.0, 1.0);
  }
  else
  {
    rf_vector3_set_components_thiscall(v19, 0.0, 1.0, 0.0);
  }
  v4 = rf_vector_cross(v19, v11, destination);
  rf_vector_copy(v18, v10, v4);
  v5 = rf_vector_cross(destination, v9, v18);
  rf_vector_copy(v19, v8, v5);
  return rf_matrix3_copy(this, v18);
}

