// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BD80 sub_40BD80
// UNREALRED VERIFIED [remote-combat-tick-20260930] Entity update 0x4275B0 passes Entity+0x2A0 here at 0x4278B6. The first counter at argument+0x260 (Entity+0x500) runs when positive and argument+0x25C (Entity+0x4FC) expires: call 0x431FD0 with continuation=1 and alt=0, rearm from weapon-record +0x448 in milliseconds, then decrement. Armed primary rounds therefore progress from entity updates, not new trigger messages. Unreal remote authority must schedule its continuation update from a tick that executes on that role.
char __cdecl sub_40BD80(int *a1)
{
  char result; // al

  if ( a1[152] > 0 && rf_replicator_has_elapsed(a1 + 151) )
  {
    sub_431FD0(*a1, 1, 0, nullptr, 0, 0);
    rf_replicator_arm_milliseconds(a1 + 151, (int)(*((float *)&unk_912448 + 340 * a1[1]) * 1000.0));
    --a1[152];
  }
  result = (char)a1;
  if ( a1[154] > 0 )
  {
    result = rf_replicator_has_elapsed(a1 + 153);
    if ( result == 1 )
    {
      rf_entity_fire_secondary_or_begin_charge((_DWORD *)*a1, 1);
      rf_replicator_arm_milliseconds(a1 + 153, (int)(*((float *)&unk_912448 + 340 * a1[2]) * 1000.0));
      --a1[154];
      return (char)a1;
    }
  }
  return result;
}

