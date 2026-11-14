// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051DFC0 rf_geomod_corner_set_primary_uv_component
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl corner,axis,value; writeF32 to corner+4 when axis==0, else+8 for ANY nonzero. No secondaryUV/geometry mutation or validation. Existing int EAX return is incidental: axis0 leaves corner pointer inEAX, nonzero branch usesECX and does not defineEAX. Caller51DC10 ignores return.
int __cdecl rf_geomod_corner_set_primary_uv_component(int a1, int a2, float a3)
{
  int result; // eax

  if ( a2 )
  {
    *(float *)(a1 + 8) = a3;
  }
  else
  {
    *(float *)(a1 + 4) = a3;
    return a1;
  }
  return result;
}

