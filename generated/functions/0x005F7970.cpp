// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7970 rf_scene_key_tracks_get_quaternion_outgoing_ease
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall(index). Reads SIGNED BYTE stream pointer12+index*20+16,divides127.0 with float rounding before x87 return. Negative raw bytes remain negative,0x80 below-1. Used on FROM key by easing evaluator;no clamp/count/pointer guard.
double __thiscall rf_scene_key_tracks_get_quaternion_outgoing_ease(_DWORD *this, int a2)
{
  return (float)((double)*(char *)(*(this + 3) + 20 * a2 + 16) / 127.0);
}

