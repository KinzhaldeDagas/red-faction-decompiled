// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606C3D _V6_HeapAlloc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(unsigned requested size), returns pointer from
// sbh_alloc_block orNULL. Initialize resultNULL; if size>LIVE2021F4C unsigned returnNULL without lock/allocation. Otherwise lock4, arm SEH try0, call sbh_alloc_block(size), save
// pointer, then normal/unwind finally unlock4; restore SEH frame and return saved result. Verified EH4 scope65E7C0 has enclosing-2/filter0/handler606C83. No Windows heap fallback,
// zero-size normalization, memset, errno or new-handler retry here; caller malloc supplies fallback policy.
_DWORD *__cdecl V6_HeapAlloc(unsigned int a1)
{
  _DWORD *v2; // [esp+10h] [ebp-1Ch]

  v2 = nullptr;
  if ( a1 <= unk_2021F4C )
  {
    _lock(4);
    v2 = __sbh_alloc_block(a1);
    _unlock(4);
  }
  return v2;
}

