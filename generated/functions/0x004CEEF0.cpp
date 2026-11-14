// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEEF0 rf_particle_emitter_extent_finish_frame
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl noargs. If BYTE 0x662DF4 is zero, leaves all emitters unchanged. Otherwise walks active emitter list head 0x867A50 to sentinel BASE 0x867908 via next +328. Only emitters
// whose signed parent/index DWORD+4>=0 qualify. Writes FLOAT emitter+156 = sqrt_float(FLOAT +160) + FLOAT +72, with final binary32 store, then clears FLOAT +160 to zero.
// Negative-parent emitters retain both fields. No finite/nonnegative check before square root, no world transform or particle traversal here, no initialization/update of origin +164.
// Companion prepare entry 0x4CEE80 is an unconditional native no-op. Particle updater accumulates maximum squared displacement into +160 for these indexed emitters. Return EAX is
// incidental: zero when gate disabled, traversal-dependent otherwise.
int rf_particle_emitter_extent_finish_frame()
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = (unsigned __int8)byte_662DF4;
  if ( byte_662DF4 )
  {
    for ( i = dword_867A50; (int *)i != dword_867908; i = result )
    {
      if ( rf_particle_emitter_has_nonnegative_parent_index((_DWORD *)i) )
      {
        *(float *)(i + 156) = rf_sqrt_float(*(float *)(i + 160)) + *(float *)(i + 72);
        *(float *)(i + 160) = 0.0;
      }
      result = *(_DWORD *)(i + 328);
    }
  }
  return result;
}

