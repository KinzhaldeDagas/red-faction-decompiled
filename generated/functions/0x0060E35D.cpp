// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E35D __freefls@4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall PTD cleanup callback, RET4, NULL no-op. Free
// nonNULL pointers in offsets36,44,52,60,64,68,72 in that order, without clearing fields. Offset92 pointer freed whenever !=static64E860, evenNULL (free handlesNULL). Lock13/SEH:
// ifmbinfo+104 nonNULL InterlockedDecrement refcount; zero andnotstatic665468 ->free mbinfo. Finallyunlock13. Lock12/SEH: locinfo+108 nonNULL ->removelocaleref; free viafreetlocinfo
// only if pointer differs LIVE665A70 andstatic665998 and firstDWORDrefcount==0. Finallyunlock12; thenfree PTD itself. Refcount/owned-buffer internals delegated, no TLS-slot clear,
// field reset, duplicate-pointer validation or whole-object finally-free if an earlier helper throws. Scopes independently enclose-2.
void __stdcall _freefls(void *Block)
{
  void *v1; // edi
  char *v2; // edi
  int savedregs; // [esp+28h] [ebp+0h]

  if ( Block )
  {
    if ( *((_DWORD *)Block + 9) )
      free(*((void **)Block + 9));
    if ( *((_DWORD *)Block + 11) )
      free(*((void **)Block + 11));
    if ( *((_DWORD *)Block + 13) )
      free(*((void **)Block + 13));
    if ( *((_DWORD *)Block + 15) )
      free(*((void **)Block + 15));
    if ( *((_DWORD *)Block + 16) )
      free(*((void **)Block + 16));
    if ( *((_DWORD *)Block + 17) )
      free(*((void **)Block + 17));
    if ( *((_DWORD *)Block + 18) )
      free(*((void **)Block + 18));
    if ( *((_UNKNOWN **)Block + 23) != &unk_64E860 )
      free(*((void **)Block + 23));
    _lock(13);
    v1 = *((void **)Block + 26);
    if ( v1 && !InterlockedDecrement(*((volatile LONG **)Block + 26)) && v1 != &unk_665468 )
      free(v1);
    _unlock(13);
    _lock(12);
    v2 = *((char **)Block + 27);
    if ( v2 )
    {
      __removelocaleref(*((volatile LONG **)Block + 27));
      if ( v2 != (char *)off_665A70 && v2 != (char *)&unk_665998 && !*(_DWORD *)v2 )
        __freetlocinfo(v2);
    }
    savedregs = 6349925;
    _unlock(12);
    free(Block);
  }
}

