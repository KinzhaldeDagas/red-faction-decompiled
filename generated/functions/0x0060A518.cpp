// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A518 _doexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(exitCode,quickFlag,returnToCaller). Acquire
// CRT lock8, install EH4 finally ENTRY60A62C (body60A62F). If global2021380==1 skip cleanup; otherwise set202137C=1, store LOW BYTE of returnToCaller at2021378. Full cleanup
// quickFlag0: decode global begin2022F90/end2022F8C; if begin nonNULL scan slots backward from end-4 while unsigned cursor>=begin. Skip dynamic encoded_null values; otherwise decode
// slot, replace slot with encoded_null BEFORE calling decoded noargs callback, ignoring return. After EACH callback re-decode live begin/end; if either changed, adopt pair and
// restart from current end, incorporating appended callbacks/reallocation. No callback-array free, global end decrement/reset, or own decoded-NULL/bounds validation. Full cleanup
// then __initterm [630F50,630F5C), original three slots {0,621F25,60CE95}. Both quick/full run __initterm [630F60,630F64), original one NULL slot. Finally unlock8 ONLY if FULL
// returnToCaller!=0. Nonzero returns; zero sets2021380=1, explicitly unlocks8, then crtExitProcess(exitCode), noreturn. On unwind returnToCaller0 leaves lock8 held; nonzero unlocks.
// No own catch/rollback; processing202137C is not a reentrancy guard. Returning cleanup may rerun terminator spans; callbacks already cleared are skipped.
void __cdecl doexit(UINT uExitCode, int a2, int a3)
{
  void **v3; // edi
  void **v4; // esi
  void (*v5)(void); // edi
  void **v6; // edi
  void **v7; // eax
  void **v8; // [esp+10h] [ebp-28h]
  void **v9; // [esp+18h] [ebp-20h]
  void **v10; // [esp+1Ch] [ebp-1Ch]

  _lock(8);
  if ( unk_2021380 != 1 )
  {
    unk_202137C = 1;
    unk_2021378 = a3;
    if ( !a2 )
    {
      v3 = (void **)_decode_pointer(dword_2022F90);
      v8 = v3;
      if ( v3 )
      {
        v4 = (void **)_decode_pointer(dword_2022F8C);
        v10 = v3;
        v9 = v4;
        while ( --v4 >= v3 )
        {
          if ( *v4 != _encoded_null() )
          {
            if ( v4 < v3 )
              break;
            v5 = (void (*)(void))_decode_pointer(*v4);
            *v4 = _encoded_null();
            v5();
            v6 = (void **)_decode_pointer(dword_2022F90);
            v7 = (void **)_decode_pointer(dword_2022F8C);
            if ( v10 != v6 || v9 != v7 )
            {
              v10 = v6;
              v8 = v6;
              v9 = v7;
              v4 = v7;
            }
            v3 = v8;
          }
        }
      }
      _initterm(&unk_630F50, (void *)&dword_630F5C);
    }
    _initterm(&unk_630F60, (void *)&dword_630F64);
  }
  if ( a3 )
    _unlock(8);
  if ( !a3 )
  {
    unk_2021380 = 1;
    _unlock(8);
    __crtExitProcess(uExitCode);
  }
}

