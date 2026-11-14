// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDAA0 rf_particle_emitter_initialize
// UNREALRED VERIFIED [combat-particle-emission-20261104]: After copying definition source position and direction,559200 normalizes runtime direction+0x14 before any immediate emission. Thus4CD520 copying its base when randomness>=1 is not evidence that nonunit authored template directions survive initialization.559200 has no zero guard; exact-zero authored direction is undefined, distinct from559300 graph fallback.
// UNREALRED VERIFIED [combat-native-followup-20261104]: Copies definition position/direction, normalizes runtime direction, resolves INITIAL room from definition position with optional supplied room/previous point and fallback to supplied room only here. Definition emitter flag0x10 gates initial scheduling (immediate bit2 emits, otherwise arms first delay). This happens BEFORE runtime enabled+320 is assigned from explicit a6 and BEFORE alternate duration sampling. Do not equate authored initially_on with runtime enabled or move alternate RNG ahead of initial spawn/deadline.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] Thiscall RET14h INITIALIZER, AL is a6/alternate-helper residue not success. Copies source/room fields before initial10 scheduling: immediate2 calls4CD520(spawn/draw/rearm) or samples delay, arms340; THEN sets enabled320=a6 and alternate20 elapsed/duration. Native draws/spawns are real ordered prefixes. Host room/source data unavailable BEFORE phase must defer without RNG; loss after phase began/completed cannot justify restarting the entire initializer. Preserve actual completed control/prefix and original input lease, or revoke exact old request without replay.
void __thiscall rf_particle_emitter_initialize(char *this, int a2, int a3, void *a4, float *a5, char a6)
{
  double v6; // st7
  float v8[3]; // [esp+Ch] [ebp-24h] BYREF
  float v9[3]; // [esp+18h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-Ch] BYREF

  *((_DWORD *)this + 1) = a2;
  *(_DWORD *)this = *(_DWORD *)a3;
  rf_vector_copy((float *)this + 2, copy_result, (const float *)(a3 + 4));
  rf_vector_copy((float *)this + 20, v9, (const float *)(a3 + 4));
  rf_vector_copy((float *)this + 5, v8, (const float *)(a3 + 16));
  rf_vector_normalize_reciprocal_sqrt((float *)this + 5);
  *((float *)this + 8) = *(float *)(a3 + 28);
  *((float *)this + 9) = *(float *)(a3 + 32);
  *((float *)this + 10) = *(float *)(a3 + 36);
  *((float *)this + 11) = *(float *)(a3 + 48);
  *((float *)this + 12) = *(float *)(a3 + 40);
  *((float *)this + 13) = *(float *)(a3 + 44);
  *((_WORD *)this + 28) = *(_WORD *)(a3 + 52);
  *((float *)this + 15) = *(float *)(a3 + 56);
  *((float *)this + 16) = *(float *)(a3 + 60);
  *((float *)this + 17) = *(float *)(a3 + 64);
  *((float *)this + 18) = *(float *)(a3 + 68);
  *((float *)this + 27) = *(float *)(a3 + 72);
  *((float *)this + 28) = *(float *)(a3 + 76);
  *((float *)this + 29) = *(float *)(a3 + 80);
  *((_DWORD *)this + 31) = *(_DWORD *)(a3 + 100);
  *((_DWORD *)this + 32) = *(_DWORD *)(a3 + 104);
  *((_DWORD *)this + 33) = *(_DWORD *)(a3 + 108);
  *((_DWORD *)this + 34) = *(_DWORD *)(a3 + 112);
  *((_DWORD *)this + 35) = *(_DWORD *)(a3 + 116);
  *((_DWORD *)this + 36) = *(_DWORD *)(a3 + 120);
  *((float *)this + 37) = *(float *)(a3 + 124);
  *((float *)this + 74) = *(float *)(a3 + 84);
  *((float *)this + 75) = *(float *)(a3 + 88);
  *((float *)this + 76) = *(float *)(a3 + 92);
  *((float *)this + 77) = *(float *)(a3 + 96);
  *((float *)this + 81) = *(float *)(a3 + 128);
  *((_DWORD *)this + 44) = this + 176;
  *((_DWORD *)this + 45) = this + 176;
  if ( a4 )
  {
    if ( a5 )
    {
      if ( rf_vector_distance_squared(a5, (const float *)this + 2) <= 0.0 )
      {
        *((_DWORD *)this + 19) = a4;
      }
      else
      {
        *((_DWORD *)this + 19) = rf_world_resolve_cached_room(
                                   (void *)rf_world_solid,
                                   a4,
                                   a5,
                                   (const float *)this + 2,
                                   0);
        if ( !*((_DWORD *)this + 19) )
          *((_DWORD *)this + 19) = a4;
      }
    }
    else
    {
      *((_DWORD *)this + 19) = a4;
    }
  }
  else
  {
    *((_DWORD *)this + 19) = rf_world_resolve_cached_room(
                               (void *)rf_world_solid,
                               nullptr,
                               (const float *)this + 2,
                               (const float *)this + 2,
                               0);
  }
  if ( (*((_WORD *)this + 28) & 0x10) != 0 )
  {
    if ( (*((_WORD *)this + 28) & 2) != 0 )
    {
      rf_particle_emitter_spawn_particle((float *)this);
    }
    else
    {
      v6 = rf_random_float_range(*((float *)this + 12), *((float *)this + 13)) * 1000.0;
      rf_replicator_arm_milliseconds((int *)this + 85, (int)v6);
    }
  }
  *((float *)this + 74) = *(float *)(a3 + 84);
  *((float *)this + 75) = *(float *)(a3 + 88);
  *((float *)this + 76) = *(float *)(a3 + 92);
  *((float *)this + 77) = *(float *)(a3 + 96);
  *(this + 320) = a6;
  if ( (*((_WORD *)this + 28) & 0x20) != 0 )
  {
    *((float *)this + 79) = 0.0;
    rf_particle_emitter_choose_alternate_duration((int)this);
  }
}

