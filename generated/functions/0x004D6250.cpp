// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D6250 rf_entity_apply_pitch_heading_rotation_input
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. Let dt=432,k=class660 float100. Float pitchDelta=1800*k*dt+1832;headingDelta=1804*k*dt+1828. Writes angular336=(pitchDelta/dt,headingDelta/dt,0) WITHOUT dt guard;clears1828/1832 and input1800 vector. Sets Euler2148X/Z0,adds headingDelta to2152;adds pitchDelta to offset2172 and zeroes2176/2180. Offset2172 clamps to+-1.5707963705062866 by ORDERED comparisons. Heading2152 resets0 only outside ORDERED+-6283.185546875,then LOOPS subtract/add6.2831854820251465 until within inclusive+-one revolution;NaN bypasses reset and loops. Zeroes2160/2184 vectors;sets current252 from Euler(pitch2148,bank2156,heading2152),copies to predicted288 and common72;visual2016 from2148+2172 with pitch-heading
// horizontal basis;zeroes torque372 and rebuilds rotated tensor P136. No reciprocal/time/class/finite validation; return helper EAX.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: This rotation-input writer consumes1800/1804,class+100,residual432 and1832/1828; clears input/direct deltas, writes body heading2152 and separate view pitch2172, and builds current252 and view7E0 separately. The caller4D7E90 selects this branch; generic NPC410920 writes angular336 and only jeep/APC also input1800, so routing all NPC through6250 without dispatcher/producer proof is unsupported.
int __cdecl rf_entity_apply_pitch_heading_rotation_input(int a1)
{
  const float *v1; // eax
  _BYTE v3[36]; // [esp+Ch] [ebp-38h] BYREF
  float v4; // [esp+30h] [ebp-14h]
  float sum_result[3]; // [esp+34h] [ebp-10h] BYREF
  float v6; // [esp+40h] [ebp-4h]

  v4 = *(float *)(a1 + 1800) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432) + *(float *)(a1 + 1832);
  v6 = *(float *)(a1 + 1804) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432) + *(float *)(a1 + 1828);
  *(float *)(a1 + 336) = v4 / *(float *)(a1 + 432);
  *(float *)(a1 + 340) = v6 / *(float *)(a1 + 432);
  *(float *)(a1 + 344) = 0.0;
  *(float *)(a1 + 1828) = 0.0;
  *(float *)(a1 + 1832) = 0.0;
  rf_vector3_zero_return_destination((float *)(a1 + 1800));
  *(float *)(a1 + 2148) = 0.0;
  *(float *)(a1 + 2152) = *(float *)(a1 + 2152) + v6;
  *(float *)(a1 + 2156) = 0.0;
  *(float *)(a1 + 2172) = *(float *)(a1 + 2172) + v4;
  *(float *)(a1 + 2176) = 0.0;
  *(float *)(a1 + 2180) = 0.0;
  if ( *(float *)(a1 + 2172) > 1.570796370506287 )
    *(float *)(a1 + 2172) = 1.5707964;
  if ( *(float *)(a1 + 2172) < -1.570796370506287 )
    *(float *)(a1 + 2172) = -1.5707964;
  if ( *(float *)(a1 + 2152) <= 6283.185546875 )
  {
    if ( *(float *)(a1 + 2152) < -6283.185546875 )
      *(float *)(a1 + 2152) = 0.0;
  }
  else
  {
    *(float *)(a1 + 2152) = 0.0;
  }
  while ( *(float *)(a1 + 2152) > 6.283185482025146 )
    *(float *)(a1 + 2152) = *(float *)(a1 + 2152) - 6.283185482025146;
  while ( *(float *)(a1 + 2152) < -6.283185482025146 )
    *(float *)(a1 + 2152) = *(float *)(a1 + 2152) + 6.283185482025146;
  rf_vector3_zero_return_destination((float *)(a1 + 2160));
  rf_vector3_zero_return_destination((float *)(a1 + 2184));
  rf_matrix3_set_euler_angles((float *)(a1 + 252), *(float *)(a1 + 2148), *(float *)(a1 + 2156), *(float *)(a1 + 2152));
  rf_matrix3_copy((float *)(a1 + 288), (const float *)(a1 + 252));
  rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
  rf_vector_add((const float *)(a1 + 2148), sum_result, (const float *)(a1 + 2172));
  v1 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v3, sum_result);
  rf_matrix3_copy((float *)(a1 + 2016), v1);
  rf_vector3_zero_return_destination((float *)(a1 + 372));
  return rf_physics_state_rebuild_rotated_tensor(a1 + 136);
}

