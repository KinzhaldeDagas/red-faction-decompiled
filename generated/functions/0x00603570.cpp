// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603570 rf_jpeg_downsample_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:start_pass_downsample matched): No-op start-pass callback with one unused cdecl cinfo argument. The old no-argument inferred prototype omitted this callback ABI argument.
void __cdecl rf_jpeg_downsample_start_pass(void *cinfo)
{
  ;
}

