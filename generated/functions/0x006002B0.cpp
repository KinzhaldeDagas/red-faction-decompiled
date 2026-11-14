// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006002B0 rf_jpeg_mem_available
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_mem_available matched): Cdecl(cinfo,longmin,longmax,longalreadyAllocated),FOURargumentssource/callerverified:realize_virt_arrays pushesmanager.total76,max,min,cinfo andcleans16bytes. BodyreturnsTHIRDargumentmaxunchanged;ignoresallothers. ItdoesnotqueryOSmemoryorhonormanager.max_memory_to_use/JPEGMEMbudget. Priorstd::_Unchecked vector-iteratorFLIRTlabelandthree-argumentinferredtypewerefalse;correctedname/prototype. No STLsemantics.
int __cdecl rf_jpeg_mem_available(void *cinfo, int min_bytes, int max_bytes, int already_allocated)
{
  return max_bytes;
}

