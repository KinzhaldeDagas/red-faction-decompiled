// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061630A __stbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl stream. fileno/isatty gate first; nonterminal ->0. Only exact
// table+32 (index0) or+64(index1) admitted,others0. Increment global20213AC BEFORE checking existing flags0x10C; existingbuffer returns0 with counter increment. Select persistent
// cache2021C74[index]. Empty cache malloc_crt4096 andstore result; success/reusedcache ->base=ptr=cache,cnt=bufsiz4096. Failure ->base=ptr=stream+20,cnt=bufsiz2.
// ORflags0x1102,return1 on BOTH heap and inlinefallback. Does not free cache/receiver or rejectNULL beforefileno; cache allocation reused, temporary ownership is not flag8 malloc
// ownership. Table getter is no-arg pure pointer; its ABI repair resolves this decompilation failure.
int __cdecl _stbuf(FILE *Stream)
{
  int v1; // eax
  int v2; // eax
  char **v3; // edi
  char *v4; // eax
  char *v5; // edi

  v1 = _fileno(Stream);
  if ( !_isatty(v1) )
    return 0;
  if ( Stream == (FILE *)((char *)crt_return_static_address_00664de0() + 32) )
  {
    v2 = 0;
  }
  else
  {
    if ( Stream != (FILE *)((char *)crt_return_static_address_00664de0() + 64) )
      return 0;
    v2 = 1;
  }
  ++unk_20213AC;
  if ( (Stream->_flag & 0x10C) != 0 )
    return 0;
  v3 = (char **)(4 * v2 + 33692788);
  if ( dword_2021C74[v2] || (v4 = (char *)_malloc_crt(0x1000u), (*v3 = v4) != nullptr) )
  {
    v5 = *v3;
    Stream->_base = v5;
    Stream->_ptr = v5;
    Stream->_bufsiz = 4096;
    Stream->_cnt = 4096;
  }
  else
  {
    Stream->_base = (char *)&Stream->_charbuf;
    Stream->_ptr = (char *)&Stream->_charbuf;
    Stream->_bufsiz = 2;
    Stream->_cnt = 2;
  }
  Stream->_flag |= 0x1102u;
  return 1;
}

