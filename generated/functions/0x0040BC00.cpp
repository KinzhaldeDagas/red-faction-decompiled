// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BC00 rf_ai_configured_body_action_is_active
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Reads owner DWORD+4964 as BODY ACTION SLOT index; -1 returnsAL0. Otherwise calls body-action active(owner,index),
// returns its AL. That helper validates slot domain0..44 and resolves animation record; this wrapper does not treat+4964 as animation record directly. No state writes or independent
// owner/null/dead admission.
bool __cdecl rf_ai_configured_body_action_is_active(int *a1)
{
  return *(_DWORD *)(*a1 + 4964) != -1 && rf_entity_body_action_is_active(*a1, *(_DWORD *)(*a1 + 4964));
}

