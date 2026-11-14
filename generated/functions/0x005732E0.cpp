// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005732E0 rf_renderer_set_vertex_fog
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Always stores RGB bytes and raw enable byte. When enable!=0, start>=0 and start<=end, updates cached bounds and factor255/renderer_scale_camera_depth_bias(end). Invalid bounds leave previous bounds/factor while still replacing RGB/enable. Backend102 immediately applies cached vertex-fog state. CORRECTION to older finite-value wording: there is no finite-value check; +infinity may satisfy these comparisons. NaN fails ordered comparisons; zero start and equal bounds are accepted, including zero end with no division-by-zero guard.
void __cdecl rf_renderer_set_vertex_fog(char a1, char a2, char a3, char a4, float a5, float a6)
{
  rf_color4_set_bytes_return_destination(&byte_187CCF1, a2, a3, a4, 255);
  byte_187CCF0 = a1;
  if ( a1 && a5 >= 0.0 && a5 <= (double)a6 )
  {
    flt_187CCF8 = a5;
    flt_187CCFC = a6;
    unk_187CD00 = 255.0 / rf_renderer_scale_camera_depth_bias(a6);
  }
  if ( dword_187CC9C == 102 )
    rf_d3d8_apply_vertex_fog_state();
}

