// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050E190 rf_projectile_postphysics_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): For nongrenade and no flame flag, only ORDERED velocity lengthSquared>DOUBLE0.001 builds orientation at+252 from velocity+324 through55BF00, then copies to matrix+72. Valid voice+672!=-1 updates positioned voice using projectile position field+228, velocity+324, gain1. If weapon thrust-lifetime predicate5111E0 returns EXACTLY1, decrements F32 thrust remaining+756; ORDERED value<=0 ORs physics flags+424 bit1 and disables every attached emitter50E510 each expired frame. Valid light+676!=-1: flickers flag+612 bit8 advances F32 phase+684 by frameDelta*DOUBLE15; ORDERED phase>=15 resets to0 (not modulo; negative/NaN remains unchecked). Thruster bit10h selects15-float6615FC curve,
// otherwise661638. Each radius separately truncates phase usingFTOL2SSE, multiplies info inner+532/outer+536 and passes both to527A40; renderer consumes outer radius. Negative/NaN phase has no table bound guard. Light position+60 submitted exactly once per valid handle, with or without flicker. Only info damage types+1324 EXACT1 or2 process trail state+760: if bits1 or2 set, emit511320 FIRST; then if bit4 set, copy bit2 truth into bit1, finally clear bit4. Other damage types retain all trail flags. No projectile/light destruction or reliable EAX status.
int __cdecl rf_projectile_postphysics_update(int a1)
{
  int result; // eax
  unsigned int v2; // edx
  int v3; // [esp+Ch] [ebp-10h]
  float v4; // [esp+10h] [ebp-Ch]
  int v5; // [esp+14h] [ebp-8h]
  float v6; // [esp+18h] [ebp-4h]

  if ( *(_DWORD *)(a1 + 664) != rf_weapon_index_grenade
    && !rf_weapon_has_flame_flag(*(_DWORD *)(a1 + 664))
    && rf_vector_length_squared((float *)(a1 + 324)) > 0.001 )
  {
    rf_orientation_matrix_from_normalized_direction((float *)(a1 + 252), (float *)(a1 + 324));
    rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
  }
  if ( *(_DWORD *)(a1 + 672) != -1 )
    rf_positioned_voice_update(*(_DWORD *)(a1 + 672), (float *)(a1 + 228), a1 + 324, 1.0);
  if ( rf_weapon_has_positive_thrust_lifetime(*(_DWORD *)(a1 + 664)) )
  {
    *(float *)(a1 + 756) = *(float *)(a1 + 756) - rf_frame_delta_seconds;
    if ( *(float *)(a1 + 756) <= 0.0 )
    {
      *(_DWORD *)(a1 + 424) |= 1u;
      rf_projectile_disable_attached_emitters(a1);
    }
  }
  if ( *(_DWORD *)(a1 + 676) != -1 )
  {
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 8) != 0 )
    {
      *(float *)(a1 + 684) = rf_frame_delta_seconds * 15.0 + *(float *)(a1 + 684);
      if ( *(float *)(a1 + 684) >= 15.0 )
        *(float *)(a1 + 684) = 0.0;
      if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x10) != 0 )
      {
        v6 = *(float *)(*(_DWORD *)(a1 + 660) + 536)
           * rf_projectile_glow_flicker_thruster_curve_15[*(float *)(a1 + 684)];
        *(float *)&v5 = *(float *)(*(_DWORD *)(a1 + 660) + 532)
                      * rf_projectile_glow_flicker_thruster_curve_15[*(float *)(a1 + 684)];
        rf_renderer_light_set_range(*(_DWORD *)(a1 + 676), v5, v6);
      }
      else
      {
        v4 = *(float *)(*(_DWORD *)(a1 + 660) + 536) * rf_projectile_glow_flicker_curve_15[*(float *)(a1 + 684)];
        *(float *)&v3 = *(float *)(*(_DWORD *)(a1 + 660) + 532)
                      * rf_projectile_glow_flicker_curve_15[*(float *)(a1 + 684)];
        rf_renderer_light_set_range(*(_DWORD *)(a1 + 676), v3, v4);
      }
    }
    rf_renderer_light_set_position(*(_DWORD *)(a1 + 676), (float *)(a1 + 60));
  }
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) == 1
    || (result = *(_DWORD *)(a1 + 660), *(_DWORD *)(result + 1324) == 2) )
  {
    if ( (*(_DWORD *)(a1 + 760) & 2) != 0 || (*(_DWORD *)(a1 + 760) & 1) != 0 )
      rf_projectile_emit_distributed_trail_particles(a1);
    if ( (*(_DWORD *)(a1 + 760) & 4) != 0 )
    {
      if ( (*(_DWORD *)(a1 + 760) & 2) != 0 )
        v2 = *(_DWORD *)(a1 + 760) | 1;
      else
        v2 = *(_DWORD *)(a1 + 760) & 0xFFFFFFFE;
      *(_DWORD *)(a1 + 760) = v2;
    }
    *(_DWORD *)(a1 + 760) &= ~4u;
    return a1;
  }
  return result;
}

