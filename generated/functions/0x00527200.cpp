// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527200 rf_light_get_ambient_rgb_floats
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Copies globals0x663B1C/20/24 into threecallerfloatoutputs; returns firstoutputpointer. No scaling,clamping or active-light query.
float *__cdecl rf_light_get_ambient_rgb_floats(float *a1, float *a2, float *a3)
{
  *a1 = flt_663B1C;
  *a2 = flt_663B20;
  *a3 = flt_663B24;
  return a1;
}

