// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D3AD0 rf_renderer_flush_immediate_wrapper
// UNREALRED VERIFIED [renderer-polygons-20261028]: Direct call/return wrapper around rf_renderer_flush_immediate_buffers0x5DF5F0; no additional state or validation.
int rf_renderer_flush_immediate_wrapper()
{
  return rf_renderer_flush_immediate_buffers();
}

