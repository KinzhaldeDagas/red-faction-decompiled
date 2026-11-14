// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536030 sub_536030
// UNREALRED VERIFIED [finite-split-20261028] Copies one six-dword / 24-byte finite intersection record. Persisted local type RFGeomodFiniteIntersectionRecord records verified pointer/pointer/xyz/scalar layout; it is a transient Boolean workspace record, not saved GeoMod operation schema.
void *__thiscall sub_536030(void *this, int a2)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  *(_DWORD *)this = *(_DWORD *)a2;
  *((_DWORD *)this + 1) = *(_DWORD *)(a2 + 4);
  rf_vector_copy((float *)this + 2, copy_result, (const float *)(a2 + 8));
  *((float *)this + 5) = *(float *)(a2 + 20);
  return this;
}

