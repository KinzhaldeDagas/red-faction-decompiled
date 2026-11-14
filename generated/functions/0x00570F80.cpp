// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570F80 rf_renderer_get_depth_buffer_mode
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. Returns raw DWORD187CD1C throughEAX. Generic context initializer sets1;D3D initializer resets0. Verified packed-state mapping5D2786 uses0->D3DZB_TRUE,1->D3DZB_USEW,2->D3DZB_FALSE. This is depth-mode state,not renderer readiness. No validation or normalization.
int __cdecl rf_renderer_get_depth_buffer_mode()
{
  return dword_187CD1C;
}

