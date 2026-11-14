// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD520 rf_particle_emitter_spawn_particle
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Dedicated emitter source direction was normalized by4CDAA0 initialization;4CD460 additionally resolves/rotates parent-relative vectors. If randomness>=1 copy resolved base directly; if<1 clamp minimumDot[-1,1] then cone-sample. Origin adds full signed spawnRadius(+0x2C)*sampledDirection before speed scaling; no random radius/sphere sampling. Flag8 dirdepend multiplies random speed by dot(sampled,base), once, then scales sampled vector (4CD610..647); decompiler dot-square is misleading. Native order speed, radius(+0x44..48), life(+0x3C..40), allocation, rearm delay.
int __thiscall rf_particle_emitter_spawn_particle(float *this)
{
  float v1; // ecx
  float v2; // ecx
  float *v3; // eax
  double v4; // st7
  float v5; // ecx
  double v6; // st7
  float v7; // ecx
  double v8; // st7
  float v9; // ecx
  double v10; // st7
  float v11; // ecx
  double v12; // st7
  float v14[2]; // [esp-8h] [ebp-60h] BYREF
  float v15; // [esp+0h] [ebp-58h]
  float scalar; // [esp+4h] [ebp-54h]
  float v17; // [esp+8h] [ebp-50h]
  double v18; // [esp+Ch] [ebp-4Ch]
  float v19; // [esp+14h] [ebp-44h]
  float scaled_result[4]; // [esp+18h] [ebp-40h] BYREF
  float v21[3]; // [esp+28h] [ebp-30h] BYREF
  float copy_result[4]; // [esp+34h] [ebp-24h] BYREF
  int v23; // [esp+44h] [ebp-14h]
  float source[3]; // [esp+48h] [ebp-10h] BYREF
  int v25; // [esp+54h] [ebp-4h]

  v19 = *(float *)&this;
  rf_vector3_copy_return_destination(source, this + 5);
  rf_vector_copy((float *)(LODWORD(v19) + 80), copy_result, (const float *)(LODWORD(v19) + 8));
  v25 = 0;
  v25 = sub_4CD460(SLODWORD(v19), (float *)(LODWORD(v19) + 80), source);
  if ( *(float *)(LODWORD(v19) + 32) < 1.0 )
  {
    rf_float_clamp_in_place((float *)(LODWORD(v19) + 32), -1.0, 1.0);
    scalar = v2;
    scalar = *(float *)(LODWORD(v19) + 32);
    rf_vector3_copy_return_destination(v14, source);
    rf_random_unit_vector_in_cone((float *)(LODWORD(v19) + 92), v14[0], v14[1], v15, scalar);
  }
  else
  {
    rf_vector_copy((float *)(LODWORD(v19) + 92), v21, source);
  }
  scalar = v1;
  v3 = rf_vector_multiply_scalar((const float *)(LODWORD(v19) + 92), scaled_result, *(float *)(LODWORD(v19) + 44));
  rf_vector_accumulate((float *)(LODWORD(v19) + 80), v3);
  if ( (*(_WORD *)(LODWORD(v19) + 56) & 8) != 0 )
  {
    v4 = rf_vector_dot((float *)(LODWORD(v19) + 92), source);
    scalar = v5;
    scalar = *(float *)(LODWORD(v19) + 40);
    v15 = v5;
    v15 = *(float *)(LODWORD(v19) + 36);
    v18 = v4;
    v6 = rf_random_float_range(v15, scalar);
    v17 = v6 * v18;
    rf_vector3_scale_in_place_return_self((float *)(LODWORD(v19) + 92), v17);
  }
  else
  {
    scalar = v19;
    scalar = *(float *)(LODWORD(v19) + 40);
    v15 = v19;
    scalar = rf_random_float_range(*(float *)(LODWORD(v19) + 36), scalar);
    rf_vector3_scale_in_place_return_self((float *)(LODWORD(v19) + 92), scalar);
  }
  scalar = v7;
  scalar = *(float *)(LODWORD(v19) + 72);
  v15 = v19;
  v8 = rf_random_float_range(*(float *)(LODWORD(v19) + 68), scalar);
  *(float *)(LODWORD(v19) + 104) = v8;
  scalar = v9;
  scalar = *(float *)(LODWORD(v19) + 64);
  v15 = v19;
  v10 = rf_random_float_range(*(float *)(LODWORD(v19) + 60), scalar);
  *(float *)(LODWORD(v19) + 120) = v10;
  v23 = *(_DWORD *)(LODWORD(v19) + 4);
  if ( v25 && (*(_WORD *)(LODWORD(v19) + 56) & 0x80) != 0 )
  {
    v23 = *(_DWORD *)(v25 + 44);
    rf_vector_accumulate((float *)(LODWORD(v19) + 92), (float *)(v25 + 324));
  }
  if ( v25 )
  {
    if ( *(float *)(v25 + 52) > 0.0 )
    {
      LODWORD(copy_result[3]) = v25;
      if ( rf_weapon_has_flame_flag(*(_DWORD *)(v25 + 676)) )
        v23 = *(_DWORD *)(v25 + 44);
    }
  }
  rf_particle_allocate_and_initialize(
    1,
    (float *)(LODWORD(v19) + 80),
    *(_DWORD *)(LODWORD(v19) + 76),
    LODWORD(v19) + 8,
    v23,
    nullptr,
    SLODWORD(v19));
  scalar = v11;
  scalar = *(float *)(LODWORD(v19) + 52);
  v15 = v11;
  v12 = rf_random_float_range(*(float *)(LODWORD(v19) + 48), scalar) * 1000.0;
  return rf_replicator_arm_milliseconds((int *)(LODWORD(v19) + 340), (int)v12);
}

