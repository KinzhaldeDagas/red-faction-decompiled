// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604A10 rf_jpeg_color_null_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:null_method matched): No-op color start-pass callback with one unused cdecl cinfo argument. Used when conversion needs no RGB lookup initialization. The old inferred no-argument prototype was incomplete.
void __cdecl rf_jpeg_color_null_start_pass(void *cinfo)
{
  ;
}

