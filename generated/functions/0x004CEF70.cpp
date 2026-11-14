// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEF70 rf_particle_emitter_draw_extent_debug
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Recovered standalone original function [0x4CEF70,0x4CF00A), cdecl noargs, no currently recorded incoming xrefs. Invokes two no-op local vector constructors, then gates on DWORD
// 0x662DF8 nonzero. Walks active emitters from head 0x867A50 to sentinel BASE 0x867908 via next +328. For signed parent/index +4>=0, source-frame helper 0x4CD460 computes current
// world source position/direction; sets global render color RGBA(255,0,0,255), then draws wire sphere centered on that source position with radius FLOAT emitter+156 and render state
// DWORD 0x187CC5C. Direction output is unused. No particle rendering, radius recomputation, sign/finite check, or restoration of prior render color. Function recovery changes only
// IDA's function definition, not the original instructions.
void __cdecl rf_particle_emitter_draw_extent_debug()
{
  int i; // [esp+8h] [ebp-1Ch]
  float v1[3]; // [esp+Ch] [ebp-18h] BYREF
  float v2[3]; // [esp+18h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v1);
  rf_vector3_default_construct_noop(v2);
  if ( dword_662DF8 )
  {
    for ( i = dword_867A50; (int *)i != dword_867908; i = *(_DWORD *)(i + 328) )
    {
      if ( rf_particle_emitter_has_nonnegative_parent_index((_DWORD *)i) )
      {
        sub_4CD460(i, v1, v2);
        rf_render_color_set_rgba8(255, 0, 0, 255);
        rf_debug_draw_wire_sphere_backend_dispatch((int)v1, *(float *)(i + 156), dword_187CC5C);
      }
    }
  }
}

