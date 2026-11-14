// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501120 rf_event_unhide_queue_hide
// UNREALRED VERIFIED [mission-protection-20261020] UnHide reverse input merely sets pending-hide byte+0x2BD=1. It does not clear pending-show or immediately hide targets. Its opposite operation shares the same500ms poll deadline.
_BYTE *__thiscall rf_event_unhide_queue_hide(_BYTE *this)
{
  *(this + 701) = 1;
  return this;
}

