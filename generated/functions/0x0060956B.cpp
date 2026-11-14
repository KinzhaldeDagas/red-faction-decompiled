// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060956B _printf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Variadic printf. NULLformat ->invalid/-1 before lock. Valid: get fixed
// table664DE0 and add32,lock_file2(index1,stream),armSEH; stbuf(stream) returns temp-buffer flag; output_l(stream,format,NULLlocale,&callerVarargs); save formatter result;
// ftbuf(tempFlag,stream),ignore its result; finally unlock_file2(1,table+32) and return SAVED formatter result. Getter re-called for each receiver, takes ZERO args; three pending
// output_l slots remain during one getter call and are not getter arguments. ADD24 reclaims four output slots plus two ftbuf slots; previous stbuf slot popped separately. SEH finally
// covers unlock only: ftbuf is normal-path work, no temp rollback if formatter throws. Repairing getter60CDDE false variadic prototype makes this original body decompile without
// code/SP changes. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths
// retain their separately described policy.
int printf(const char *const Format, ...)
{
  void *v2; // eax
  FILE *v3; // eax
  int v4; // edi
  FILE *v5; // eax
  FILE *v6; // eax
  void *v7; // eax
  int v8; // [esp+10h] [ebp-1Ch]
  va_list va; // [esp+38h] [ebp+Ch] BYREF

  va_start(va, Format);
  if ( Format )
  {
    v2 = crt_return_static_address_00664de0();
    _lock_file2(1, (int)v2 + 32);
    v3 = (FILE *)crt_return_static_address_00664de0();
    v4 = _stbuf(v3 + 1);
    v5 = (FILE *)crt_return_static_address_00664de0();
    v8 = _output_l(v5 + 1, Format, nullptr, va);
    v6 = (FILE *)crt_return_static_address_00664de0();
    _ftbuf(v4, v6 + 1);
    v7 = crt_return_static_address_00664de0();
    _unlock_file2(1, (int)v7 + 32);
    return v8;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

