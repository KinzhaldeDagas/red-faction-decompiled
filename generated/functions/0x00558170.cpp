// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558170 rf_geomod_vertex_pool_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Initializes50000 embedded44-byte records into ascending free list, lastNULL; freeHead=base, freeCount50000. Copies caller tag at2200004 and zeros heap count, heap peak, currentActive and resettable peakActive. Other vertex bytes uninitialized; reinitializing live pool loses existing spill bookkeeping.
_DWORD *__thiscall rf_geomod_vertex_pool_construct(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 550001) = a2;
  *(this + 550000) = 0;
  *(this + 550002) = 0;
  *(this + 550003) = 0;
  *(this + 550004) = 0;
  *(this + 550006) = 0;
  *(this + 550005) = 0;
  *(this + 550003) = 50000;
  *(this + 550000) = this;
  for ( i = 0; i < 49999; ++i )
    *(this + 11 * i) = this + 11 * i + 11;
  *(this + 11 * i) = 0;
  return this;
}

