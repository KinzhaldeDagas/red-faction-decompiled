// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D300 __aullshr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native register helper:64-bit value in EDX:EAX, UNSIGNED8 count in CL,64-bit result ALSO EDX:EAX. No stack arguments, frame or memory access. Count0..31 uses
// SHRD EAX,EDX,CL and SHR EDX,CL. Count32..63 moves relevant old half into surviving half and masks CL&31; clears highEDX and logical-shifts oldEDX into lowEAX. Count>=64 returns
// both halves0. This is explicit saturation at64, not modulo64 count behavior. Only CL participates; upper ECX ignored, CL is modified on32..63 path. EAX-only old result types for
// signed helpers truncated the upper half and are corrected; no helper/overflow/error call.
unsigned __int64 __usercall _aullshr@<edx:eax>(unsigned __int64 a1@<edx:eax>, unsigned __int8 a2@<cl>)
{
  if ( a2 >= 0x40u )
    return 0;
  else
    return a1 >> a2;
}

