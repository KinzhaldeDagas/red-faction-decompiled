// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566EA0 rf_model_handle88_pool_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): ECX descriptor plus caller tag word,RET4. Builds1000 embedded88byte records into ascending free list,lastNULL. Control base88000:freeHead=base,tag+4=callerWord,freeCount+12=1000,heapCount+8/peakHeap+16/peakActive+20/currentActive+24=0. Only record DWORD0 links initialized; other record bytes unchanged. Reinitializing live pool discards prior free/spill bookkeeping; returns descriptor.
_DWORD *__thiscall rf_model_handle88_pool_construct(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 22001) = a2;
  *(this + 22000) = 0;
  *(this + 22002) = 0;
  *(this + 22003) = 0;
  *(this + 22004) = 0;
  *(this + 22006) = 0;
  *(this + 22005) = 0;
  *(this + 22003) = 1000;
  *(this + 22000) = this;
  for ( i = 0; i < 999; ++i )
    *(this + 22 * i) = this + 22 * i + 22;
  *(this + 22 * i) = 0;
  return this;
}

