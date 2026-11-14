// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608908 _feof
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl stream. NonNULL ->return rawflags&0x10 (0 or16,NOT normalized1).
// NULL ->invalid/0. No lock, I/O, EOFbit clearing, descriptor test or validity check beyondNULL. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with
// stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl feof(FILE *Stream)
{
  if ( Stream )
    return Stream->_flag & 0x10;
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return 0;
}

