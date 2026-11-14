// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580B50 rf_volume_sample_contribution
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Recovered cdecl volume pointer,world-point pointer. Tag1 dispatches sphere contribution580BA0,tag2 box contribution580C00;other tags return floating0.0 in ST0. Does not combine RGB,iterate active list or check pointer;requires caches from view preparation. Original standalone bounds580B50..580B96,all already-code instructions.
float __cdecl rf_volume_sample_contribution(const void *a1, const float *a2)
{
  if ( *(_BYTE *)a1 == 1 )
  {
    return rf_volume_sphere_sample_contribution((int)a1, (int)a2);
  }
  else if ( *(_BYTE *)a1 == 2 )
  {
    return rf_volume_box_sample_contribution(a1, a2);
  }
  else
  {
    return 0.0;
  }
}

