// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525D90 rf_decal_polygon_pool_release
// UNREALRED VERIFIED [decal-updates-20261028]: Pushes caller record onto free list at pool+2664000 using record first dword as next. Increments free count+2664012, decrements active count+2664024, returns pool. Does not operator-delete spill records, clear payload or validate ownership/double release.
_DWORD *__thiscall rf_decal_polygon_pool_release(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 666000);
  *(this + 666000) = a2;
  ++*(this + 666003);
  --*(this + 666006);
  return this;
}

