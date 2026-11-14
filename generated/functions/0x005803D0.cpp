// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005803D0 rf_renderer_draw_impact_chunk_backend_dispatch
// UNREALRED VERIFIED [impact-callbacks-20261028]: Only when renderer selector0x187CC9C==102 delegates chunk pointer and alpha integer to0x5DD550. Other backends no-op. No input validity/alpha clamp or allocation.
void __cdecl rf_renderer_draw_impact_chunk_backend_dispatch(int a1, int a2)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_impact_chunk_backend_102(a1, a2);
}

