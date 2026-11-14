// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7930 rf_scene_key_tracks_get_quaternion_incoming_ease
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall(index). Reads SIGNED BYTE from stream pointer12+index*20+15,divides by127.0 and rounds result through float before x87 return. Thus raw0x80 gives -128/127;not unsigned0..1,not clamped. Used on TO key by easing evaluator. No index/NULL guard.
double __thiscall rf_scene_key_tracks_get_quaternion_incoming_ease(_DWORD *this, int a2)
{
  return (float)((double)*(char *)(*(this + 3) + 20 * a2 + 15) / 127.0);
}

