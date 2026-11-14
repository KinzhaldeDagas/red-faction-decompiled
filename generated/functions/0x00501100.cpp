// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501100 rf_event_unhide_queue_show
// UNREALRED VERIFIED [mission-protection-20261020] UnHide forward input merely sets pending-show byte+0x2BC=1. It does not immediately reactivate common objects. Ordinary base forwarding occurs independently after this local handler.
_BYTE *__thiscall rf_event_unhide_queue_show(_BYTE *this)
{
  *(this + 700) = 1;
  return this;
}

