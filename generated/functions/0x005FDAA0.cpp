// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDAA0 rf_jpeg_stdio_empty_output_buffer
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jdatadst.c:empty_output_buffer matched): Writesexact4096 bytes(buffer24) toFILE20 viafwrite(size1,count4096). Shortwrite invokesfatalerror37 FileWrite. Resetsnext_output_byte0=buffer,free_in_buffer4=4096,returnsTRUE1. Thisdestination neveroffers suspension;FILE remainsopen.
int __cdecl rf_jpeg_stdio_empty_output_buffer(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = a1[6];
  if ( fwrite(*(const void **)(v2 + 24), 1u, 0x1000u, *(FILE **)(v2 + 20)) != 4096 )
  {
    *(_DWORD *)(*a1 + 20) = 37;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  *(_DWORD *)v2 = *(_DWORD *)(v2 + 24);
  *(_DWORD *)(v2 + 4) = 4096;
  return 1;
}

