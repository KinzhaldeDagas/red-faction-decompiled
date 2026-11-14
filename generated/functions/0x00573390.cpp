// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573390 rf_renderer_get_vertex_fog_parameters
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(outRed32,outGreen32,outBlue32,outStartFloat,outEndFloat),five NONNULL output pointers. Zero-extends cached RGB bytes187CCF1/F2/F3 and stores each as FOUR-byte DWORD,not one byte. Copies cached float bounds187CCF8/CCFC even if fog disabled,returns raw enable byte187CCF0 inAL. Setter5732E0 always replaces RGB/enable but invalid/disabled bounds can preserve earlier ranges. No backend query,boolean normalization,NULL/alias validation or recomputation of fog factor.
unsigned __int8 __cdecl rf_renderer_get_vertex_fog_parameters(
        unsigned int *red,
        unsigned int *green,
        unsigned int *blue,
        float *start,
        float *end)
{
  *red = (unsigned __int8)byte_187CCF1;
  *green = (unsigned __int8)byte_187CCF2;
  *blue = (unsigned __int8)byte_187CCF3;
  *start = flt_187CCF8;
  *end = flt_187CCFC;
  return byte_187CCF0;
}

