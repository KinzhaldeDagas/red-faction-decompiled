// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556FB0 rf_geomod_spatial_node_finalize_bounds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): If intrusive face list24 nonempty, initializes node min0/max12 from first face bounds16/28, then componentwise-unions every face including first through independent min/max helper5B13E0 and spatial next link Face88. Does not include child bounds. Empty face list zeros BOTH extrema to origin. Return is incidental last face-next/vector-copy value.
float *__thiscall rf_geomod_spatial_node_finalize_bounds(float *this)
{
  float *result; // eax
  float v3[3]; // [esp+4h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-10h] BYREF
  float *first_dword; // [esp+1Ch] [ebp-4h]

  first_dword = (float *)rf_receiver_get_first_dword(this + 6);
  if ( first_dword )
  {
    rf_vector_copy(this, copy_result, first_dword + 4);
    result = rf_vector_copy(this + 3, v3, first_dword + 7);
    while ( first_dword )
    {
      rf_aabb_union_componentwise_in_place(this, this + 3, first_dword + 4, first_dword + 7);
      result = (float *)rf_face_next_spatial_node_link((int)first_dword);
      first_dword = result;
    }
  }
  else
  {
    rf_vector3_zero_return_destination(this);
    return rf_vector3_zero_return_destination(this + 3);
  }
  return result;
}

