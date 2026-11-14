// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEAB0 rf_ui_slider_set_page_step
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Stores raw DWORD argument at+660,returns this. No clamp,range adjustment or event;used for page movement of slider/derived scrollbar.
_DWORD *__thiscall rf_ui_slider_set_page_step(_DWORD *this, int a2)
{
  *(this + 165) = a2;
  return this;
}

