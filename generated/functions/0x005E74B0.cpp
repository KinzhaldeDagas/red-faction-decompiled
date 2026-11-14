// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E74B0 rf_byte_arena_release_owned_chunks
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): ECX arena receiver. If OWN flag24&01 clear,no writes/free and returns receiver bits. If set,walks linked chunks from head0,loads next from firstDWORD BEFORE deleting each,then head0=0,data4=0,clears ONLY OWN01 in flags24,returns resulting flags DWORD. Leaves cursor8,capacity12,remaining16,lastAllocation20 and GROW02 unchanged. Therefore header is not a safe reset allocator after release:allocation helper can use stale remaining/cursor. No cycle/double-free checks. Prototype normalized from raw fastcall integer receiver to thiscall opaque header.
unsigned int __thiscall rf_byte_arena_release_owned_chunks(void *this)
{
  unsigned int result; // eax
  _DWORD *i; // [esp+8h] [ebp-8h]
  _DWORD *v4; // [esp+Ch] [ebp-4h]

  result = (unsigned int)this;
  if ( (*((_DWORD *)this + 6) & 1) != 0 )
  {
    for ( i = *(_DWORD **)this; i; i = v4 )
    {
      v4 = (_DWORD *)*i;
      operator delete(i);
    }
    *(_DWORD *)this = 0;
    *((_DWORD *)this + 1) = 0;
    result = *((_DWORD *)this + 6) & 0xFFFFFFFE;
    *((_DWORD *)this + 6) = result;
  }
  return result;
}

