// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061320A ___updatetlocinfo
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs,borrowedcurrentPTDlocaleROOTpointerEAX
// (correctedfalseDWORDsignature). getptd;if(PTD+112 &global66598C)!=0 ANDPTD+108nonNULL,callgetptdAGAINandreturnSECONDPTD+108withoutlock/refchanges.
// Elselock12/armEH4scope65ED20,callupdatetlocinfoEx_nolock(EAX=&PTD+108,EDI=LIVEglobaloff665A70),savereturn;finallyunlock12andrestoreESIonbothnormal/unwindhandler613274.
// NULLresultafterunlock ->amsg_exit32fatal. No ownpinset,copy,callerreferenceacquisition,errno policyorcomponentvalidation; helpermaydeclineNULLglobalwithoutupdatingPTD.
volatile LONG *__cdecl __updatetlocinfo()
{
  DWORD *v0; // esi
  volatile LONG *v1; // esi
  volatile LONG *v3; // [esp+10h] [ebp-1Ch]

  v0 = _getptd();
  if ( (dword_66598C & v0[28]) != 0 && v0[27] )
  {
    v1 = (volatile LONG *)_getptd()[27];
  }
  else
  {
    _lock(12);
    v3 = _updatetlocinfoEx_nolock((volatile LONG **)v0 + 27, (volatile LONG *)off_665A70);
    _unlock(12);
    v1 = v3;
  }
  if ( !v1 )
    _amsg_exit(32);
  return v1;
}

