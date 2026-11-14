// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F1F0 rf_array24_set_count_reallocate_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Thiscall header(count0,capacity4,base8), signed requested count one DWORD,RET4; returns requested count. Nonzero (negative included) calls reallocator with requested capacity BEFORE count change; that helper copies FULL OLD count with no shrink clamp, so shrinking below old count can overrun new storage and spare records remain uninitialized. Zero count directly operator-deletes nonnull base but DOES NOT clear base or capacity, then stores count0. Thus zero resize leaves dangling backing pointer and old capacity: not reusable safe release; later append/destruction can use/free stale storage. No sign, allocation, null or exception rollback guard.
int __thiscall rf_array24_set_count_reallocate_unchecked(int this, int a2)
{
  if ( a2 )
  {
    rf_array24_reallocate_capacity_unchecked((int *)this, a2);
  }
  else if ( *(_DWORD *)(this + 8) )
  {
    operator delete(*(void **)(this + 8));
  }
  *(_DWORD *)this = a2;
  return a2;
}

