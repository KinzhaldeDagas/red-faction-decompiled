// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B900 rf_ai_start_pending_unholster_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Resolves owner handle+44 as ENTITY; miss exits. In mode13, resolves original owner attachment handle+512 as COMMON
// object: if found with ordered health FLOAT+52>0 returns BEFORE pending-flag test; missing/nonpositive/NaN instead writes resolved owner DWORD+1980=0 and continues, even when later
// pending tests fail. Requires AI pending mask0x100 nonzero, active-deadline predicate40B850 !=EXACT AL1, dead predicate !=EXACT1 and resolved animation slot40 DWORD+3284!=-1. Resets
// model actions, requests body action(owner,40,1.0,0,1), ignores outcome, queries animation duration(model,slot record), rounds to float32 then LOW32 trunc(duration*DOUBLE1000) arms
// block+628. Independently LOW32 trunc(class FLOAT+3960*DOUBLE1000) arms block+632; no extra float store in this second conversion. No own positive-duration/range/finite/model-null
// guard, pending flag clear or playback rollback. Flags cleared later by409530.
void __cdecl rf_ai_start_pending_unholster_action(int *a1)
{
  float v1; // [esp+Ch] [ebp-Ch]
  int v2; // [esp+10h] [ebp-8h]
  int *v3; // [esp+14h] [ebp-4h]

  v3 = (int *)rf_entity_resolve_handle(*(_DWORD *)(*a1 + 44));
  if ( v3 )
  {
    if ( a1[160] == 13 )
    {
      v2 = rf_object_resolve_handle(*(_DWORD *)(*a1 + 512));
      if ( v2 && *(float *)(v2 + 52) > 0.0 )
        return;
      v3[495] = 0;
    }
    if ( rf_ai_unholster_pending_flag_set((int)a1)
      && !rf_ai_unholster_animation_deadline_active((int)a1)
      && !rf_entity_is_dead((int)v3)
      && v3[821] != -1 )
    {
      rf_model_handle_reset_actions_adapter(v3[32]);
      rf_entity_request_body_action((int)v3, 0x28u, 1.0, 0, 1);
      v1 = rf_model_animation_duration_seconds((unsigned int *)v3[32], v3[821]);
      rf_replicator_arm_milliseconds(a1 + 157, (int)(v1 * 1000.0));
      rf_replicator_arm_milliseconds(a1 + 158, (int)(*(float *)(v3[165] + 3960) * 1000.0));
    }
  }
}

