// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605BC1 ?CatchGuardHandler@@YA?AW4_EXCEPTION_DISPOSITION@@PAUEHExceptionRecord@@PAUCatchGuardRN@@PAX2@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl guard handler; reads three stack slots
// {exception*,guardRecord*,context*}, any fourth dispatcher slot ignored. CLD. Check cookie ECX=guard+8 XOR guardAddress through security-cookie helper. Then
// InternalCxxFrameHandler(exception,*(guard+16),context,NULL,*(guard+12),*(guard+20),guard,0); reclaim32, return raw EAX. Guard layout first24bytes
// {next,handler,cookieXorAddress,FuncInfo*,parentRegistration*,catchDepth}. It is NOT a plain EHRegistrationNode: old type incorrectly renders these fields as array elements. No own
// flag filtering, fs-chain change, cookie repair, NULL validation or guarded retry; cookie mismatch delegates fatal path. Preserve ESI/EBP.
int __cdecl CatchGuardHandler(struct EHExceptionRecord *a1, _DWORD *a2, struct _CONTEXT *a3)
{
  crt_check_security_cookie_ecx((unsigned int)a2 ^ a2[2]);
  return __InternalCxxFrameHandler(
           a1,
           (struct EHRegistrationNode *)a2[4],
           a3,
           nullptr,
           (const struct _s_FuncInfo *)a2[3],
           a2[5],
           (struct EHRegistrationNode *)a2,
           0);
}

