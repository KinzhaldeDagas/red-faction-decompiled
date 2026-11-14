// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF0E0 rf_collision_static_triangle_dispatch_radius
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl passes six arguments unchanged to static sphere-triangle test5CF280 if query radius+72>=~1e-4,else static ray-triangle5CF140. No radius clamp;negative radii take ray branch after outer broadphase may have shrunk bounds. Threshold differs from skinned triangle helper,which uses radius>0.025.
char __cdecl rf_collision_static_triangle_dispatch_radius(int a1, _DWORD *a2, int a3, int a4, int a5, int a6)
{
  if ( *(float *)(a4 + 72) >= 0.00009999999747378752 )
    return rf_collision_static_triangle_sphere(a1, a2, a3, a4, a5, a6);
  else
    return rf_collision_static_triangle_ray(a1, a2, a3, a4, a5, a6);
}

