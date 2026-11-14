// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CC83 __fcloseall
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Noargs.
// Lockglobal1,armSEH;SIGNEDindex3..<LIVE2022F80,skippingstandard0..2. FornonnullLIVEtable2021F68 entry,flags&0x83 ->fclose;count result!= -1. Regardlessactiveflags/closefailure,
// index>=20 THENDeleteCriticalSection(FILE+32),freeFILE,clearcurrenttableentry0; indices3..19 staticstorage notfreed. Re-fetchtable/slot
// betweendelegates,nosnapshot/decrementoflimit/freeoftable. Outerfinallyunlockglobal1 onnormal/unwind. Return successful-closecount,notnumberfreed; no rollback/continue-on-throw
// catch.
int __cdecl _fcloseall()
{
  int i; // edi
  int v1; // esi
  int *v2; // eax
  int v3; // eax
  int v5; // [esp+14h] [ebp-1Ch]

  v5 = 0;
  _lock(1);
  for ( i = 3; i < dword_2022F80; ++i )
  {
    v1 = 4 * i;
    v2 = (int *)(4 * i + unk_2021F68);
    if ( *v2 )
    {
      v3 = *v2;
      if ( (*(_BYTE *)(v3 + 12) & 0x83) != 0 && fclose((FILE *)v3) != -1 )
        ++v5;
      if ( i >= 20 )
      {
        DeleteCriticalSection((LPCRITICAL_SECTION)(*(_DWORD *)(v1 + unk_2021F68) + 32));
        free(*(void **)(v1 + unk_2021F68));
        *(_DWORD *)(v1 + unk_2021F68) = 0;
      }
    }
  }
  _unlock(1);
  return v5;
}

