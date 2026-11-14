// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587560 rf_character_instance_set_cyclic_action_mix
// UNREALRED VERIFIED [mission-play-animation-20261013] Starts/updates a cyclic animation by shared record identity through find-or-add; clears global frozen byte and sets mix to caller value. Does not reset all other cyclic records or rewrite entity normal-state scheduler indices.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Finds/adds action record from supplied identity via existing action helper. If returned slot>=0, clears instance frozen byte7500 and stores caller float mix at action array4828+12*slot, returns receiver bits. Failure returns negative slot unchanged. Does not reset other cyclic records, action time, or scheduler indices; no clamp of mix.
int __thiscall rf_character_instance_set_cyclic_action_mix(int this, int a2, float a3)
{
  int result; // eax
  int v5; // [esp+4h] [ebp-4h]

  result = rf_character_instance_find_or_add_action_record((float *)this, a2);
  v5 = result;
  if ( result > -1 )
  {
    *(_BYTE *)(this + 7500) = 0;
    *(float *)(this + 12 * v5 + 4828) = a3;
    return this;
  }
  return result;
}

