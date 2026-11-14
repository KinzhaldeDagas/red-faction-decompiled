// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D21E __positive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl pointer toDOUBLE64. FLDZ; FCOMP QWORD[*pointer] compares0 with value and pops temporary. FNSTSW AX; TEST AH,0x41; JP rejects when masked status parity
// even. Exact result1 for ORDERED value>=0 including both signed zeros,0 for negative or unorderedNaN. Canonical fullEAX0/1, no CW changes or input mutation; NULL pointer invalid. No
// input x87 stack argument.
BOOL __cdecl _positive(double *a1)
{
  return *a1 >= 0.0;
}

