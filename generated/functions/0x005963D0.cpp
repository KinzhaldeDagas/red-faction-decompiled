// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005963D0 rf_scene_node_clear_names_and_link
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall partial initializer: zeroes BYTE+0, BYTE+65, and DWORD+132, then returns this. Does not clear the full object or either entire string buffer. Called by several distinct scene definition constructors; no allocation or destruction.
_BYTE *__thiscall rf_scene_node_clear_names_and_link(_BYTE *this)
{
  *this = 0;
  *(this + 65) = 0;
  *((_DWORD *)this + 33) = 0;
  return this;
}

