// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CB4B _abort
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs abort. Global behavior666050 mask1 ->
// NMSG_WRITE10. Get decoded abort-handler slot2021C84; any NONNULL value, including SIG_IGN1, triggers raise(22), ignoring result. NULL bypasses raise. Behavior mask2: build PARTIAL,
// nonzero-initialized CONTEXT with flags10001, live registers AFTER preceding calls, low WORD segment fields and caller EIP/saved EBP/ESP=&returnAddress. Zero80-byte
// EXCEPTION_RECORD, set code40000015, flags0, caller exception address. SetUnhandledExceptionFilter(NULL), directly call UnhandledExceptionFilter(record/context), ignore results/old
// filter, never restore. Always QUICK _exit(3)60A65A. No actual RaiseException call, full-context capture, own catch or security-cookie epilogue; noreturn path delegates termination
// to quick exit.
void __cdecl __noreturn abort()
{
  int v0; // esi
  PVOID decoded_pointer_02021c84; // eax
  int v2; // edx
  int v3; // ecx
  unsigned int v4; // kr00_4
  int v5; // [esp-4h] [ebp-330h]
  _DWORD v6[20]; // [esp+4h] [ebp-328h] BYREF
  struct _EXCEPTION_POINTERS ExceptionInfo; // [esp+54h] [ebp-2D8h] BYREF
  int v8; // [esp+5Ch] [ebp-2D0h] BYREF
  __int16 v9; // [esp+E8h] [ebp-244h]
  __int16 v10; // [esp+ECh] [ebp-240h]
  __int16 v11; // [esp+F0h] [ebp-23Ch]
  __int16 v12; // [esp+F4h] [ebp-238h]
  int v13; // [esp+FCh] [ebp-230h]
  int v14; // [esp+104h] [ebp-228h]
  int v15; // [esp+108h] [ebp-224h]
  PVOID v16; // [esp+10Ch] [ebp-220h]
  int v17; // [esp+110h] [ebp-21Ch]
  void *v18; // [esp+114h] [ebp-218h]
  __int16 v19; // [esp+118h] [ebp-214h]
  unsigned int v20; // [esp+11Ch] [ebp-210h]
  void **v21; // [esp+120h] [ebp-20Ch]
  __int16 v22; // [esp+124h] [ebp-208h]
  int savedregs; // [esp+32Ch] [ebp+0h]
  void *retaddr; // [esp+330h] [ebp+4h] BYREF

  if ( (dword_666050 & 1) != 0 )
    _NMSG_WRITE(10);
  decoded_pointer_02021c84 = crt_get_decoded_pointer_02021c84();
  if ( decoded_pointer_02021c84 )
  {
    decoded_pointer_02021c84 = (PVOID)raise(22);
    v3 = v5;
  }
  if ( (dword_666050 & 2) != 0 )
  {
    v16 = decoded_pointer_02021c84;
    v15 = v3;
    v14 = v2;
    v13 = v0;
    v22 = __SS__;
    v19 = __CS__;
    v12 = __DS__;
    v11 = __ES__;
    v10 = __FS__;
    v9 = __GS__;
    v4 = __readeflags();
    v20 = v4;
    v21 = &retaddr;
    v8 = 65537;
    v18 = retaddr;
    v17 = savedregs;
    memset(v6, 0, sizeof(v6));
    ExceptionInfo.ExceptionRecord = (PEXCEPTION_RECORD)v6;
    v6[0] = 1073741845;
    v6[3] = retaddr;
    ExceptionInfo.ContextRecord = (PCONTEXT)&v8;
    SetUnhandledExceptionFilter(nullptr);
    UnhandledExceptionFilter(&ExceptionInfo);
  }
  _exit(3);
}

