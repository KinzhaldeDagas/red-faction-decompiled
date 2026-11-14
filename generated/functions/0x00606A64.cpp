// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606A64 _sprintf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl variadic(Buffer,Format,...), returns raw
// output_l result. Validate Format FIRST,then Buffer; NULL ->errno22,invalid_parameter5zeros,-1 if handler returns, WITHOUT clearing valid Buffer. Partial32-byte stack FILE
// initializes ptr=base=Buffer,cnt7FFFFFFF,flags42h; fd,charbuf,bufsiz,tmpname UNINITIALIZED. String flag40 bypasses descriptor checks. Vararg cursor=address first optional stack slot
// EBP+16; output_l(&FILE,Format,NULLlocale,cursor),pop16. Regardless formatter result, decrement FILE.cnt for terminator: nonnegative ->store NUL at current ptr without advancing;
// negative ->flsbuf(0,&FILE), IGNORE result. Preserve formatter result through ESI. Attempts termination after partial errors but failed flsbuf does not guarantee NUL. No real
// buffer-size argument/check, whole-FILE zeroing, lock, locale snapshot,cookie,caller va-list writeback,output rollback or success errno reset.
int sprintf(char *const Buffer, const char *const Format, ...)
{
  int v3; // eax
  bool v4; // sf
  int v5; // esi
  FILE File; // [esp+4h] [ebp-20h] BYREF
  va_list va; // [esp+34h] [ebp+10h] BYREF

  va_start(va, Format);
  if ( Format && Buffer )
  {
    File._base = Buffer;
    File._ptr = Buffer;
    File._cnt = 0x7FFFFFFF;
    File._flag = 66;
    v3 = _output_l(&File, Format, nullptr, va);
    v4 = --File._cnt < 0;
    v5 = v3;
    if ( v4 )
      _flsbuf(0, &File);
    else
      *File._ptr = 0;
    return v5;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

