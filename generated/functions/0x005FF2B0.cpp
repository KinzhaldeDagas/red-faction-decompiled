// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF2B0 rf_jpeg_abort
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcomapi.c:jpeg_abort matched): Cdeclcommoncinfo. Ifmem4NULL,no-op. Otherwisefree_pool callbackmem+36 forpool1only(retainspermanent0). Ifis_decompressor16nonzero,state20=200 andmarker_list304=NULL;elsecompressstate100. Does notcloseFILE,emitEOI orfreememmanager/cinfo;APIvoid.
_DWORD *__cdecl rf_jpeg_abort(_DWORD *a1)
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = a1;
  if ( a1[1] )
  {
    for ( i = 1; i > 0; --i )
      result = (_DWORD *)(*(int (__cdecl **)(_DWORD *, int))(a1[1] + 36))(a1, i);
    if ( a1[4] )
    {
      a1[5] = 200;
      a1[76] = 0;
      return a1;
    }
    else
    {
      a1[5] = 100;
    }
  }
  return result;
}

