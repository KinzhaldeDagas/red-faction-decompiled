// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578720 rf_bitmap_end_residency_scope_unless_suppressed
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): No args. If suppression BYTE189744D nonzero,returns its zero-extended value. Otherwise calls573470 end-residency-scope with argument0 and returns delegatedEAX. Does not change suppression flag,validate a matching begin or force unconditional cache release.
char rf_bitmap_end_residency_scope_unless_suppressed()
{
  char result; // al

  result = unk_189744D;
  if ( !unk_189744D )
    return rf_renderer_end_texture_residency_scope(0);
  return result;
}

