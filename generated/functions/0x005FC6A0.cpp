// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC6A0 rf_jpeg_abort_compress
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_abort_compress matched): Recovered original0x5FC6A0..0x5FC6B1. Thin cdecl wrapper to common jpeg_abort0x5FF2B0. Releases image pool but retains permanent configuration/tables;resets compress state100 when mem exists. Does not write EOI,flush FILE or freecinfo. APIvoid.
void __cdecl rf_jpeg_abort_compress(void *cinfo)
{
  rf_jpeg_abort(cinfo);
}

