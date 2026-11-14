// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605BF4 ?_CallSETranslator@@YAHPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAX2PBU_s_FuncInfo@@H1@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Recovered original215-byte native
// function605BF4..605CCB; continuation605C9F bytes837DFC00 reclassified from DWORD data to CMP [EBP-4],0, NO byte patch. Original decorated name and continuation label preserved.
// Cdecl seven caller-popped slots {exceptionOrSentinel,registrationOrOutputSlot,context,unusedDispatcher,FuncInfo,catchDepth,markerRegistration}, int0/1. Fourth slot never read. If
// first rawDWORD==123h: write continuation605C9F into *(DWORD*)second slot, return1, without reading exception record, other arguments, PTD or cookie; no NULL output guard. This is
// continuation-address query, not exception code classification. TranslatorGuardHandler uses it then restores ESP/EBP and JMPs to continuation inside original translator frame.
// Normal path installs40-byte stack translator SEH guard {previous fs:0,TranslatorGuardHandler605CCB,global securityCookie XOR
// guardAddress,FuncInfo,registration,catchDepth,marker,savedESP,savedEBP,unwindObserved0}. SavedESP includes savedEBX (EBP-3Ch), savedEBP is this function's frame. Set local
// returnStatus1, build two-DWORD EXCEPTION_POINTERS-like record {originalException,context}; getptd then load LIVE callback DWORD PTD+80h, without decode or NULL check. Cdecl
// indirect callback(exception->code,&localPointers), reclaim8, IGNORE callback EAX; on ordinary callback return set local status0. No default translator fallback, internal exception
// matching or forwarded dispatcher slot. Continuation605C9F (ordinary fallthrough or nonlocal guard jump): if guard.unwindObserved==0 restore fs:0=guard.previous; otherwise read
// next=*(DWORD*)current fs:0, store *(DWORD*)guard.previous=next, then fs:0=guard.previous. This branch relinks previous record and assumes valid chain pointers; it is not the same
// as direct restore. Return local status (normally0, nonlocal path retains1), restore original EBX/EBP/plain RET. No own final cookie check, input/callback validation, allocation,
// lock or finally guarantee on escaping transfers. Cookie/unwind/handler policy resides in reviewed guard; pseudocode omits parts of fs/stack restoration and native notes are
// authoritative.
int __cdecl _CallSETranslator(
        struct EHExceptionRecord *a1,
        void *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        int a6,
        struct EHRegistrationNode *a7)
{
  int v8; // [esp+0h] [ebp-3Ch] BYREF
  int v9; // [esp+4h] [ebp-38h]
  _DWORD v10[2]; // [esp+8h] [ebp-34h] BYREF
  void (__cdecl *v11)(unsigned int, _DWORD *); // [esp+10h] [ebp-2Ch]
  _DWORD v12[9]; // [esp+14h] [ebp-28h] BYREF
  int v13; // [esp+38h] [ebp-4h]
  int savedregs; // [esp+3Ch] [ebp+0h] BYREF

  if ( a1 == (struct EHExceptionRecord *)291 )
  {
    *(_DWORD *)a2 = &_ExceptionContinuation_27230;
    return 1;
  }
  else
  {
    v12[1] = TranslatorGuardHandler;
    v12[2] = (unsigned int)v12 ^ dword_664BD8;
    v12[3] = a5;
    v12[4] = a2;
    v12[5] = a6;
    v12[6] = a7;
    v13 = 0;
    v12[7] = &v8;
    v12[8] = &savedregs;
    v12[0] = NtCurrentTeb()->NtTib.ExceptionList;
    v9 = 1;
    v10[0] = a1;
    v10[1] = a3;
    v11 = (void (__cdecl *)(unsigned int, _DWORD *))_getptd()[32];
    v11(a1->ExceptionCode, v10);
    v9 = 0;
    if ( v13 )
      *(_DWORD *)v12[0] = NtCurrentTeb()->NtTib.ExceptionList->Next;
    return v9;
  }
}

