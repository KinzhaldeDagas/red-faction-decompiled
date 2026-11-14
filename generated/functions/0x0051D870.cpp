// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D870 rf_uv_distance_xyxy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl four BY-VALUE float arguments x1,y1,x2,y2, caller pop16. Store dx=x2-x1 and dy=y2-y1 F32, construct local vec2, call558A90 and return its x87 floating value directly with no FSTP. That helper F32-rounds dx*dx+dy*dy then sqrt. Original stored void declaration was false: recovered51D6A0 calls three times and immediately FSTPs each result. No pointer arguments, squared-distance return or normalization.
double __cdecl rf_uv_distance_xyxy(float x1, float y1, float x2, float y2)
{
  float v5; // [esp+8h] [ebp-10h]
  float v6; // [esp+Ch] [ebp-Ch]
  float v7[2]; // [esp+10h] [ebp-8h] BYREF

  v6 = y2 - y1;
  v5 = x2 - x1;
  rf_vector2_assign_components(v7, v5, v6);
  return rf_vector2_length(v7);
}

