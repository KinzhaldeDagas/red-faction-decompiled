// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609939 crt_flush_all_streams_mode_one
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed args/plain RET. Push literal1, cdecl60980C _flsall, POP ECX stack cleanup, return unmodified delegate EAX. No stream enumeration, validity/lock
// handling or result normalization in this wrapper; helper owns mode1 behavior. Does not itself call fclose or release stream allocations.
int crt_flush_all_streams_mode_one()
{
  return flsall(1);
}

