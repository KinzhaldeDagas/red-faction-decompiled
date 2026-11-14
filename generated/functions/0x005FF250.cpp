// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF250 rf_jpeg_memory_self_destruct
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:self_destruct matched): Cdeclcinfo. Callsfree_pool image1 thenpermanent0;frees84-bytememorymanagerwithjpeg_free_small(cinfo,mem,84),setscinfo.mem4=NULL,platformjpeg_mem_term(cinfo). Doesnotfreecinfoitselforchangeglobalstate20. All platformfreecalls passTHREEargs even thougholdinferredprototypesomittedsize;APIvoid.
void __cdecl rf_jpeg_memory_self_destruct(void **cinfo)
{
  signed int i; // [esp+0h] [ebp-4h]

  for ( i = 1; i >= 0; --i )
    rf_jpeg_free_pool(cinfo, i);
  rf_jpeg_free_small(cinfo, cinfo[1], 0x54u);
  cinfo[1] = nullptr;
  rf_jpeg_mem_term(cinfo);
}

