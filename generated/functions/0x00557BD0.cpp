// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557BD0 rf_geomod_spatial_node_pool_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Drains ONLY free list. Computes signed32(pointer-base)/40 via CDQ/IDIV, truncating toward0 and operator-deletes entries whose quotient<0 OR quotient>=5000 (separate signed branches), decrementing heapCount; embedded records skipped. Outstanding active heap records are not found or freed. Does not reconcile free/current/peak counters as head drains; no destructor invocation for faces/nodes and no cycle/range validation.
_DWORD *__thiscall rf_geomod_spatial_node_pool_destroy(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 50000) )
      break;
    v3 = (*(this + 50000) - (int)this) / 40;
    v4 = (_DWORD *)*(this + 50000);
    *(this + 50000) = *v4;
    if ( v3 >= 0x1388 )
    {
      operator delete(v4);
      --*(this + 50002);
    }
  }
  return result;
}

