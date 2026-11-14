// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578700 rf_bitmap_begin_residency_scope_unless_suppressed
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): No args. Zero-extends suppression BYTE189744D toEAX. If nonzero returns raw0..255 without backend call;otherwise calls573450 renderer begin-residency-scope and returns its incidentalEAX. No normalized boolean/readiness/bitmap-manager initialization or counter balancing added.
char rf_bitmap_begin_residency_scope_unless_suppressed()
{
  char result; // al

  result = unk_189744D;
  if ( !unk_189744D )
    return rf_renderer_begin_texture_residency_scope();
  return result;
}

