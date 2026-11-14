// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A8C0 __allshr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native register helper:64-bit value in EDX:EAX, UNSIGNED8 count in CL,64-bit result ALSO EDX:EAX. No stack arguments, frame or memory access. Count0..31 uses
// SHRD EAX,EDX,CL and SAR EDX,CL. Count32..63 moves relevant old half into surviving half and masks CL&31; sets highEDX to sign extension of oldEDX and arithmetic-shifts oldEDX into
// lowEAX. Count>=64 returns both halves sign-filled from original high sign. This is explicit saturation at64, not modulo64 count behavior. Only CL participates; upper ECX ignored,
// CL is modified on32..63 path. EAX-only old result types for signed helpers truncated the upper half and are corrected; no helper/overflow/error call.
__int64 __usercall _allshr@<edx:eax>(__int64 value@<edx:eax>, unsigned __int8 count@<cl>)
{
  __int64 result; // rax

  if ( count >= 0x40u )
  {
    HIDWORD(result) = SHIDWORD(value) >> 31;
    LODWORD(result) = HIDWORD(result);
  }
  else if ( count >= 0x20u )
  {
    result = SHIDWORD(value);
    LODWORD(result) = (int)result >> (count & 0x1F);
  }
  else
  {
    return value >> (count & 0x1F);
  }
  return result;
}

