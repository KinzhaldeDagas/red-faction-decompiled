// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00522F10 rf_world_decal_face_near_center
// UNREALRED VERIFIED [decal-projection-20261028]: Radius=max(dimensions)*0.5. Requires overlap between face AABB+16/+28 and center +/- radius box, calls0x51D480(face,center,temp), computes distance(temp,center), returns true only when distance<radius. Current decompiler x87 values obscure floating return from rf_vector_distance; comparison is strict. No abs of dimensions or metadata bounds validation.
bool __cdecl rf_world_decal_face_near_center(float *a1, float *a2)
{
  double v3; // st7
  float v4[3]; // [esp+Ch] [ebp-28h] BYREF
  int v5[3]; // [esp+18h] [ebp-1Ch] BYREF
  float v6; // [esp+24h] [ebp-10h]
  int v7[3]; // [esp+28h] [ebp-Ch] BYREF

  v6 = rf_float_maximum_two_values(a2[12], a2[13]);
  v6 = rf_float_maximum_two_values(v6, a2[14]);
  v6 = v6 * 0.5;
  rf_vector3_add_scalar_to_components(a2, (float *)v7, v6);
  rf_vector3_subtract_scalar_from_components(a2, (float *)v5, v6);
  if ( !rf_aabb_overlap_inclusive(a1 + 4, a1 + 7, (float *)v5, (float *)v7) )
    return 0;
  rf_vector3_default_construct_noop(v4);
  rf_geomod_face_closest_point_to_point(a1, a2, v4);
  v3 = rf_vector_distance(v4, a2);
  return v6 > v3;
}

