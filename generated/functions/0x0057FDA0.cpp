// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057FDA0 rf_renderer_debug_endpoint_arrow_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Cdecl six scalar floats(startXYZ,endXYZ),three color DWORDs. Backend102 forwards all9 values unchanged to verified debug endpoint-arrow renderer;other backend returns void without drawing. Does not independently set global alpha or build geometry.
void __cdecl rf_renderer_debug_endpoint_arrow_backend_wrapper(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        int a7,
        int a8,
        int a9)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_draw_debug_endpoint_arrow(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

