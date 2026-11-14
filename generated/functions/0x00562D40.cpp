// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562D40 rf_model_handle_reset_cyclic_animations
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 calls5877B0:clear freeze index/frozen byte and zero mix ONLY cyclic records. Tag3 sets instance bit4,clears8and2,resets clocks12/16; preserves scene draining low bit and other flags. Other tags no change. Distinct character action-reset wrapper562DC0 despite identical scene branch; raw return incidental.
int *__thiscall rf_model_handle_reset_cyclic_animations(int *this)
{
  int *result; // eax

  result = this;
  if ( *this == 2 )
    return (int *)rf_character_instance_reset_cyclic_action_mixes(*(this + 1));
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

