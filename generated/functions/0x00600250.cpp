// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600250 rf_jpeg_free_small
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_free_small matched): Cdecl(cinfo,object,size_tbytes). THREE-argumentABIverifiedfree_pool pushesbytes/object/cinfo andcleans12. Bodyignorescinfo/bytesandcallsfree(object). Previousinferredtwo-argtypeomittedunusedsize;correctedprototypepreservesactualcallerstackflow. No poolaccountinghere;APIvoid.
void __cdecl rf_jpeg_free_small(void *cinfo, void *object, unsigned int bytes)
{
  free(object);
}

