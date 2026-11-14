// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600230 rf_jpeg_get_small
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_get_small matched): Cdecl(cinfo,size_tbytes). Ignorescinfo,returnsmalloc(bytes). No zeroing,poolbookkeepingorerrorcallback;NULLpropagates tocaller. Flat32-bitplatformallocation,notC++new.
void *__cdecl rf_jpeg_get_small(void *cinfo, unsigned int bytes)
{
  return malloc(bytes);
}

