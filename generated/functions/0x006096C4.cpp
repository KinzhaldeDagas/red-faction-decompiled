// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006096C4 __vsprintf_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(buffer,format,locale,vaList). Requireformat andbuffer
// nonNULL,elseinvalid/-1. Create local FILE with base=ptr=buffer,cntINT_MAX,flags0x42; remainingfields notfullyinitialized. output_l(&FILE,format,locale,vaList),save result. DEC
// localcnt wrapped: negative ->flsbuf(0,&FILE),elsewriteNUL atcurrentptr; IGNORE terminator-flsbuf result andreturn SAVED formatter result. No actual caller capacity, INT_MAX is
// fabricated extent; no own formatting/parser/lock. Destination progress andfinalNULattempt remain even if formatter resultnegative. Unqualified invalid denotes errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl _vsprintf_l(char *const Buffer, const char *const Format, const _locale_t Locale, va_list ArgList)
{
  int v5; // eax
  bool v6; // sf
  int v7; // esi
  FILE File; // [esp+4h] [ebp-20h] BYREF

  if ( Format && Buffer )
  {
    File._base = Buffer;
    File._ptr = Buffer;
    File._cnt = 0x7FFFFFFF;
    File._flag = 66;
    v5 = _output_l(&File, Format, (struct localeinfo_struct *)Locale, ArgList);
    v6 = --File._cnt < 0;
    v7 = v5;
    if ( v6 )
      _flsbuf(0, &File);
    else
      *File._ptr = 0;
    return v7;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

