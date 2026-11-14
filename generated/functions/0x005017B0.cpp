// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005017B0 rf_event_display_fullscreen_image_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_display_fullscreen_image forward, vtable0x63E3E8 slot+4. Copy raw event dword+0x2B8 into global selected image0x663290. No asset load, validation, timer, draw or target traversal in this callback.
_DWORD *__thiscall rf_event_display_fullscreen_image_forward(_DWORD *this)
{
  dword_663290 = *(this + 174);
  return this;
}

