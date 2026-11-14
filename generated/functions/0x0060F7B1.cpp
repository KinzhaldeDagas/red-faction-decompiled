// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F7B1 ??0exception@std@@QAE@ABQBD@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall destination plus pointer-to-C-string-pointer stack argument, RET4,return self. Set std::exception vtable first; dereference supplied pointer once.
// NonNULL source: strlen+1 with native32 wrap, malloc extent, store result toself+4 even whenNULL; only nonNULL allocation calls strcpy_s(buffer,extent,LIVE re-fetched source). NULL
// source sets+self4=0. ALWAYS set ownershipDWORD+self8=1 afterward, even allocation failure/NULL message. Does not validate self/outer source-pointer, bound strlen, propagate
// allocation/copy status, preserve old destination message or allocate containing object. No dedicated constructor-failure status; base vtable remains until derived wrapper
// overwrites.
std::exception *__thiscall std::exception::exception(std::exception *this, const char **a2)
{
  size_t v3; // esi
  char *v4; // eax

  *(_DWORD *)this = &std::exception::`vftable';
  if ( *a2 )
  {
    v3 = strlen(*a2) + 1;
    v4 = (char *)malloc(v3);
    *((_DWORD *)this + 1) = v4;
    if ( v4 )
      strcpy_s(v4, v3, *a2);
  }
  else
  {
    *((_DWORD *)this + 1) = 0;
  }
  *((_DWORD *)this + 2) = 1;
  return this;
}

