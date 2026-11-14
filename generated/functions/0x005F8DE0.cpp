// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F8DE0 rf_scene_frame_channel_state_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 72-byte state:arg definition pointer stored0,lastSampleFrame float12=0. Cur quaternion28 and previous quaternion56 initialized(0,0,0,1);vector defaults at16(current position),44(previous position) are NO-OP. Clears flag bits31,30,29 inDWORD8,preserving uninitialized low29bits;attachment pointer4 untouched. Returns this. Does not sample definition or zero positions.
float *__thiscall rf_scene_frame_channel_state_construct(float *this, int a2)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_float4_construct_zero_zero_zero_one(this + 7);
  rf_vector3_default_construct_noop(this + 11);
  rf_float4_construct_zero_zero_zero_one(this + 14);
  *((_DWORD *)this + 2) &= ~0x40000000u;
  *((_DWORD *)this + 2) &= ~0x20000000u;
  *((_DWORD *)this + 2) &= ~0x80000000;
  *(_DWORD *)this = a2;
  *(this + 3) = 0.0;
  return this;
}

