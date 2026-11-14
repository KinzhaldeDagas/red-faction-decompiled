// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061EC7F __sopen_helper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. Cdecl(filename,oflag,share,pmode,int*outfd,secureFlag),errno-style0/error. Initacquiredlocal0;NULLoutfd invalid22/return22
// withoutwrite. Validoutfd FIRSTset-1,thenrequirefilenameNONNULL and,ifsecureFlag!=0,(pmode&0xFFFFFE7F)==0 (onlybits180allowed);failureinvalid22/22,nodoserrnoreset.
// Noemptyfilename/oflag/sharegrammarprecheck. ArmEH4finally; calltsopen_nolock withEAXoutfd
// andfivecaller-cleanedstackslots(acquiredAddress,filename,oflag,share,pmode),storestatusONLYAFTERcalleereturn. Finallyifacquirednonzero: ifstatusnonzero
// clearrecordopen1,thenunlock_fhandle(*outfd). Normalreturnstatusnonzero sets*outfd=-1 AFTERfinally;successpreservesfd. OnUNWIND,statuslocalhasnotnecessarilybeeninitialized
// (assignedaftercall),so flagclearingdependsuninitializedstatus,thoughacquiredstillgovernsunlock. NoownCloseHandle/resourcefreeonexception, rollbackofBOM/truncateprogress or
// normalizationoferrorvalues. Scope65F008 filter0/handler61ED18 independentlyverified.
int __cdecl _sopen_helper(LPCSTR lpFileName, int a2, int a3, int a4, int *a5, int a6)
{
  int result; // eax
  _BYTE *v7; // eax
  int v8; // [esp+14h] [ebp-20h]
  int v9; // [esp+18h] [ebp-1Ch] BYREF
  CPPEH_RECORD ms_exc; // [esp+1Ch] [ebp-18h]

  v9 = 0;
  if ( !a5 || (*a5 = -1, !lpFileName) || a6 && (a4 & 0xFFFFFE7F) != 0 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  else
  {
    ms_exc.registration.TryLevel = 0;
    v8 = _tsopen_nolock(a5, &v9, lpFileName, a2, a3, a4);
    ms_exc.registration.TryLevel = -2;
    if ( v9 )
    {
      if ( v8 )
      {
        v7 = (_BYTE *)(unk_2021E40[*a5 >> 5] + ((*a5 & 0x1F) << 6) + 4);
        *v7 &= ~1u;
      }
      _unlock_fhandle(*a5);
    }
    result = v8;
    if ( v8 )
      *a5 = -1;
  }
  return result;
}

