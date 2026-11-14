// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611967 __mtdeletelocks
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, two full36-entry passes over665280..6653A0
// exclusive. First: pointer nonNULL ANDkind!=1 ->DeleteCriticalSection(pointer),free(pointer),clear pointer0. Second: pointer nonNULL ANDkind==1 ->DeleteCriticalSection(pointer), but
// retain pointer andkind. Static objects are not freed; dynamic records are cleared. No lock, caller quiescence/held-state check, exception catch or status. Repeated teardown can
// Delete static CS again because those pointers remain nonNULL. Dynamic-first order is literal native behavior, not a single mixed pass.
void _mtdeletelocks()
{
  LPCRITICAL_SECTION *v0; // esi
  LPCRITICAL_SECTION v1; // edi
  LPCRITICAL_SECTION *v2; // esi

  v0 = &lpCriticalSection;
  do
  {
    v1 = *v0;
    if ( *v0 && v0[1] != (LPCRITICAL_SECTION)1 )
    {
      DeleteCriticalSection(*v0);
      free(v1);
      *v0 = nullptr;
    }
    v0 += 2;
  }
  while ( (int)v0 < (int)dword_6653A0 );
  v2 = &lpCriticalSection;
  do
  {
    if ( *v2 )
    {
      if ( v2[1] == (LPCRITICAL_SECTION)1 )
        DeleteCriticalSection(*v2);
    }
    v2 += 2;
  }
  while ( (int)v2 < (int)dword_6653A0 );
}

