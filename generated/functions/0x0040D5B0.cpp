// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D5B0 rf_object_request_physics_reactivation_flags
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] OR owner+0x1A8 bit0x80000000 and common+0x7C bits0x06000000. No null check, linear/angular velocity reset, explicit physics-state activation call or attachment restoration. Turn_Off_Physics reverse uses this flag-only request.
int __cdecl rf_object_request_physics_reactivation_flags(int a1)
{
  *(_DWORD *)(a1 + 424) |= 0x80000000;
  *(_DWORD *)(a1 + 124) |= 0x6000000u;
  return a1;
}

