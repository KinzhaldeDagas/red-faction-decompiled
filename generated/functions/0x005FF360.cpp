// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF360 rf_jpeg_alloc_quant_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcomapi.c:jpeg_alloc_quant_table matched): Allocates132bytesfrompermanentpool0 viasize-smallcallbackmem+0;setssent_table128=FALSE0,returnsJQUANT_TBL*. Does notinitialize64WORDcoefficients orinstallpointerintoanyslot. Assumesmemorymanager/errorpolicyinitialized.
int __cdecl rf_jpeg_alloc_quant_table(int a1)
{
  int result; // eax

  result = (**(int (__cdecl ***)(int, _DWORD, int))(a1 + 4))(a1, 0, 132);
  *(_DWORD *)(result + 128) = 0;
  return result;
}

