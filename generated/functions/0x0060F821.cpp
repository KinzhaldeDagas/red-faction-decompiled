// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F821 ??0exception@std@@QAE@ABV01@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall destination plus source exception pointer, RET4,return self. Set std::exception vtable then copy fullDWORD ownership source+8 toself+8. Ownership0:
// copy message pointer source+4 verbatim (borrowed). Nonzero ownership and source message nonNULL: strlen+1 wrapped,malloc,store new pointer evenNULL; successful allocation strcpy_s
// with LIVE source message and extent,ignore copy status. Nonzero ownership with NULL message sets destination messageNULL. No source/destination NULL/alias validation, old-message
// free or containing allocation. Self-copy of owned message overwrites source pointer before re-fetch for strcpy_s, so no self-copy safety promise. Allocation failure leaves copied
// ownership flag withNULL pointer and still returns self.
std::exception *__thiscall std::exception::exception(std::exception *this, const struct std::exception *a2)
{
  int v3; // eax
  bool v4; // zf
  int v5; // eax
  size_t v6; // edi
  char *v7; // eax

  *(_DWORD *)this = &std::exception::`vftable';
  v3 = *((_DWORD *)a2 + 2);
  *((_DWORD *)this + 2) = v3;
  v4 = v3 == 0;
  v5 = *((_DWORD *)a2 + 1);
  if ( v4 )
  {
    *((_DWORD *)this + 1) = v5;
  }
  else if ( v5 )
  {
    v6 = strlen(*((const char **)a2 + 1)) + 1;
    v7 = (char *)malloc(v6);
    *((_DWORD *)this + 1) = v7;
    if ( v7 )
      strcpy_s(v7, v6, *((const char **)a2 + 1));
  }
  else
  {
    *((_DWORD *)this + 1) = 0;
  }
  return this;
}

