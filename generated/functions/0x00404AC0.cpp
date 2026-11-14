// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404AC0 rf_ai_should_seek_replacement_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, explicit AL0/1 predicate. Requires nonplayer-sentient/runtime-enabled owner predicate nonzero OR mode15. Resolve
// COMMON target+704. Owner DWORD+504==1 special case returns1 ONLY if target unresolved AND signed pointer-array count at block+524>0. Other owners: handle-1 OR unresolved target
// returns1. Resolved target ordered health<=0 returns1; positive OR UNORDERED health continues. Equal target/owner DWORD+504 returns1; otherwise returns1 iff AI mode!=3. Thus only
// live-or-unordered different-class target in mode3 suppresses general replacement. No mutation, independent entity-target type requirement or own dead/authority test.
bool __cdecl rf_ai_should_seek_replacement_target(int *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !rf_entity_is_nonplayer_sentient_or_runtime_enabled(*a1) && a1[160] != 15 )
    return 0;
  v2 = rf_object_resolve_handle(a1[176]);
  if ( *(_DWORD *)(*a1 + 504) == 1 )
    return !v2 && rf_receiver_get_first_dword(a1 + 131) > 0;
  if ( a1[176] == -1 )
  {
    return 1;
  }
  else if ( v2 )
  {
    return *(float *)(v2 + 52) <= 0.0 || *(_DWORD *)(v2 + 504) == *(_DWORD *)(*a1 + 504) || a1[160] != 3;
  }
  else
  {
    return 1;
  }
}

