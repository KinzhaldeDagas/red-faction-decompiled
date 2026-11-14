// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056ADD0 rf_oriented_box_contains_point
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Mover occupancy uses this point-only helper with authored dimensions. Inverse-rotated point is tested inclusively against half full size via0x56AD40. Do not use padded UE interaction extents or capsule overlap for this call.
// UNREALRED VERIFIED [mission-startup-20261020] Imported trigger shape correction: RFL loader/constructor retains FULL box dimensions; this containment helper halves them. UE BoxExtent must therefore be half the serialized size after axis/unit conversion. Previously importing full sizes as extents doubled each trigger dimension, including mover occupancy volumes.
bool __cdecl rf_oriented_box_contains_point(
        const float *point,
        const float *center,
        const float *orientation,
        const float *full_dimensions)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+8h] [ebp-54h] BYREF
  float v9[3]; // [esp+14h] [ebp-48h] BYREF
  float v10[3]; // [esp+20h] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-30h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+44h] [ebp-18h] BYREF
  int v14; // [esp+58h] [ebp-4h]

  if ( (dword_18091F4 & 1) == 0 )
  {
    dword_18091F4 |= 1u;
    rf_vector3_default_construct_noop(unk_18091E8);
    v14 = -1;
  }
  v4 = rf_vector_subtract(point, out_vector, center);
  rf_vector_copy(unk_18091E8, copy_result, v4);
  rf_matrix3_inverse_rotate_vector(unk_18091E8, (float *)orientation);
  if ( (dword_18091F4 & 2) == 0 )
  {
    dword_18091F4 |= 2u;
    v14 = 1;
    rf_vector3_default_construct_noop(unk_18091DC);
    v14 = -1;
  }
  if ( (dword_18091F4 & 4) == 0 )
  {
    dword_18091F4 |= 4u;
    v14 = 2;
    rf_vector3_default_construct_noop(unk_18091D0);
    v14 = -1;
  }
  v5 = rf_vector_multiply_scalar(full_dimensions, scaled_result, -0.5);
  rf_vector_copy(unk_18091DC, v10, v5);
  v6 = rf_vector_multiply_scalar(full_dimensions, v9, 0.5);
  rf_vector_copy(unk_18091D0, v8, v6);
  return rf_aabb_contains_point_inclusive(unk_18091E8, unk_18091DC, unk_18091D0);
}

