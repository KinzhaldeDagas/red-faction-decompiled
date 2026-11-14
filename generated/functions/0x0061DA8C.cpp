// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DA8C __getbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE,noNULL/existingbuffer/lockguard. Incrementglobal20213AC,
// malloc_crt4096,storeallocation atbase evenNULL. SuccessORflags8,bufsiz4096;failureORflags4,base=FILE+20 inlinecharbuf,bufsiz2. Thenptr=base,cnt0,returnbase-addressEAX.
// Doesnotclearoppositebufferflag,freeoldbase orresetotherfields; callerownsadmission toavoid overwritinglivebuffer.
int __cdecl _getbuf(_DWORD *a1)
{
  void *v1; // eax
  int result; // eax

  ++unk_20213AC;
  v1 = _malloc_crt(0x1000u);
  a1[2] = v1;
  if ( v1 )
  {
    a1[3] |= 8u;
    a1[6] = 4096;
  }
  else
  {
    a1[3] |= 4u;
    a1[2] = a1 + 5;
    a1[6] = 2;
  }
  result = a1[2];
  a1[1] = 0;
  *a1 = result;
  return result;
}

