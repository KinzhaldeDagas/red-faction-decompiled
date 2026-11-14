// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562DC0 rf_model_handle_reset_action_animations
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 delegates character_instance_reset_actions, distinct from cyclic-only5877B0. Tag3 same scene branch as562D40:sets4,clears8and2,zeros clocks12/16,leaves draining low bit untouched. Other tags unchanged. No event dispatch/unload here; raw return not reliable status.
int *__thiscall rf_model_handle_reset_action_animations(int *this)
{
  int *result; // eax

  result = this;
  if ( *this == 2 )
    return (int *)rf_character_instance_reset_actions(*(this + 1));
  if ( *this == 3 )
  {
    *(_DWORD *)*(this + 1) |= 4u;
    *(_DWORD *)*(this + 1) &= ~8u;
    *(_DWORD *)*(this + 1) &= ~2u;
    *(float *)(*(this + 1) + 16) = 0.0;
    result = (int *)*(this + 1);
    *((float *)result + 3) = 0.0;
  }
  return result;
}

