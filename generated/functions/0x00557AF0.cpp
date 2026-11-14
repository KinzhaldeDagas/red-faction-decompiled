// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557AF0 rf_geomod_spatial_node_pool_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Initializes5000 embedded40-byte nodes into ascending free list, lastNULL. Sets freeCount5000, freeHead=descriptor base, copies supplied tag at200004, zeroes heap count, heap peak, current active and resettable active peak. Record first DWORD overwritten by next link; other record bytes untouched. Reinitializing a live pool loses outstanding/free spill bookkeeping.
_DWORD *__thiscall rf_geomod_spatial_node_pool_construct(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 50001) = a2;
  *(this + 50000) = 0;
  *(this + 50002) = 0;
  *(this + 50003) = 0;
  *(this + 50004) = 0;
  *(this + 50006) = 0;
  *(this + 50005) = 0;
  *(this + 50003) = 5000;
  *(this + 50000) = this;
  for ( i = 0; i < 4999; ++i )
    *(this + 10 * i) = this + 10 * i + 10;
  *(this + 10 * i) = 0;
  return this;
}

