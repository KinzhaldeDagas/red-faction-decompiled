// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600270 rf_jpeg_get_large
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_get_large matched): Cdecl(cinfo,size_tbytes),returnsmalloc(bytes),cinfoignored. Sameflatallocatorassmall;nofar-segmentlogic,zeroingorerrorcallback. Calleradds12-bytepoolheaderandtracksownership.
void *__cdecl rf_jpeg_get_large(void *cinfo, unsigned int bytes)
{
  return malloc(bytes);
}

