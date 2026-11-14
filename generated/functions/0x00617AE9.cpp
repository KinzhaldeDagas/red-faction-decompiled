// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617AE9 _parse_cmdline
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal ABI EDX=input char*,EDI=byteCountOut;
// stack(argvOut optional,characterStorage optional,slotCountOut), caller cleans12. Reset byteCount0,slotCount1 (program argv slot); optionally emit argv[0]=storage. First program
// token: quotes toggle mode and are omitted, backslashes ordinary; copy/count every other byte incl terminating NUL or delimiter space/tab, overwrite copied delimiter with NUL. DBCS
// lead consumes/counts second byte without trail validation. Empty input still creates empty program argument. Remaining args skip ONLY space/tab; increment slotcount each arg and
// optionally store pointer. Backslash runs before quote: emit floor(n/2) backslashes; odd n copies literal quote, even n toggles quote mode except doubled quote INSIDE quote mode
// consumes first and emits one literal second quote. Without following quote, emit all backslashes. NUL or unquoted space/tab ends arg; append/count NUL. Ordinary emitted DBCS lead
// consumes/counts second byte; argument path passes SIGN-EXTENDED byte to ismbblead, program path zero-extends. Same counting logic with storageNULL supports sizing pass; argv
// optional independently. Finally optionally argv[next]=NULL, increment slotcount for terminator; EAX returns argv cursor (NULL in count-only mode), NOT argc. No own validation,
// capacities, allocation, overflow checks, or malformed DBCS protection.
char **__usercall parse_cmdline@<eax>(char *a1@<edx>, _DWORD *a2@<edi>, char **a3, char *a4, _DWORD *a5)
{
  _DWORD *v5; // ecx
  char *v7; // edx
  char **v8; // ebx
  char v9; // bl
  char *v10; // ecx
  char **v11; // eax
  int v12; // ebx
  unsigned int v13; // ecx
  char v14; // al
  char *v15; // ecx
  char *v16; // ecx
  char **result; // eax
  unsigned int v18; // [esp-4h] [ebp-10h]
  BOOL v19; // [esp+8h] [ebp-4h]
  BOOL v20; // [esp+8h] [ebp-4h]

  v5 = a5;
  *a2 = 0;
  v7 = a4;
  *a5 = 1;
  if ( a3 )
  {
    v8 = a3++;
    *v8 = a4;
  }
  v19 = 0;
  do
  {
    if ( *a1 == 34 )
    {
      v9 = 34;
      ++a1;
      v19 = !v19;
    }
    else
    {
      ++*a2;
      if ( v7 )
      {
        *v7 = *a1;
        a4 = v7 + 1;
      }
      v9 = *a1;
      v18 = (unsigned __int8)*a1++;
      if ( _ismbblead(v18) )
      {
        ++*a2;
        if ( a4 )
        {
          v10 = a4++;
          *v10 = *a1;
        }
        ++a1;
      }
      v7 = a4;
      v5 = a5;
      if ( !v9 )
      {
        --a1;
        goto LABEL_18;
      }
    }
  }
  while ( v19 || v9 != 32 && v9 != 9 );
  if ( v7 )
    *(v7 - 1) = 0;
LABEL_18:
  v20 = 0;
  while ( *a1 )
  {
    while ( *a1 == 32 || *a1 == 9 )
      ++a1;
    if ( !*a1 )
      break;
    if ( a3 )
    {
      v11 = a3++;
      *v11 = v7;
    }
    ++*v5;
    while ( 1 )
    {
      v12 = 1;
      v13 = 0;
      while ( *a1 == 92 )
      {
        ++a1;
        ++v13;
      }
      if ( *a1 == 34 )
      {
        if ( (v13 & 1) == 0 )
        {
          if ( v20 && a1[1] == 34 )
          {
            ++a1;
          }
          else
          {
            v12 = 0;
            v20 = !v20;
          }
        }
        v13 >>= 1;
      }
      if ( v13 )
      {
        do
        {
          --v13;
          if ( v7 )
            *v7++ = 92;
          ++*a2;
        }
        while ( v13 );
        a4 = v7;
      }
      v14 = *a1;
      if ( !*a1 || !v20 && (v14 == 32 || v14 == 9) )
        break;
      if ( v12 )
      {
        if ( v7 )
        {
          if ( _ismbblead(v14) )
          {
            v15 = a4++;
            *v15 = *a1++;
            ++*a2;
          }
          v16 = a4++;
          *v16 = *a1;
        }
        else if ( _ismbblead(v14) )
        {
          ++a1;
          ++*a2;
        }
        ++*a2;
        v7 = a4;
      }
      ++a1;
    }
    if ( v7 )
    {
      *v7++ = 0;
      a4 = v7;
    }
    ++*a2;
    v5 = a5;
  }
  result = a3;
  if ( a3 )
    *a3 = nullptr;
  ++*v5;
  return result;
}

