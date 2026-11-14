// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE660 rf_jpeg_request_virt_barray
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:request_virt_barray matched): Cdecl(cinfo,poolID,preZero,blocksPerRow,totalRows,maxAccess). Descriptor128bytes:rowpointerbuffer0,totalRows4,itemsPerRow8,maxAccessRows12,rowsInMemory16,rowsPerChunk20,currentStartRow24,firstUndefinedRow28,preZero32,dirty36,backingStoreOpen40,next44,backingStore callbacks/state48+. Onlybuffer0=NULL,totalRows4,items8,maxAccess12,preZero32,backingOpen40=0,next44initializedhere;otherfieldssetonrealize. RequirespoolID==1 elseerror14;descriptorallocated viaalloc_small inimagepool1,prepended toappropriatevirtuallist. No dimensions/maxaccessvalidation,dataallocation orbackingopen yet. Blocklistheadmanager72;itemsPerRow counts128-byteblocks.
_DWORD *__cdecl rf_jpeg_request_virt_barray(_DWORD *a1, unsigned int a2, int a3, int a4, int a5, int a6)
{
  _DWORD *result; // eax
  int v7; // [esp+0h] [ebp-8h]

  v7 = a1[1];
  if ( a2 != 1 )
  {
    *(_DWORD *)(*a1 + 20) = 14;
    *(_DWORD *)(*a1 + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  result = (_DWORD *)rf_jpeg_alloc_small(a1, a2, 0x80u);
  *result = 0;
  result[1] = a5;
  result[2] = a4;
  result[3] = a6;
  result[8] = a3;
  result[10] = 0;
  result[11] = *(_DWORD *)(v7 + 72);
  *(_DWORD *)(v7 + 72) = result;
  return result;
}

