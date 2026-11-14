// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F060 rf_physics_state_deactivate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Cdecl physics-state P (object+136),one stackarg caller pops4. Clears ONLY flagsP288 bit0x80000000,then ORs0x18000000. Zeroes linear velocityP188,angular-stateP212,andangular-rateP200 vectors,in that order. Leaves forceP224/torqueP236,positions/matrices,bounds,time296,other flags and contact fields intact. Returns final zero-vector destination P200 inEAX,not boolean. No pointer/class/current-object admission checks;existing generic deactivate comment retained and refined to exact fields.
float *__cdecl rf_physics_state_deactivate(int a1)
{
  *(_DWORD *)(a1 + 288) &= ~0x80000000;
  *(_DWORD *)(a1 + 288) |= 0x18000000u;
  rf_vector3_zero_return_destination((float *)(a1 + 188));
  rf_vector3_zero_return_destination((float *)(a1 + 212));
  return rf_vector3_zero_return_destination((float *)(a1 + 200));
}

