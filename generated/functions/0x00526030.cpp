// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526030 rf_decal_polygon_pool_drain_free_chain_and_delete_spills
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Thiscall pool, no stack args, plainRET returns pool. While freeHead at byte2664000(0x28A640) nonNULL, compute signed32 quotient q=(recordAddress-poolAddress)/1332 usingCDQ/IDIV, truncating towardzero; pop freeHead from record DWORD0. If q<0 OR q>=2000, operator-delete record then decrement pool DWORD2664008. Inline quotient0..1999 is popped but not deleted. No alignment test; pointer just below base by<1332 gives quotient0. Does not decrement freeCount2664012, change activeCount2664024, rebuild inline free chain, or release active records. Final freeHeadNULL; not a complete pool reinitializer or whole-pool delete.
_DWORD *__thiscall rf_decal_polygon_pool_drain_free_chain_and_delete_spills(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 666000) )
      break;
    v3 = (*(this + 666000) - (int)this) / 1332;
    v4 = (_DWORD *)*(this + 666000);
    *(this + 666000) = *v4;
    if ( v3 >= 0x7D0 )
    {
      operator delete(v4);
      --*(this + 666002);
    }
  }
  return result;
}

