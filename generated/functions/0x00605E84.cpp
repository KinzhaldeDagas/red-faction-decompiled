// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605E84 ?_CallCatchBlock2@@YAPAXPAUEHRegistrationNode@@PBU_s_FuncInfo@@PAXHK@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(parentRegistration*,const
// FuncInfo*,catchCodePC,signed depth,unsigned notificationCode), return raw CallSettingFrame EAX/continuation pointer. Allocate24-byte stack guard {old
// fs:0,CatchGuardHandler605BC1,securityCookie XOR guardAddress,FuncInfo,parentRegistration,depth+1 modulo32}. Publish fs:0=&guard; stdcall
// CallSettingFrame(catchCodePC,parentRegistration,notificationCode), whose RET12 consumes three slots. On normal return preserve helper EAX in ECX while restoring fs:0=guard.next;
// return saved EAX. No own normal-return cookie check, locking, exception-record object copy or validation. Cookie checked by guard only when invoked during exceptional dispatch. No
// finally block guarantees explicit normal restoration if delegate transfers control; guard participates in native SEH. Parent frame/callback semantics delegated to reviewed
// CallSettingFrame.
void *__cdecl _CallCatchBlock2(
        struct EHRegistrationNode *a1,
        const struct _s_FuncInfo *a2,
        void *a3,
        int a4,
        unsigned int a5)
{
  _DWORD v6[6]; // [esp+0h] [ebp-18h] BYREF

  v6[2] = (unsigned int)v6 ^ dword_664BD8;
  v6[3] = a2;
  v6[1] = CatchGuardHandler;
  v6[4] = a1;
  v6[5] = a4 + 1;
  v6[0] = NtCurrentTeb()->NtTib.ExceptionList;
  return _CallSettingFrame(a3, a1, a5);
}

