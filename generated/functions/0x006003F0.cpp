// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006003F0 rf_jpeg_jzero_far
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jutils.c:jzero_far matched): Cdecl(target,size_tbytes). Directmemset(target,0,bytes). Flat32-bitimplementation;nofar-segmentlooporallocation. VoidAPI,incidentalEAXtarget;usedbyvirtualarrayprezero.
void *__cdecl rf_jpeg_jzero_far(void *a1, size_t Size)
{
  return memset(a1, 0, Size);
}

