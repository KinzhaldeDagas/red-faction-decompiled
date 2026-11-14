// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF320 rf_jpeg_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcomapi.c:jpeg_destroy matched): Ifmem4nonNULL,callself_destructcallbackmem+40. Alwaysmem4=NULL,state20=0. No cinfo allocationfree,FILEclose orpermanent state preservation. APIvoid;incidentalEAXcinfo.
int __cdecl rf_jpeg_destroy(int a1)
{
  if ( *(_DWORD *)(a1 + 4) )
    (*(void (__cdecl **)(int))(*(_DWORD *)(a1 + 4) + 40))(a1);
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  return a1;
}

