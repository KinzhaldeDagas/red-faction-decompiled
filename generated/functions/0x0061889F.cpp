// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061889F ___set_fpsr_sse2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl raw desired MXCSR DWORD,void (old int0 result
// incidental; sole original caller ignores EAX). Always SEH4 prolog/epilog. If LIVE global2021F64==0,perform NO MXCSR load. Else requested bit40h AND LIVE latch665ED8 nonzero ->arm
// scope0,try LDMXCSR raw argument. Original65EF00 filter6188CC returns1 only for C0000005/C000001D,others0/continue-search; handler6188E8 restoresESP,clears global latch665ED8
// to0,clears bit40h in by-value argument,retries LDMXCSR. Own disarm write-2 follows retry; no newly armed retry scope or loop. When requested bit40h absent OR latch0,clear bit40h
// and LDMXCSR directly without own try0 arm. Other invalid bits/opcode failures are not normalized or validated; retry/direct load can escape. No current-MXCSR read/merge,status
// preservation or errno/status Boolean. Shared latch has original PE initialization1 and only cleared here,no lock/reset. Full raw word loaded apart from optional bit40h clearing;
// x87 untouched. Caller must not interpret leftover EAX as success.
void __cdecl __set_fpsr_sse2(unsigned int a1)
{
  if ( unk_2021F64 )
  {
    if ( (a1 & 0x40) != 0 && dword_665ED8 )
      _mm_setcsr(a1);
    else
      _mm_setcsr(a1 & 0xFFFFFFBF);
  }
}

