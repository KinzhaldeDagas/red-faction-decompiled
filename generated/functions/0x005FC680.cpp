// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC680 rf_jpeg_destroy_compress
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_destroy_compress matched): Cdecl cinfo,thin wrapper to jpeg_destroy0x5FF320. Destroys memory manager/pools and marks state0;does not free application-owned cinfo structure or close destination FILE. APIvoid,incidental return forwarded.
int __cdecl rf_jpeg_destroy_compress(int a1)
{
  return rf_jpeg_destroy(a1);
}

