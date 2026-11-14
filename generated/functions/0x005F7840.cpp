// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7840 rf_scene_key_tracks_get_vector2_outgoing_control
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall(destination vector,index);copies three floats from pointer at object+16,key stride40,index*40+28. Returns destination. No count/index/NULL validation;negative index reads before key array. Incoming/outgoing labels follow use as destination/source Bezier controls in0x5F6CE0/0x5F70E0.
float *__thiscall rf_scene_key_tracks_get_vector2_outgoing_control(_DWORD *this, float *a2, int a3)
{
  rf_vector3_copy_return_destination(a2, (float *)(*(this + 4) + 40 * a3 + 28));
  return a2;
}

