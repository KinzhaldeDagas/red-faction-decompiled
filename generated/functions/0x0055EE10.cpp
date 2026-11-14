// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EE10 rf_packed3x4_copy_static_identity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX48byte destination. Copies exactly48 raw bytes from PE6407A8, independently verified as three4float identity rows(1,0,0,0),(0,1,0,0),(0,0,1,0). No allocation, validation or translation-rows conversion. Saved return declaration void; does not construct contiguous3x3-plus-XYZ affine layout.
void __thiscall rf_packed3x4_copy_static_identity(void *this)
{
  qmemcpy(this, &unk_6407A8, 0x30u);
}

