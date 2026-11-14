// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006002C0 rf_jpeg_open_backing_store
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_open_backing_store matched): Cdecl(cinfo,backingStoreState,longtotalBytes). No-backing-storeplatform:setsfatalerror49 NoBackingStore,callserr.error_exit(cinfo). No filecreation,allocation,read/write/closecallbackinstallationorstatusreturn. Unusedsecond/thirdargumentsarepartofsourceandverifiedcallerABI,thougholdtypeonlyshowedcinfo. Defaultcallbackexits;mustnotreturnnormally.
void __cdecl rf_jpeg_open_backing_store(void *cinfo, void *backing_store, int total_bytes)
{
  *(_DWORD *)(*(_DWORD *)cinfo + 20) = 49;
  (**(void (__cdecl ***)(void *))cinfo)(cinfo);
}

