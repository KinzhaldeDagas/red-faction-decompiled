// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055B2A0 rf_matrix3_rebuild_basis_from_forward_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX source plus output. Unchecked-normalizes source forward row24. Chooses temporary up from normalized source up if its length>0, else cross(forward,sourceRight) if right length>0, else +Z for purely Y forward or +Y otherwise. Sets right=cross(up,forward), up=cross(forward,right), copies temporary matrix to output. Final right/up are NOT normalized, so not guaranteed orthonormal even with valid nonparallel source axes. Zero forward unguarded. Staging permits output==source; EAX output bits.
int __thiscall rf_matrix3_rebuild_basis_from_forward_to_output(float *this, int a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v9[3]; // [esp+10h] [ebp-A4h] BYREF
  float v10[3]; // [esp+1Ch] [ebp-98h] BYREF
  float v11[3]; // [esp+28h] [ebp-8Ch] BYREF
  float v12[3]; // [esp+34h] [ebp-80h] BYREF
  float v13[3]; // [esp+40h] [ebp-74h] BYREF
  float v14[3]; // [esp+4Ch] [ebp-68h] BYREF
  float v15[3]; // [esp+58h] [ebp-5Ch] BYREF
  float v16[3]; // [esp+64h] [ebp-50h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-44h] BYREF
  float v18[3]; // [esp+7Ch] [ebp-38h] BYREF
  float v19[3]; // [esp+88h] [ebp-2Ch] BYREF
  float v20[3]; // [esp+94h] [ebp-20h] BYREF
  float destination[3]; // [esp+A0h] [ebp-14h] BYREF
  float v22; // [esp+ACh] [ebp-8h]
  float v23; // [esp+B0h] [ebp-4h]

  rf_matrix3_construct((char *)v19);
  v2 = rf_vector3_normalized_copy_unchecked(this + 6, v18);
  rf_vector_copy(destination, copy_result, v2);
  v22 = rf_vector3_length(this + 3);
  v23 = rf_vector3_length(this);
  if ( v22 > 0.0 )
  {
    v4 = rf_vector3_normalized_copy_unchecked(this + 3, v14);
    rf_vector_copy(v20, v13, v4);
  }
  else if ( v23 > 0.0 )
  {
    v3 = rf_vector_cross(destination, v16, this);
    rf_vector_copy(v20, v15, v3);
  }
  else if ( destination[0] == 0.0 && destination[2] == 0.0 && destination[1] != 0.0 )
  {
    rf_vector3_set_components_thiscall(v20, 0.0, 0.0, 1.0);
  }
  else
  {
    rf_vector3_set_components_thiscall(v20, 0.0, 1.0, 0.0);
  }
  v5 = rf_vector_cross(v20, v12, destination);
  rf_vector_copy(v19, v11, v5);
  v6 = rf_vector_cross(destination, v10, v19);
  rf_vector_copy(v20, v9, v6);
  rf_matrix3_copy_construct(a2, v19);
  return a2;
}

