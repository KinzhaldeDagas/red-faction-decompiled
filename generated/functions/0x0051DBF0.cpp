// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051DBF0 rf_geomod_corner_primary_uv_component
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl corner,axis. axis==0 loadsF32 corner+4 (U), ANY nonzero loads+8 (V), returns viaFLD/x87. No clamp to0..1 or validation. Does not address secondaryUV12/16.
double __cdecl rf_geomod_corner_primary_uv_component(int a1, int a2)
{
  if ( a2 )
    return *(float *)(a1 + 8);
  else
    return *(float *)(a1 + 4);
}

