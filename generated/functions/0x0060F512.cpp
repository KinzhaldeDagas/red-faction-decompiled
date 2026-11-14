// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F512 __get_sse2_info
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs full EAX Boolean0/1,not a cached CPU info
// record. Initialize local feature bits0. Save EFLAGS DWORD,write saved XOR200000h ID-bit attempt,read EFLAGS AGAIN,compare WHOLE DWORD difference (SUB),not just ID mask. If
// unchanged skip CPUID without explicit POPF restore on this branch. If changed restore captured EFLAGS BEFORE CPUID; execute leaf0,store vendor/max-leaf locals unused for decision;
// then leaf1 UNCONDITIONALLY,without checking leaf0 maximum/vendor. Save leaf1 EDX features/EAX signature. Require EDX mask04000000 (bit26) AND has_osfxsr_set() nonzero ->1,else0. No
// independent FXSR/SSE feature-bit test, extended-leaf query, OS API, global capability write, allocation or lock. No own SEH around flag manipulation/CPUID. EBX saved/restored twice
// around CPUID; ESI/EDI not changed. Successful subordinate MOVAPD probe clobbers XMM0. EFLAGS not promised restored at function return (tests/arithmetic afterward); no full x87/SSE
// context preservation.
BOOL _get_sse2_info()
{
  unsigned int v0; // kr00_4
  unsigned int v1; // kr04_4
  int v13; // [esp+18h] [ebp-4h]

  v13 = 0;
  v0 = __readeflags();
  __writeeflags(v0 ^ 0x200000);
  v1 = __readeflags();
  if ( v1 != v0 )
  {
    __writeeflags(v0);
    _EAX = 0;
    __asm { cpuid }
    _EAX = 1;
    __asm { cpuid; UNREALRED VERIFIED: Leaf1 executed without checking leaf0 max leaf; vendor/signature locals unused. }
    v13 = _EDX;
  }
  return (v13 & 0x4000000) != 0 && has_osfxsr_set();
}

