// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7740 rf_byte_arena_used_capacity_estimate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall no stack args. Starts currentCapacity12-remaining16,then dereferences head0 to its next link and adds CURRENT capacity12 for every previous chunk. Returns wrapped32-bit total,including alignment consumption and treating all prior chunks as full/current-size,not actual requested-byte sum or per-chunk capacity. Unconditionally dereferences head,so empty/bare borrowed arena with NULL head faults. No cycle/ownership/overflow checks.
unsigned int __thiscall rf_byte_arena_used_capacity_estimate(const void *this)
{
  _DWORD *i; // [esp+4h] [ebp-8h]
  unsigned int v3; // [esp+8h] [ebp-4h]

  v3 = *((_DWORD *)this + 3) - *((_DWORD *)this + 4);
  for ( i = **(_DWORD ***)this; i; i = (_DWORD *)*i )
    v3 += *((_DWORD *)this + 3);
  return v3;
}

