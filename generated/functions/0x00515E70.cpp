// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515E70 rf_geomod_room_face_attach
// UNREALRED VERIFIED [combat-native-query-20261104]: Detaches any previous room owner, appends to new Room face list, then expands all Room min/max components from the face epsilon bounds. This happens during initial loader attachment too, before517470 reads roomMinY+depth. Global solid/workspace face order is independent; room attachment must not implicitly append global order.
int __thiscall rf_geomod_room_face_attach(float *this, int a2)
{
  int result; // eax

  if ( *(_DWORD *)(a2 + 68) )
    rf_geomod_room_face_detach((int *)(*(_DWORD *)(a2 + 68) + 40), a2);
  *(_DWORD *)(a2 + 68) = this;
  rf_geomod_room_face_list_append((int *)this + 10, a2);
  *(this + 2) = rf_float_minimum_two_values(*(float *)(a2 + 16), *(this + 2));
  *(this + 3) = rf_float_minimum_two_values(*(float *)(a2 + 20), *(this + 3));
  *(this + 4) = rf_float_minimum_two_values(*(float *)(a2 + 24), *(this + 4));
  *(this + 5) = rf_float_maximum_two_values(*(float *)(a2 + 28), *(this + 5));
  *(this + 6) = rf_float_maximum_two_values(*(float *)(a2 + 32), *(this + 6));
  *(this + 7) = rf_float_maximum_two_values(*(float *)(a2 + 36), *(this + 7));
  return result;
}

