// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571C00 rf_renderer_get_viewport_width
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Returns effective viewport width187CCC4; this may differ from physical screen width after clipping.
int rf_renderer_get_viewport_width()
{
  return unk_187CCC4;
}

