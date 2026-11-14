// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005017D0 rf_event_display_fullscreen_image_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_display_fullscreen_image reverse, vtable0x63E3E8 slot+8. Write global0x663290=-1 unconditionally. No release of image resource or event-specific ownership check in this body.
void rf_event_display_fullscreen_image_reverse()
{
  dword_663290 = -1;
}

