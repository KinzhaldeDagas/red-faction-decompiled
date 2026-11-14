// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA120 rf_physics_set_gravity_acceleration
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] Store supplied float to rf_physics_gravity_acceleration, negate it, and pass(0,-gravity,0) plus vector storage0x87BF54 to0x40D250. No clamping or finite-value validation. Event Set_Gravity passes its stored float directly.
float *__cdecl rf_physics_set_gravity_acceleration(float a1)
{
  float v2; // [esp+4h] [ebp-8h]

  rf_physics_gravity_acceleration = a1;
  v2 = -a1;
  return rf_vector3_set_components_thiscall(unk_87BF54, 0.0, v2, 0.0);
}

