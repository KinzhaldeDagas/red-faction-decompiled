// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006143CC __freebuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE,noNULL/lock. SnapshotflagsEAX. ONLY flags&0x83
// ANDownedbufbit8 callsfree(base);thenflags &=0xFFFFFBF7 clears8/0x400,ptr/base/cnt0,return0. Skiproute returnsORIGINALflagsDWORD,notBoolean. Doesnotclearbufsiz/fd/tmpname
// orfreeFILE/borrowedtempbuffer. No priorbuffer validity or duplicate-freeguard beyondclearedbits.
int __cdecl _freebuf(int a1)
{
  int result; // eax

  result = *(_DWORD *)(a1 + 12);
  if ( (result & 0x83) != 0 && (result & 8) != 0 )
  {
    free(*(void **)(a1 + 8));
    *(_DWORD *)(a1 + 12) &= 0xFFFFFBF7;
    *(_DWORD *)a1 = 0;
    *(_DWORD *)(a1 + 8) = 0;
    *(_DWORD *)(a1 + 4) = 0;
    return 0;
  }
  return result;
}

