// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566D30 rf_model_handle88_pool_allocate_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Thiscall pool descriptor. Control base88000:freeHead0,tag4,heapCount8,freeCount12,peakHeap16,peakActive20,currentActive24. Pops free node/decrementsfreeCount; empty list returnsNULL if heap spill disabled,otherwise operator-new88bytes/increments heap counters. Successful allocation increments active/peak. No object initialization, zeroing, synchronization or null-check after heap allocator.
_DWORD *__thiscall rf_model_handle88_pool_allocate_raw(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 22000) )
  {
    v3 = (_DWORD *)*(this + 22000);
    *(this + 22000) = *v3;
    --*(this + 22003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled[0] )
      return nullptr;
    v3 = operator new(0x58u);
    if ( ++*(this + 22002) > *(this + 22004) )
      *(this + 22004) = *(this + 22002);
  }
  if ( ++*(this + 22006) > *(this + 22005) )
    *(this + 22005) = *(this + 22006);
  return v3;
}

