// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562E40 rf_model_handle_zero_action_weight
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 zeros specified character action weight through helper;tag3 ignores index and invokes562DC0 whole scene reset/stop; other tags no change. No common index validation or preserved action subset for scene. Returns delegate/incidental receiver bits.
int *__thiscall rf_model_handle_zero_action_weight(float **this, int a2)
{
  int *result; // eax

  if ( *this == (float *)2 )
    return (int *)rf_character_instance_zero_action_weight(*(this + 1), a2);
  result = (int *)this;
  if ( *this == (float *)3 )
    return rf_model_handle_reset_action_animations((int *)this);
  return result;
}

