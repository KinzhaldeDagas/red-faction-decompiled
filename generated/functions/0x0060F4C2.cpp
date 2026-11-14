// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F4C2 _has_osfxsr_set
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs int Boolean probe; native MOVAPD XMM0,XMM1
// inside SEH4 scope65EC80,not direct CR4/OSFXSR flag query. On instruction success overwrite XMM0 from live XMM1, set result1. Filter60F4DF reads exception code; C0000005 orC000001D
// ->1/execute-handler; other codes0/continue-search. Handler60F4FB restoresESP,result0. Normal disarm/epilog,return0/1. XMM0 is NOT restored on success; no XMM/MXCSR snapshot, CPUID
// gate here, cache/global update or handler callback. Flattened pseudocode constant1 omits real instruction/exception paths. Other exceptions escape; routine does not report false
// for every possible failure.
int has_osfxsr_set()
{
  return 1;
}

