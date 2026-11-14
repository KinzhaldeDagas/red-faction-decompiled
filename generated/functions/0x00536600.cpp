// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536600 rf_geomod_face_pool_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall facePool, no stack args, return receiverEAX after chain empty. Repeatedly pop EVERY freeHead record at pool+2880000, advancing head BEFORE potential delete. Compute signed quotient q=(32-bit signed(record-pool))/96 with CDQ/IDIV truncating toward0; delete record iff q<0 OR q>=30000 (raw signed JL tests), decrement spillLive at+2880008 only on delete. Records with0<=q<30000 are just removed from chain. No alignment test: slightly-below-base pointers within95bytes can quotient0. Does not visit active records absent from chain, zero freeCount/currentActive/peak counters, invoke face payload destructors, or delete receiver. Static-exit wrapper is a caller, not a guarantee all spills were returned.
_DWORD *__thiscall rf_geomod_face_pool_destroy(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 720000) )
      break;
    v3 = (*(this + 720000) - (int)this) / 96;
    v4 = (_DWORD *)*(this + 720000);
    *(this + 720000) = *v4;
    if ( v3 >= 0x7530 )
    {
      operator delete(v4);
      --*(this + 720002);
    }
  }
  return result;
}

