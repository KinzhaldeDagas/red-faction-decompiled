// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D1180 rf_physics_shape_sweep_against_transformed_solid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start,end,shape,target origin,target matrix,solid,INOUT physics hit. Converts start/end by subtracting target origin then inverse-rotating target matrix. Solid query flags80=4; adds0x100 ONLY when ORDERED shape float248<double0.05000000074505806 (NaN skips). Explicit identity query matrix16 and zero position4, direction64=transformedEnd-transformedStart; result fraction4 seeded once from caller24. For each sphere collection252/24-byte stride, radius76=record12; start52=rotate(record offset,SHAPE matrix116)+ALREADY target-local start. No additional target inverse-rotation of that offset in this function. Calls solid sweep initializeByte0; backend resets result count0/edge32/face36 each call but preserves
// fraction bound. Signed count>0 copies bound to caller24, local normal20 rotated by target matrix to caller12 WITHOUT extra normalization, local point8 rotated/translated into caller0; copies face pointer result36 to caller60, zeros64. Other physics-hit metadata untouched. No own finite/NULL/radius/index guards or global cache build/clear; returnsAL1 on any positive hit count.
char __cdecl rf_physics_shape_sweep_against_transformed_solid(
        float *lhs,
        float *a2,
        float *a3,
        float *rhs,
        float *a5,
        char *a6,
        float *a7)
{
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  float v13[3]; // [esp+0h] [ebp-140h] BYREF
  float v14[3]; // [esp+Ch] [ebp-134h] BYREF
  float v15[3]; // [esp+18h] [ebp-128h] BYREF
  float v16[3]; // [esp+24h] [ebp-11Ch] BYREF
  float v17[3]; // [esp+30h] [ebp-110h] BYREF
  float v18[3]; // [esp+3Ch] [ebp-104h] BYREF
  float v19[3]; // [esp+48h] [ebp-F8h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-ECh] BYREF
  float out_vector[3]; // [esp+60h] [ebp-E0h] BYREF
  float destination[3]; // [esp+6Ch] [ebp-D4h] BYREF
  char v23[4]; // [esp+78h] [ebp-C8h] BYREF
  float v24[3]; // [esp+7Ch] [ebp-C4h] BYREF
  float v25[9]; // [esp+88h] [ebp-B8h] BYREF
  float v26[3]; // [esp+ACh] [ebp-94h] BYREF
  float v27[4]; // [esp+B8h] [ebp-88h] BYREF
  int v28; // [esp+C8h] [ebp-78h]
  int v29; // [esp+ECh] [ebp-54h] BYREF
  float v30; // [esp+F0h] [ebp-50h]
  float v31[3]; // [esp+F4h] [ebp-4Ch] BYREF
  float source[5]; // [esp+100h] [ebp-40h] BYREF
  int i; // [esp+114h] [ebp-2Ch]
  float v34[3]; // [esp+118h] [ebp-28h] BYREF
  _BYTE v35[12]; // [esp+124h] [ebp-1Ch] BYREF
  _BYTE v36[15]; // [esp+130h] [ebp-10h] BYREF
  char v37; // [esp+13Fh] [ebp-1h]

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v34);
  rf_vector3_default_construct_noop(v36);
  rf_vector3_default_construct_noop(v35);
  rf_solid_collision_query_construct_clear_face_hint(v23);
  rf_solid_collision_result_construct_noop((int)&v29);
  v37 = 0;
  v7 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v7);
  rf_matrix3_inverse_rotate_vector(destination, a5);
  v8 = rf_vector_subtract(a2, v19, rhs);
  rf_vector_copy(v34, v18, v8);
  rf_matrix3_inverse_rotate_vector(v34, a5);
  v28 = 4;
  if ( a3[62] < 0.05000000074505806 )
    v28 |= 0x100u;
  rf_identity_orientation_matrix(v25);
  rf_vector3_zero_return_destination(v24);
  v9 = rf_vector_subtract(v34, v17, destination);
  rf_vector_copy(v27, v16, v9);
  v30 = a7[6];
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(a3 + 63);
    if ( i >= first_dword )
      break;
    v27[3] = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)a3 + 63, i) + 12);
    element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)a3 + 63, i);
    rf_vector_copy(v26, v15, element_address_unchecked);
    rf_vector_rotate_by_matrix3(v26, a3 + 29);
    rf_vector_accumulate(v26, destination);
    rf_world_collision_sweep(a6, (int)v23, (int)&v29, 0);
    if ( v29 > 0 )
    {
      v37 = 1;
      a7[6] = v30;
      rf_vector_copy(a7 + 3, v14, source);
      rf_vector_rotate_by_matrix3(a7 + 3, a5);
      rf_vector_copy(a7, v13, v31);
      rf_vector_rotate_by_matrix3(a7, a5);
      rf_vector_accumulate(a7, rhs);
      a7[15] = source[4];
      a7[16] = 0.0;
    }
  }
  return v37;
}

