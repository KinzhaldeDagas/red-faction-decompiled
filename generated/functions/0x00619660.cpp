// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619660 __unwind_handler
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl five raw stack slots {const
// exceptionRecord*,opaque secondValue,unused thirdValue,outputSlot**,guardRecord*},int disposition1/3; no assumption that fifth slot is an ordinary four-argument OS handler. Read
// exception flagsDWORD+4 mask6 only. Mask clear ->EAX1 immediately,no cookie/output/guard access. Nonzero: EAX=fifth guard pointer,ECX=*(guard-4) XOR guard,check_security_cookie. On
// expected cookie-match return helper preserves EAX, so subsequent loads STILL use fifth guard pointer; decompiler undefined v6 is an ABI artifact. Save
// liveEBP,setEBP=*(guard+10h),push DWORDguard+28h target thenDWORDguard+24h legacy frame;call local_unwind2 with this parentEBP,caller reclaim8,restore savedEBP. Write original
// secondValue into *fourth output slot,EAX3,plainRET. Local_unwind2 guard layout makes +24/+28 original caller stack arguments beyond five-DWORD registration,not validated object
// members. No NULL/size/output check, flags reset, own SEH scope or callback result. Cookie failure delegates fatal reporter; expected-match preservation contract recorded
// separately.
int __cdecl _unwind_handler(const struct _EXCEPTION_RECORD *a1, void *a2, void *a3, void **a4, const _DWORD *a5)
{
  int result; // eax
  int v6; // eax

  result = 1;
  if ( (a1->ExceptionFlags & 6) != 0 )
  {
    crt_check_security_cookie_ecx((unsigned int)a5 ^ *(a5 - 1));
    _local_unwind2(*(void **)(v6 + 16), *(_DWORD **)(v6 + 36), *(_DWORD *)(v6 + 40));
    *a4 = a2;
    return 3;
  }
  return result;
}

