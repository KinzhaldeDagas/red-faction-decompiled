// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ACB0 crt_atan2_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Ten-byte tail adapter: MOV EDX,descriptor665D60; JMP616A7B __ctrandisp2. Original48 descriptor bytes begin length5 and ASCII atan2, contain native handler
// pointers. Fresh616A7B reads TWO DOUBLE64 stack arguments at caller+4/+12, calls616C44 __fload for each, saves x87 control word and dispatches60DD27 using EDX descriptor. ctranexit
// fall-through616AC3..616C10 preserves/restores ST0 result (including error handler reload) and original control word; wrapper return is DOUBLE in ST0, NOT EAX and not incoming
// ST0/ST1 parameters. Corrected ordinary cdecl(double,double) prototype, no caller argument consumption in tail. Domain/range/special-value/control-word policy delegated to runtime
// dispatcher; no claim that EAX carries numeric result.
double __cdecl crt_atan2_dispatch(double a1, double a2)
{
  return _ctrandisp2(&unk_665D60, a1, a2);
}

