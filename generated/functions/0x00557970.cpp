// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557970 rf_geomod_spatial_node_pool_allocate_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Pool has5000 embedded40-byte records; control DWORDs at record-array end200000:freeHead+0,tag+4,heapCount+8,freeCount+12,peakHeap+16,peakActive+20,currentActive+24. Pops freeHead, decrements freeCount; when empty, returnsNULL if global heap-spill disabled, otherwise allocates40 bytes, increments heapCount/peakHeap. Successful allocation increments currentActive/peakActive. Freed heap spills are recycled into same free list and are not deleted here; no synchronization or counter-overflow checks.
_DWORD *__thiscall rf_geomod_spatial_node_pool_allocate_raw(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 50000) )
  {
    v3 = (_DWORD *)*(this + 50000);
    *(this + 50000) = *v3;
    --*(this + 50003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled[0] )
      return nullptr;
    v3 = operator new(0x28u);
    if ( ++*(this + 50002) > *(this + 50004) )
      *(this + 50004) = *(this + 50002);
  }
  if ( ++*(this + 50006) > *(this + 50005) )
    *(this + 50005) = *(this + 50006);
  return v3;
}

