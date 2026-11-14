// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DF1C __convertTOStoQNaN
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Dual-output x87 helper: test incoming EAX mask0x80000. Set bit ->EAX7,leaveST0 untouched. Clear bit ->FADD verified DOUBLE1.0 to ST0 (quieting via hardware
// arithmetic),EAX1. No EBP/frame/stack args or status-PF test, no payload preservation guarantee beyond hardware, no malloc/errno. Existing floating prototype does not express
// additional EAX status channel; both outputs recorded explicitly.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Native clobber refinement: only EAX among GPRs
// changes; preserve ECX/EDX and remaining GPRs. Input extended ST0, plus EAX original high/exponent classifier; returned FP value and independent EAX type1/7 remain dual native
// channels. Explicit spoils<eax> avoids broader fictitious register destruction; floating arithmetic remains live-environment behavior.
double __usercall __spoils<eax> _convertTOStoQNaN@<st0>(int a1@<eax>, long double a2@<st0>)
{
  if ( (a1 & 0x80000) == 0 )
    return a2 + 1.0;
  return a2;
}

