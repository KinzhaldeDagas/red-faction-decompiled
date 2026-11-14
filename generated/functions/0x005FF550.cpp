// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF550 rf_jpeg_marker_emit_2bytes
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_2bytes matched): Emitsbits8..15 ofvalue thenbits0..7 viaemit_byte. Thus big-endianlow16bits;higherbitsignored,signedpromotionofhighchar doesnotchangeemittedbyte. No ownrangecheck orbufferallocation;voidAPI.
int __cdecl rf_jpeg_marker_emit_2bytes(_DWORD *a1, __int16 a2)
{
  rf_jpeg_marker_emit_byte(a1, SHIBYTE(a2));
  return rf_jpeg_marker_emit_byte(a1, a2);
}

