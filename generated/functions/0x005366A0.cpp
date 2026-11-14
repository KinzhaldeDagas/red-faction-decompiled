// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005366A0 rf_geomod_corner_pool_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall cornerPool, no stack args, return receiverEAX after chain empty. Pop EVERY freeHead at+4200000(401640), advancing before delete. Signed CDQ/IDIV computes q=(32-bit signed(record-pool))/28 truncating toward0; delete iff q<0 OR q>=150000, decrement spillLive+4200008 only when deleted. In-range quotient records are removed without delete. No record-alignment validation (slightly below base within27bytes can quotient0). Does not reach live records outside free chain, adjust freeCount/currentActive/peaks, destroy corner payloads/vertices, or delete receiver. loc_401640 is receiver-relative offset, not code.
_DWORD *__thiscall rf_geomod_corner_pool_destroy(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(_DWORD *)((char *)&loc_401640 + (_DWORD)this) )
      break;
    v3 = (*(_DWORD *)((char *)&loc_401640 + (_DWORD)this) - (int)this) / 28;
    v4 = *(_DWORD **)((char *)&loc_401640 + (_DWORD)this);
    *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) = *v4;
    if ( v3 >= 0x249F0 )
    {
      operator delete(v4);
      --*(this + 1050002);
    }
  }
  return result;
}

