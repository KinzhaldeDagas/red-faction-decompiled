// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503740 rf_event_make_invulnerable_construct
// UNREALRED VERIFIED [mission-protection-20261020] Type24 vtable slots+4/+8/+12 are forward0x5006D0, reverse0x5007E0, per-frame0x500890. Protection owns a replicator at+0x2BC in addition to base authored-delay ownership.
char *__thiscall rf_event_make_invulnerable_construct(char *this)
{
  rf_mission_event_construct_base(this);
  *(_DWORD *)this = &event_make_invulnerable::`vftable';
  rf_timestamp4_construct_invalid((int *)this + 175);
  return this;
}

