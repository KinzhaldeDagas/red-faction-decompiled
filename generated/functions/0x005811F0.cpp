// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005811F0 rf_renderer_set_camera_projection_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): When backend code==102, forwards orientation, position, lens, depth-clear control byte and perspective byte to5C4D10. Independently of backend, if cached fog-enable187CCF0 is set, updates fog factor187CD00=255/renderer_scale_camera_depth_bias(fogEnd187CCFC). No denominator guard or immediate fog-state device call here.
void __cdecl rf_renderer_set_camera_projection_dispatch(float *a1, float *a2, float a3, char a4, char a5)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_set_camera_projection_backend102(a1, a2, a3, a4, a5);
  if ( byte_187CCF0 )
    unk_187CD00 = 255.0 / rf_renderer_scale_camera_depth_bias(flt_187CCFC);
}

