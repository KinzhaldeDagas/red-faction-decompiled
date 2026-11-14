// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612A9E ___updatetmbcinfo
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multibyte record layout:
// refcountLONG+0,codepageDWORD+4,multibyteFlagDWORD+8,LCIDDWORD+12,sixWORDdata+16..27,classBYTE[257]+28 (character c at+29+c),caseMapBYTE[256]+285,totalallocation544
// with3trailingpaddingbytes. Noargs,borrowed current PTDmultibytepointer,notnewrefownership. getptd; if(PTD+112 & global66598C)!=0 AND PTDlocale+108nonNULL,returnPTDmb+104
// WITHOUTlock/refchange (gatechecksLOCALEpointer,notmbpointer). Elselock13,armEH4scope65ECE0. IfoldPTDmb!=global lpAddend: oldnonNULL InterlockedDecrement;zeroandold!=ADDRESS665468
// ->freeold. PublishCURRENTglobaltoPTD+104,re-readglobalasreturnpointer,InterlockedIncrement(new), noNULLguardonnewbeforeincrement. Identicalpointerdoesnotincrement/decrement.
// Finallyunlock13 normal/unwind via612B36(reloadESI) /612B39. Afterunlock NULLresult callsamsg_exit32fatal;no ownerrno or validation. Multipleglobalreadsassumeprotectionbylock13;
// nocopiedsnapshot, detachedcallerreferenceorcomponentdestructor.
volatile LONG *__updatetmbcinfo()
{
  DWORD *v0; // edi
  volatile LONG *v1; // esi

  v0 = _getptd();
  if ( (dword_66598C & v0[28]) != 0 && v0[27] )
  {
    v1 = (volatile LONG *)v0[26];
  }
  else
  {
    _lock(13);
    v1 = (volatile LONG *)v0[26];
    if ( v1 != lpAddend )
    {
      if ( v1 && !InterlockedDecrement(v1) && v1 != (volatile LONG *)&unk_665468 )
        free((void *)v1);
      v0[26] = (DWORD)lpAddend;
      v1 = lpAddend;
      InterlockedIncrement(lpAddend);
    }
    _unlock(13);
  }
  if ( !v1 )
    _amsg_exit(32);
  return v1;
}

