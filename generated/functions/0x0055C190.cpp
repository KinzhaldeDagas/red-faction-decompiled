// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C190 rf_orientation_from_forward_and_up_hint
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX destination plus forward and upHint. Unchecked-normalizes forward into row24; copies upHint into row12 and normalizes with559280 which returns original length even if zero normalization already wrote NaNs. If returned length==0, falls back55BF00(forward). Otherwise right=up cross forward, normalize/get length, same zero fallback, then up=forward cross right. NaN returns do not equal0 and can propagate. No pointer/finite guard; normal-path EAX is up-row copy destination bits.
float *__thiscall rf_orientation_from_forward_and_up_hint(float *this, float *a2, float *source)
{
  float *v3; // eax
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-54h] BYREF
  float v9[3]; // [esp+10h] [ebp-48h] BYREF
  float v10[3]; // [esp+1Ch] [ebp-3Ch] BYREF
  float v11[3]; // [esp+28h] [ebp-30h] BYREF
  float v12[3]; // [esp+34h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-18h] BYREF
  float v14[3]; // [esp+4Ch] [ebp-Ch] BYREF

  v3 = rf_vector3_normalized_copy_unchecked(a2, v14);
  rf_vector_copy(this + 6, copy_result, v3);
  rf_vector_copy(this + 3, v12, source);
  if ( rf_vector3_normalize_return_length(this + 3) == 0.0 )
    return rf_orientation_matrix_from_normalized_direction(this, a2);
  v5 = rf_vector_cross(this + 3, v11, this + 6);
  rf_vector_copy(this, v10, v5);
  if ( rf_vector3_normalize_return_length(this) == 0.0 )
    return rf_orientation_matrix_from_normalized_direction(this, a2);
  v6 = rf_vector_cross(this + 6, v9, this);
  return rf_vector_copy(this + 3, v8, v6);
}

