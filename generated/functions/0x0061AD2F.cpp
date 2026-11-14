// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AD2F ___check_float_string
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI EDI=bufferPointerSlot*,
// ESI=unsignedCapacitySlot*, three caller-popped stack slots {raw usedCount,originalStackBuffer,heapFlagSlot*}, EAX Boolean. ONLY usedCount==capacity triggers growth (not >=);
// otherwise return1 without touching buffer/flag/capacity. If *bufferSlot==originalStackBuffer: calloc_crt(capacity,2), PUBLISH returned pointer into bufferSlot BEFORE NULL test.
// Failure0 leaves bufferSlot NULL, capacity/heapFlag unchanged, original stack pointer still in argument. Success set *heapFlagSlot=1 BEFORE memcpy(newBuffer,originalStackBuffer,OLD
// capacity bytes). If already heap-backed: recalloc_crt(oldBuffer,capacity,2); failure0 preserves old pointer/capacity/flag; success publish new pointer (does not rewrite heapFlag).
// On growth success shift capacity DWORD left1 modulo32; return1. Recalloc/calloc own zeroing/overflow/errno behavior delegated; no own NULL-slot checks, count>capacity handling,
// overflow/maximum/zero-capacity guard, terminator append or per-character copy. No own lock/exception cleanup. Initial allocation failure and later reallocation failure have
// intentionally different pointer-state effects.
int __usercall __check_float_string@<eax>(void **a1@<edi>, size_t *a2@<esi>, int a3, void *Src, _DWORD *a5)
{
  size_t v5; // eax
  void *v6; // eax
  void *v8; // eax

  v5 = *a2;
  if ( a3 == *a2 )
  {
    if ( *a1 == Src )
    {
      v6 = _calloc_crt(v5, 2u);
      *a1 = v6;
      if ( !v6 )
        return 0;
      *a5 = 1;
      memcpy(*a1, Src, *a2);
    }
    else
    {
      v8 = _recalloc_crt(*a1, v5, 2u);
      if ( !v8 )
        return 0;
      *a1 = v8;
    }
    *a2 *= 2;
  }
  return 1;
}

