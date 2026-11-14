// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C58F0 rf_renderer_set_linear_mip_filter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): CORRECTION to false CRT _flushall label: calls renderer filter dispatcher573CC0 with selector1. Backend102 dispatches this to D3D stage0 MIPFILTER state18 value2 (linear). Does not flush C streams; no arguments. Return EAX follows dispatcher.
int __cdecl rf_renderer_set_linear_mip_filter()
{
  return rf_renderer_set_mip_filter_backend_dispatch(1);
}

