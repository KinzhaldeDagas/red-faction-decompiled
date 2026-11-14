// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006131CC __updatetlocinfoEx_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Locale root offsets:
// rootrefLONG0,lconvRefPtr176,numericRefPtr180,monetaryRefPtr184,lconvPtr188,ctypeRefPtr192,biasedCtypePtr196,biasedLowerPtr204,biasedUpperPtr208,timePtr212. Six categoryrecords
// at72+16*i contain narrowNamePtr0,wideNamePtr4,narrowRefPtr8,wideRefPtr12; narrow static C-name identity ADDRESS665990. Internal
// EAX=destinationroot**slot,EDI=newroot*,returnsnewroot/NULL. IfeitherinputNULLreturnNULLwithoutwrites/refchanges. Ifold==newreturnnewwithoutcountchange.
// ElseFIRSTpublishnewthroughslot,addlocaleref(new);ifoldnonNULL removelocaleref(old),thenreadoldROOTcount;EXACT0andold!=ADDRESS665998 ->freetlocinfo(old). Returnnew. No
// ownlock,rollback,allocation,errno orcomponentcountresultnormalization. Publicationprecedesownershipadjustment; callerlockrequiredforconsistentglobaladoption.
volatile LONG *__usercall _updatetlocinfoEx_nolock@<eax>(volatile LONG **a1@<eax>, volatile LONG *a2@<edi>)
{
  volatile LONG *v2; // esi

  if ( !a2 || !a1 )
    return nullptr;
  v2 = *a1;
  if ( *a1 != a2 )
  {
    *a1 = a2;
    __addlocaleref(a2);
    if ( v2 )
    {
      __removelocaleref(v2);
      if ( !*v2 && v2 != (volatile LONG *)&unk_665998 )
        __freetlocinfo((char *)v2);
    }
  }
  return a2;
}

