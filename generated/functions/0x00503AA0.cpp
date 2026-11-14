// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503AA0 rf_event_unhide_construct
// UNREALRED VERIFIED [mission-protection-20261020] Type50 UnHide owns pending-show/pending-hide and replicator fields distinct from base authored delay. vtable slots forward501100,reverse501120,update501140. World integration must preserve pending updates, geometry visibility gating and common hide/reactivate side effects.
char *__thiscall rf_event_unhide_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_unhide::`vftable';
  rf_timestamp4_construct_invalid((int *)this + 174);
  return this;
}

