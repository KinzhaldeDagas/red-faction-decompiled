// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595C40 rf_scene_point_track_bind_definition
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall runtime record and definition pointer. Zeroes vector runtime+24, copies definition position+160 to runtime+12; clears runtime flags bits28..31, sets scalar runtime+36=1, stores definition pointer+0. Allocates type0 scene-point pool slot with runtime position/scalar and definition scalar fields+144,+148,+152,+156, stores returned index at runtime+56. Does not initialize runtime+4 or low28 flag bits, nor release an older pool slot before rebinding. Returns allocation index, potentially-1.
int __thiscall rf_scene_point_track_bind_definition(float *this, int a2)
{
  int result; // eax
  float copy_result[3]; // [esp+18h] [ebp-Ch] BYREF

  rf_vector3_zero_return_destination(this + 6);
  rf_vector_copy(this + 3, copy_result, (const float *)(a2 + 160));
  *((_DWORD *)this + 2) &= ~0x20000000u;
  *((_DWORD *)this + 2) &= ~0x10000000u;
  *((_DWORD *)this + 2) &= ~0x40000000u;
  *((_DWORD *)this + 2) &= ~0x80000000;
  *(this + 9) = 1.0;
  *(_DWORD *)this = a2;
  result = rf_scene_point_pool_allocate_type0_zero_channel64(
             this + 3,
             *(this + 9),
             *(float *)(*(_DWORD *)this + 144),
             *(float *)(*(_DWORD *)this + 148),
             *(float *)(*(_DWORD *)this + 152),
             *(float *)(*(_DWORD *)this + 156));
  *((_DWORD *)this + 14) = result;
  return result;
}

