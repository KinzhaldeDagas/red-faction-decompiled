// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519E60 rf_solid_finalize_bounds
// UNREALRED VERIFIED [combat-native-query-20261104]: Rebuilds world bounds from ALL solid vertices in vertex-array order, then expands min/max by0.0001RF. Point-room ray extent reads these expanded world bounds. Authored Room bounds are a different mutable owner and also expand on face attachment.
int __thiscall rf_solid_finalize_bounds(float *this)
{
  int result; // eax
  int first_dword; // eax
  float v4[3]; // [esp+8h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-14h] BYREF
  int i; // [esp+20h] [ebp-8h]
  float *source; // [esp+24h] [ebp-4h]

  result = rf_receiver_get_first_dword(this + 30);
  if ( result >= 1 )
  {
    source = *(float **)sub_552200((_DWORD *)this + 30, 0);
    rf_vector_copy(this + 18, copy_result, source);
    rf_vector_copy(this + 21, v4, source);
    for ( i = 1; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(this + 30);
      if ( i >= first_dword )
        break;
      source = *(float **)sub_552200((_DWORD *)this + 30, i);
      if ( *(this + 18) > (double)*source )
        *(this + 18) = *source;
      if ( *(this + 19) > (double)source[1] )
        *(this + 19) = source[1];
      if ( *(this + 20) > (double)source[2] )
        *(this + 20) = source[2];
      if ( *(this + 21) < (double)*source )
        *(this + 21) = *source;
      if ( *(this + 22) < (double)source[1] )
        *(this + 22) = source[1];
      if ( *(this + 23) < (double)source[2] )
        *(this + 23) = source[2];
    }
    rf_vector3_subtract_scalar_in_place(this + 18, 0.000099999997);
    rf_vector3_add_scalar_in_place(this + 21, 0.000099999997);
    return (int)rf_solid_bounding_sphere_rebuild(this);
  }
  return result;
}

