// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E4A6 ____lc_codepage_func
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Noargs. Getthreaddata,currentlocale=thread+108. If locale differsglobal665A70 AND(thread+112 &global66598C)==0,call updatetlocinfo anduse
// returnedlocale;otherwise use original. ReturnDWORD locale+4. No NULL/pin/ownershipcheck, locale retain/release, allocation directly inwrapper or pointer result; current
// global/thread values reread as shown.
unsigned int __cdecl ___lc_codepage_func()
{
  DWORD *v0; // ecx
  volatile LONG *v1; // eax

  v0 = _getptd();
  v1 = (volatile LONG *)v0[27];
  if ( v1 != (volatile LONG *)off_665A70 && (dword_66598C & v0[28]) == 0 )
    v1 = __updatetlocinfo();
  return *((_DWORD *)v1 + 1);
}

