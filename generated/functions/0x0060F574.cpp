// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F574 crt_initialize_sse2_information_cache
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed args/plain RET. Call60F512 __get_sse2_info, store returned rawDWORD into2021F64, then XOR EAX,EAX and return0. No own CPUID probe/feature mask
// interpretation, once guard, comparison or SSE2 enable instruction; producer owns feature detection. Repeated calls overwrite cache. Stored value and returned status are different.
int crt_initialize_sse2_information_cache()
{
  unk_2021F64 = _get_sse2_info();
  return 0;
}

