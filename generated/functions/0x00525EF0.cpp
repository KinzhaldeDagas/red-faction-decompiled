// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525EF0 rf_decal_polygon_pool_initialize
// UNREALRED VERIFIED [decal-face-links-20261028]: Initializes pool metadata after2000 inline1332-byte slots: stores caller tag at+2664004, clears spill/active/highwater counters, sets free count+2664012=2000 and free head+2664000=pool base. Writes each record first dword to next record, finalnull. Does not zero record payload or free previous heap spill allocations; returns pool.
_DWORD *__thiscall rf_decal_polygon_pool_initialize(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 666001) = a2;
  *(this + 666000) = 0;
  *(this + 666002) = 0;
  *(this + 666003) = 0;
  *(this + 666004) = 0;
  *(this + 666006) = 0;
  *(this + 666005) = 0;
  *(this + 666003) = 2000;
  *(this + 666000) = this;
  for ( i = 0; i < 1999; ++i )
    *(this + 333 * i) = this + 333 * i + 333;
  *(this + 333 * i) = 0;
  return this;
}

