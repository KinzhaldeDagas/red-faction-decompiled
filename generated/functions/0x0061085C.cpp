// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061085C _write_string
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Internal EAX count/errorpointer,ECXsource,EDI FILE,one
// signedcountstackslot. Syntheticstringflag0x40 ANDbaseNULL ->ADD rawcount to*counter evenifnegative,returnrawcountEAX. Otherwisewhilecount>0:readbyte,DEClocalcount
// BEFOREwrite_char(FILE,AL,counter),advance source;counter==-1 ->readerrno. Errno!=42 exits witherrnoSLOTpointerEAX;errno42 attemptswrite_char literal?
// (0x3F),thencontinuesremainingloop,without restoringoldcount. Successful replacement canincrement sentinel-1 to0. No own sourceNULstop/capacitycheck/lock. Count<=0 real-outputpath
// writesnone andreturnsincomingpointerresidue; no semanticint* resultpromise.
int *__usercall write_string@<eax>(int *result@<eax>, _BYTE *a2@<ecx>, int a3@<edi>, int a4)
{
  int *v4; // esi

  v4 = result;
  if ( (*(_BYTE *)(a3 + 12) & 0x40) == 0 || *(_DWORD *)(a3 + 8) )
  {
    while ( a4 > 0 )
    {
      LOBYTE(result) = *a2;
      --a4;
      result = (int *)write_char((FILE *)a3, (int)result, v4);
      ++a2;
      if ( *v4 == -1 )
      {
        result = _errno();
        if ( *result != 42 )
          return result;
        LOBYTE(result) = 63;
        result = (int *)write_char((FILE *)a3, (int)result, v4);
      }
    }
  }
  else
  {
    *result += a4;
    return (int *)a4;
  }
  return result;
}

