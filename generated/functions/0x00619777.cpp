// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619777 __rt_probe_read4@4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(const pointer),RET4,int Boolean. SEH4
// original65EF20 arms try0; execute EXACT one DWORD memory load MOV EAX,[input],discard loaded value,set result1. No alignment/NULL/range precheck or page-by-page validation; NULL
// may succeed if mapped,unaligned/cross-page behavior delegated CPU/OS. Filter619795 returns1 ONLY for codeC0000005; handler6197A9 restoresESP,result0. Any other exception returns
// filter0/continue-search,not necessarily Boolean false. Normal disarm/SEH epilog,return0/1. No writes to probed bytes,locking,retained copy or guarantee of later accessibility.
// Flattened pseudocode constant1 omits the actual memory read and fault path. Used by longjmp for only format DWORD+20h,not full jump-buffer validation.
int __stdcall _rt_probe_read4(const void *a1)
{
  return 1;
}

