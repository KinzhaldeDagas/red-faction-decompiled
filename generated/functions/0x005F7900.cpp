// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7900 rf_scene_key_tracks_get_packed_quaternion
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall(destination fourWORDs,index). Copies8 bytes from stream pointer12+index*20+4 via0x584750;returns destination. No count/index/pointer check or unpack/normalization.
_WORD *__thiscall rf_scene_key_tracks_get_packed_quaternion(_DWORD *this, _WORD *a2, int a3)
{
  rf_short_quaternion_assign_words_return_this(a2, (_WORD *)(*(this + 3) + 20 * a3 + 4));
  return a2;
}

