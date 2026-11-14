// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FAD80 rf_scene_transform_track_state_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 40-byte state:definition pointer0=input;flagsDWORD8 bits29/30/31 cleared,preserves low29 uninitialized bits;attachment pointer4 untouched. Position float3 at12 zeroed,quaternion24 set(0,0,0,1) via0x583C30. Returns this;no sampling or allocation.
void *__thiscall rf_scene_transform_track_state_construct(void *this, int a2)
{
  *((_DWORD *)this + 2) &= ~0x20000000u;
  *((_DWORD *)this + 2) &= ~0x40000000u;
  *((_DWORD *)this + 2) &= ~0x80000000;
  rf_vector3_zero_return_destination((float *)this + 3);
  rf_quaternion_set_identity_return_this((float *)this + 6);
  *(_DWORD *)this = a2;
  return this;
}

