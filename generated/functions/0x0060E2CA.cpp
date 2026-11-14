// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E2CA __getptd_noexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, returns existing/new PTD orNULL without own
// fatal exit. Save GetLastError FIRST; push LIVE provider index6650C0, obtain getter function from set_flsgetvalue, indirect stdcall getter(index). NonNULL PTD reused without
// validation. NULL ->calloc_crt(1,532); allocationNULL returnsNULL. New allocation: decode20213B8 setter and stdcall setter(index,PTD) BEFORE initptd. SetterFALSE frees allocation
// andreturnsNULL. SetterTRUE callsinitptd(PTD,NULL), setsPTD+4=-1 andPTD+0=GetCurrentThreadId. Every normal return calls SetLastError(original), even allocation/cache failure; errno
// can change through delegates. No own exception-finally, so LastError restoration and installed-pointer rollback are not promised if a helper throws.
DWORD *_getptd_noexit()
{
  DWORD LastError; // eax
  DWORD v1; // edi
  int (__stdcall *v2)(int); // eax
  DWORD *v3; // esi
  int v4; // eax
  int (__stdcall *v5)(int, int); // eax
  DWORD CurrentThreadId; // eax
  int v8; // [esp-8h] [ebp-10h]
  int v9; // [esp-4h] [ebp-Ch]
  int v10; // [esp-4h] [ebp-Ch]

  LastError = GetLastError();
  v9 = dword_6650C0;
  v1 = LastError;
  v2 = (int (__stdcall *)(int))__set_flsgetvalue();
  v3 = (DWORD *)v2(v9);
  if ( !v3 )
  {
    v4 = _calloc_crt(1u, 532);
    v3 = (DWORD *)v4;
    if ( v4 )
    {
      v10 = v4;
      v8 = dword_6650C0;
      v5 = (int (__stdcall *)(int, int))_decode_pointer(MEMORY[0x20213B8]);
      if ( v5(v8, v10) )
      {
        _initptd(v3, nullptr);
        CurrentThreadId = GetCurrentThreadId();
        v3[1] = -1;
        *v3 = CurrentThreadId;
      }
      else
      {
        free(v3);
        v3 = nullptr;
      }
    }
  }
  SetLastError(v1);
  return v3;
}

