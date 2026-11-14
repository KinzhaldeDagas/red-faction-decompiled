// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581740 rf_clip_outcode_enable_all_bits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Stores0xFF to global byte663F38,then returns void. Used by renderer instance-transform push;camera outcode routine treats this byte as a boolean enable gate: any nonzero enables all ordinary bits, not a per-bit mask. Does not rebuild planes or change projection mode.
// [UnrealRed retained room-view state 2026-11-12; full original-byte writer/callee closure] Sets renderer clip-enable byte663F38 toFF.5C5210 treats ANY NONZERO as enabled; an inherited mask-bit interpretation is incorrect. Preserve this exact boolean consumer contract rather than assigning semantic clip-plane mask bits to this byte.
void rf_clip_outcode_enable_all_bits()
{
  byte_663F38 = -1;
}

