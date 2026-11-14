// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F8F9 __CxxThrowException@8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Stdcall(exceptionObject*,ThrowInfo*),RET8epiloguepresentafterRaiseExceptionifitreturns;existingnoreturntypingretained.
// CopyEXACT32originalPEbytesfrom6490A4tostack8DWORDrecord={E06D7363h,1,0,0,3,19930520h,0,0}. Setparameter1=RAWexceptionObjectpointer,parameter2=RAWThrowInfopointer.
// IfThrowInfopointerNONNULLandattributesBYTE mask8set,replaceparameter0magicwithIMMEDIATE01994000h,NOTdereferenceofthataddress.
// RaiseException(record.code,record.flags=1,record.nParams=3,&record.param0).
// NoownobjectNULLguard,RTTIsignaturevalidation,exceptionobjectcopy/constructor/destructor,allocation,lock,errno,catchorloop.
// ThrowInfopointerisusedonlyforoptionalattributecheckandforwardedraw;noncontinuableflag1anddispatchbehaviorbelongtoOSunwinder.
// Objectlifetime/catchcopy/destructionhandledelsewhere;originalnormalmagicandthreeparametersindependentlyverifiedagainststatictemplate.
void __stdcall __noreturn _CxxThrowException(void *pExceptionObject, _ThrowInfo *pThrowInfo)
{
  DWORD dwExceptionCode[8]; // [esp+8h] [ebp-20h] BYREF

  qmemcpy(dwExceptionCode, &unk_6490A4, sizeof(dwExceptionCode));
  dwExceptionCode[6] = (DWORD)pExceptionObject;
  dwExceptionCode[7] = (DWORD)pThrowInfo;
  if ( pThrowInfo && (pThrowInfo->attributes & 8) != 0 )
    dwExceptionCode[5] = (DWORD)&unk_1994000;
  RaiseException(dwExceptionCode[0], dwExceptionCode[1], dwExceptionCode[4], &dwExceptionCode[5]);
}

