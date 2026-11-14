// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CF9E0 rf_segment_plane_front_side_hit_fraction
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start vector,direction vector,plane4,output fraction. Computes d=float(-plane_point_signed_distance(plane,start)),q=float(dot(direction,plane normal)). For ordered values requires d>=0,d<=q,q>0, then writes float(d/q),returnsAL1; failed gate returns0 without output write. Native unordered gates differ from pseudocode: first d>=0 test admits unordered, d>q rejects ONLY ordered greater, final q>0 admits unordered. Consequently NaN d/q may be written with success; no finite/normalization, pointer, polygon or explicit extra0..1 clamp. No ray endpoint argument; finite admitted interval follows those three tests.
char __cdecl rf_segment_plane_front_side_hit_fraction(float *a1, float *a2, float *a3, float *a4)
{
  float v5; // [esp+0h] [ebp-8h]
  float v6; // [esp+4h] [ebp-4h]

  v5 = -rf_plane_point_signed_distance(a3, a1);
  if ( v5 < 0.0 )
    return 0;
  v6 = rf_vector_dot(a2, a3);
  if ( v5 > (double)v6 || v6 <= 0.0 )
    return 0;
  *a4 = v5 / v6;
  return 1;
}

