// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566F80 rf_model_handle88_pool_destroy_free_nodes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): Drains only freeHead at88000. For each pointer computes SIGNED32 byte difference/88 using CDQ/IDIV,truncating toward0. Separate signed branches delete when quotient<0 OR quotient>=1000 and heapCount88008 decrement,embedded records skipped. Active/outstanding heap records not discovered or freed. Does not destroy handle-owned instances/materials or reconcile free/active/peak counters; no range/cycle/ownership checks. Returns descriptor.
_DWORD *__thiscall rf_model_handle88_pool_destroy_free_nodes(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 22000) )
      break;
    v3 = (*(this + 22000) - (int)this) / 88;
    v4 = (_DWORD *)*(this + 22000);
    *(this + 22000) = *v4;
    if ( v3 >= 0x3E8 )
    {
      operator delete(v4);
      --*(this + 22002);
    }
  }
  return result;
}

