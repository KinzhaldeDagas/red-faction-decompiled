// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006183D9 __raise_exc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 14 instructions/35 bytes. Cdecl invoke 0x006180FD __raise_exc_ex with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), callerDWORD4(EBP+24), callerDWORD5(EBP+28), 0x00000000]. Order derived from every raw PUSH,
// not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly28 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument
// validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers
// forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literal0 selects binary64 operand/result storage in __raise_exc_ex.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Refined actual delegate contract: six ordinary
// caller-popped DWORD slots are record*,savedRawCW*,flags,operation,binary64 arg*,binary64 result*. Appended literal0 selects BINARY64 width in __raise_exc_ex, not a locale/default
// argument. No semantic EAX return; delegate's last integer register state is incidental. Corrected void return and pointer widths; native PUSH order/28-byte delegate cleanup/plain
// RET unchanged.
void __cdecl _raise_exc(
        _DWORD *Arguments,
        unsigned int *a2,
        unsigned int dwExceptionCode,
        int a4,
        const double *a5,
        double *a6)
{
  _raise_exc_ex(Arguments, a2, dwExceptionCode, a4, a5, a6, 0);
}

