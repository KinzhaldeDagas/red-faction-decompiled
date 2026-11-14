// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00433E90 rf_entity_try_secondary_fire_body_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer), void. Pushes entity as ignored extra DWORD to435380: exact eight-byte helper always ORs EAX,-1 and returns, reading no input.
// Saved result is therefore signed-1 and JL bypasses the entire remaining body-action path for EVERY normal native call. No application state writes or action start currently occurs.
// The retained unreachable branch would test action active with any-nonzero AL, and if inactive request(entity,action,FLOAT1,LOWBYTE0,LOWBYTE1); do not infer this actually runs or
// repair the stub. No own pointer dereference beyond reading incoming argument value, validation, timer or meaningful result.
void __cdecl rf_entity_try_secondary_fire_body_action(int a1)
{
  signed int v1; // [esp+Ch] [ebp-4h]

  v1 = rf_constant_minus_one_435380();
  if ( v1 >= 0 && !rf_entity_body_action_is_active(a1, v1) )
    rf_entity_request_body_action(a1, v1, 1.0, 0, 1);
}

