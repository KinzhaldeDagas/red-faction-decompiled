// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005813D0 rf_renderer_set_far_clip_distance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Ordered distance>1 sets flag18CD369=1 and distance18CD36C=input;otherwise flag0 and distance0 (NaN also clears by assembly status test). Always calls backend wrapper581180 to rebuild world clip planes. This controls optional far plane,not fog density;no max or finite validation.
// [UnrealRed retained room-view state 2026-11-12; full original-byte caller closure] Ordered input>1 enables far flag18CD369 and stores raw36C=input; otherwise(including NaN) disables flag and stores raw36C=0. Calls581180->5C4540 to rebuild planes only; leaves view-scaled matrix/depth projection state intact.442BC0 mainview sets base far before camera setup then may override after camera for liquid/globalfog/levelcustom conditions.
int __cdecl rf_renderer_set_far_clip_distance(float a1)
{
  if ( a1 <= 1.0 )
  {
    byte_18CD369 = 0;
    flt_18CD36C = 0.0;
  }
  else
  {
    byte_18CD369 = 1;
    flt_18CD36C = a1;
  }
  return rf_renderer_rebuild_world_clip_planes_backend_wrapper();
}

