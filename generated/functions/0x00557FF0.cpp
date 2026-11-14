// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557FF0 rf_geomod_vertex_pool_allocate_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Same fixed-pool policy as spatial allocator with50000 embedded44-byte records and control base2200000. Pops free list/decrements freeCount; empty list returnsNULL if heap spill disabled, otherwise allocates44 bytes and increments heapCount/peakHeap. Successful allocation increments currentActive/peakActive. Spill records are recycled on release; no allocation-success/null/overflow/synchronization checks beyond spill-enable branch.
_DWORD *__thiscall rf_geomod_vertex_pool_allocate_raw(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 550000) )
  {
    v3 = (_DWORD *)*(this + 550000);
    *(this + 550000) = *v3;
    --*(this + 550003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled[0] )
      return nullptr;
    v3 = operator new(0x2Cu);
    if ( ++*(this + 550002) > *(this + 550004) )
      *(this + 550004) = *(this + 550002);
  }
  if ( ++*(this + 550006) > *(this + 550005) )
    *(this + 550005) = *(this + 550006);
  return v3;
}

