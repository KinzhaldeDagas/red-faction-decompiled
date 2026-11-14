// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573F00 rf_bitmap_get_load_context_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): No args. Returns raw byte189744C inAL,partner to setter573F10. No initialization,readiness check,boolean normalization or bitmap lookup;upperEAX bits not meaningful.
char rf_bitmap_get_load_context_byte()
{
  return unk_189744C;
}

