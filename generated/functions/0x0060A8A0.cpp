// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A8A0 __allshl
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native register helper:64-bit value in EDX:EAX, UNSIGNED8 count in CL,64-bit result ALSO EDX:EAX. No stack arguments, frame or memory access. Count0..31 uses
// SHLD EDX,EAX,CL and SHL EAX,CL. Count32..63 moves relevant old half into surviving half and masks CL&31; clears lowEAX,shifts highEDX from oldEAX. Count>=64 returns both halves0.
// This is explicit saturation at64, not modulo64 count behavior. Only CL participates; upper ECX ignored, CL is modified on32..63 path. EAX-only old result types for signed helpers
// truncated the upper half and are corrected; no helper/overflow/error call.
unsigned __int64 __usercall _allshl@<edx:eax>(unsigned __int64 value@<edx:eax>, unsigned __int8 count@<cl>)
{
  unsigned __int64 result; // rax
  int v3; // edx

  if ( count >= 0x40u )
    return 0;
  if ( count < 0x20u )
    return value << (count & 0x1F);
  v3 = value;
  LODWORD(result) = 0;
  HIDWORD(result) = v3 << (count & 0x1F);
  return result;
}

