// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581410 rf_renderer_set_depth_fade_start_distance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl float. Ordered input>1 stores18CD378=input;otherwise writes0 (including NaN per x87 status test). Always invokes backend clip-plane rebuild581180,which computes scaled fade-start18CD37C=18CD3C4*18CD378 on backend102. Does not set far-plane enable18CD369 or change far distance18CD36C. Nominal EAX inherited from wrapper,not a defined success result.
int __cdecl rf_renderer_set_depth_fade_start_distance(float a1)
{
  if ( a1 <= 1.0 )
    flt_18CD378 = 0.0;
  else
    flt_18CD378 = a1;
  return rf_renderer_rebuild_world_clip_planes_backend_wrapper();
}

