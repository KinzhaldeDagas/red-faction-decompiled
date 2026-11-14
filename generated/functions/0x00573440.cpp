// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573440 rf_renderer_get_backend_code
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Returns current renderer backend code187CC9C. No device query.
int rf_renderer_get_backend_code()
{
  return dword_187CC9C;
}

