// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587D90 rf_animation_clip_has_raw_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Returns boolean whether clip pointer DWORD+120 is nonzero. Does not inspect name, ownership byte+108, field+112/reference count+116 or raw-buffer validity; no load/acquire action.
bool __thiscall rf_animation_clip_has_raw_buffer(_DWORD *this)
{
  return *(this + 30) != 0;
}

