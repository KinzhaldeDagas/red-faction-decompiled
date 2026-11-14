// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C57F __fileno
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE. NonNULL returns rawDWORDfd at+16 without OSquery/range/flags
// validation orlock. NULL ->invalid/-1. Does not normalize -1/-2 specialhandles or allocate stream. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0),
// with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl _fileno(FILE *Stream)
{
  if ( Stream )
    return Stream->_file;
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return -1;
}

