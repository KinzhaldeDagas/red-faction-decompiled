// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006130A4 ___addlocaleref
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Locale root offsets:
// rootrefLONG0,lconvRefPtr176,numericRefPtr180,monetaryRefPtr184,lconvPtr188,ctypeRefPtr192,biasedCtypePtr196,biasedLowerPtr204,biasedUpperPtr208,timePtr212. Six categoryrecords
// at72+16*i contain narrowNamePtr0,wideNamePtr4,narrowRefPtr8,wideRefPtr12; narrow static C-name identity ADDRESS665990.
// Noownlock,allocation,free,underflow/overflowcheckortransaction; eachcomponentcountupdatedatomicallybutoperationisNOTatomicasawhole. Cdecl(nonNULLroot),LONGEAX.
// InterlockedIncrement(rootref),then nonNULLlconvRef,monRef,numRef,ctypeRefinthatorder. Sixcategoryslots: incrementnarrowRefiffnarrowName!=ADDRESS665990 andrefnonNULL
// (nameNULLitselfdoesnotblock);incrementwideRefiffwideNameANDrefnonNULL. FinallyUNCONDITIONALLYincrementtimePtr+180,noNULL/static-timeguard.
// ReturnLASTtimeincrementresult,NOTrootrefcount. No specialcasefordefaultlocale/timeotherthanstaticnarrow-namecheck.
LONG __cdecl __addlocaleref(volatile LONG *lpAddend)
{
  volatile LONG **v2; // ebx
  int lpAddenda; // [esp+14h] [ebp+8h]

  InterlockedIncrement(lpAddend);
  if ( *((_DWORD *)lpAddend + 44) )
    InterlockedIncrement(*((volatile LONG **)lpAddend + 44));
  if ( *((_DWORD *)lpAddend + 46) )
    InterlockedIncrement(*((volatile LONG **)lpAddend + 46));
  if ( *((_DWORD *)lpAddend + 45) )
    InterlockedIncrement(*((volatile LONG **)lpAddend + 45));
  if ( *((_DWORD *)lpAddend + 48) )
    InterlockedIncrement(*((volatile LONG **)lpAddend + 48));
  v2 = (volatile LONG **)(lpAddend + 20);
  lpAddenda = 6;
  do
  {
    if ( *(v2 - 2) != (volatile LONG *)&unk_665990 && *v2 )
      InterlockedIncrement(*v2);
    if ( *(v2 - 1) && v2[1] )
      InterlockedIncrement(v2[1]);
    v2 += 4;
    --lpAddenda;
  }
  while ( lpAddenda );
  return InterlockedIncrement((volatile LONG *)(*((_DWORD *)lpAddend + 53) + 180));
}

