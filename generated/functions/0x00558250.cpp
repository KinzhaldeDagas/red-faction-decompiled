// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558250 rf_geomod_vertex_pool_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Drains only free list; signed32(pointer-base)/44 via CDQ/IDIV, truncating toward0; separate signed quotient<0 OR quotient>=50000 branches classifies external spill records for operator delete and decrements heapCount. Outstanding active spill allocations not discovered/freed. Leaves free/current/peak counters unreconciled and does not release vertex incident-face arrays. No cycle/double-free/foreign-pointer protection.
_DWORD *__thiscall rf_geomod_vertex_pool_destroy(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 550000) )
      break;
    v3 = (*(this + 550000) - (int)this) / 44;
    v4 = (_DWORD *)*(this + 550000);
    *(this + 550000) = *v4;
    if ( v3 >= 0xC350 )
    {
      operator delete(v4);
      --*(this + 550002);
    }
  }
  return result;
}

