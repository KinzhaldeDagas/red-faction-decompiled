// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D0FE0 rf_physics_shape_sweep_against_model
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start,end,shape,target position,target matrix,model wrapper,INOUT physics hit. Model-query position0/matrix12 copied from target, direction60=end-start,flags76=0; result fraction0 seeded ONCE from caller hit24. For each24-byte sphere in shape collection252, query radius72=sphere radius12 and query start48=rotate(offset,shape matrix116)+start. Calls model collide-all initializeByte0, preserving shared fraction bound across spheres rather than resetting to1. Any nonzero hit copies fraction to caller24; result normal16 rotated by target matrix then unchecked-normalized into caller12; result point4 rotated and translated by target position into caller0. Clears caller DWORD60, copies RAW model-result DWORD28 into
// caller64. Does not fill material28,scalar32,velocity36,UID48,raw material52 or liquid56; no own comparison/clamp/normal guard, wrapper NULL check or pointer/collection validation. ReturnsAL1 on any delegated hit; otherwise leaves caller hit untouched.
char __cdecl rf_physics_shape_sweep_against_model(
        float *rhs,
        float *lhs,
        int a3,
        float *source,
        float *a5,
        _DWORD *a6,
        float *a7)
{
  float *v7; // eax
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  float v11[3]; // [esp+0h] [ebp-D8h] BYREF
  float v12[3]; // [esp+Ch] [ebp-CCh] BYREF
  float v13[3]; // [esp+18h] [ebp-C0h] BYREF
  float v14[3]; // [esp+24h] [ebp-B4h] BYREF
  float out_vector[3]; // [esp+30h] [ebp-A8h] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-9Ch] BYREF
  float destination[3]; // [esp+48h] [ebp-90h] BYREF
  float v18[9]; // [esp+54h] [ebp-84h] BYREF
  float v19[3]; // [esp+78h] [ebp-60h] BYREF
  float v20[11]; // [esp+84h] [ebp-54h] BYREF
  float v21; // [esp+B0h] [ebp-28h] BYREF
  float v22[3]; // [esp+B4h] [ebp-24h] BYREF
  float v23[4]; // [esp+C0h] [ebp-18h] BYREF
  int i; // [esp+D0h] [ebp-8h]
  char v25; // [esp+D7h] [ebp-1h]

  rf_model_collision_query_construct_noop((char *)destination);
  rf_model_collision_result_construct_noop((int)&v21);
  v25 = 0;
  v20[4] = 0.0;
  rf_matrix3_copy(v18, a5);
  rf_vector_copy(destination, copy_result, source);
  v7 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v20, v14, v7);
  v21 = a7[6];
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a3 + 252));
    if ( i >= first_dword )
      break;
    v20[3] = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i) + 12);
    element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i);
    rf_vector_copy(v19, v13, element_address_unchecked);
    rf_vector_rotate_by_matrix3(v19, (float *)(a3 + 116));
    rf_vector_accumulate(v19, rhs);
    if ( rf_model_handle_collide_all_adapter(a6, (int)destination, (int)&v21, 0) )
    {
      v25 = 1;
      a7[6] = v21;
      rf_vector_copy(a7 + 3, v12, v23);
      rf_vector_rotate_by_matrix3(a7 + 3, a5);
      rf_vector_normalize_reciprocal_sqrt(a7 + 3);
      rf_vector_copy(a7, v11, v22);
      rf_vector_rotate_by_matrix3(a7, a5);
      rf_vector_accumulate(a7, source);
      a7[15] = 0.0;
      a7[16] = v23[3];
    }
  }
  return v25;
}

