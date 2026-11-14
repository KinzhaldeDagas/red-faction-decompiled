// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EAE0 rf_renderer_tapered_segment_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Cdecl worldEndpointA,FLOAT worldWidthA,worldEndpointB,FLOAT worldWidthB,packedState,maxScreenLength float. Original FLD/FSTP copies full4-byte widths into callee stack slots:old callee char types causing SLOBYTE in pseudocode were WRONG. Backend102 forwards six arguments and returns callee floating ST0 scaled-depth value;unsupported returns0.0. No byte truncation or numeric float-to-char conversion in original instructions.
double __cdecl rf_renderer_tapered_segment_backend_wrapper(
        const float *a1,
        float a2,
        const float *a3,
        float a4,
        unsigned int a5,
        float a6)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_screen_tapered_world_segment(a1, a2, a3, a4, a5, a6);
  else
    return 0.0;
}

