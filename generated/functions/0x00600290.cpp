// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600290 rf_jpeg_free_large
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_free_large matched): Cdecl(cinfo,object,size_tbytes),THREEargumentsverifiedatfree_pool0x5FF1B9..1C7. Bodyfree(object),ignorescinfo/size;oldtwo-argprototypewasincomplete. No poolunlink/accountingorNULLspecialcaselocally;APIvoid.
void __cdecl rf_jpeg_free_large(void *cinfo, void *object, unsigned int bytes)
{
  free(object);
}

