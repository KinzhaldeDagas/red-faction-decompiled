// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005800E0 rf_renderer_draw_sorted_translucent_faces_view_scope
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Calls442A30(1),conditionally dispatches sorted-translucent context-face renderer when backend102,then442A30(0) unconditionally. Flagscope calls occur even on unsupported backend. No face processing here;no exception cleanup around final scope restoration.
void __cdecl rf_renderer_draw_sorted_translucent_faces_view_scope(int a1)
{
  rf_renderer_apply_or_suspend_level_fog_and_far_clip(1);
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_context_faces_sorted_translucent(a1);
  rf_renderer_apply_or_suspend_level_fog_and_far_clip(0);
}

