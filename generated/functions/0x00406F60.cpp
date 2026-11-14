// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406F60 rf_ai_mode5_release_target_after_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, mode5 secondary7 subhandler. AI flags+1328 mask0x20 clear AND owner animation slot34
// record+3188!=-1 ->request action34(1.0,0,1), ignore outcome, set mask0x20, arm block+600 for125ms. Independently mask0x20 set and action-active34 AL0 ->clear mask and secondary4.
// Independently of mask/action state, +600 elapsed EXACT1 resets deadline BEFORE resolving COMMON target+704; miss loses timer but does not raw-clear target. Found ->4343A0 thiscall
// ECX=owner, stack(current target handle,1); guarded target setter-1 ignoring result; captured target physics DWORD+424 OR0x80000001. Resolve that target handle as clutter; success
// invokes clutter seconds timer(clutter,FLOAT0.5,state10 if full handle+44 even else11). The handle low BIT, not authored ID+32, chooses state. No own clear of common
// reservation0x2000, authority gate, action-completion requirement on actual release path, or uniform return status.
char __cdecl rf_ai_mode5_release_target_after_action(int *a1)
{
  int v1; // eax
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+14h] [ebp-8h]

  if ( (a1[332] & 0x20) == 0 && *(_DWORD *)(*a1 + 3188) != -1 )
  {
    rf_entity_request_body_action(*a1, 0x22u, 1.0, 0, 1);
    a1[332] |= 0x20u;
    rf_replicator_arm_milliseconds(a1 + 150, 125);
  }
  if ( (a1[332] & 0x20) != 0 && !rf_entity_body_action_is_active(*a1, 0x22u) )
  {
    a1[332] &= ~0x20u;
    rf_ai_secondary_state_write((int)a1, 4);
  }
  LOBYTE(v1) = rf_replicator_has_elapsed(a1 + 150);
  if ( (unsigned __int8)v1 == 1 )
  {
    rf_replicator_reset(a1 + 150);
    v1 = rf_object_resolve_handle(a1[176]);
    v4 = v1;
    if ( v1 )
    {
      rf_entity_detach_first_matching_child(*a1, a1[176], 1);
      sub_40BA80(a1, -1);
      *(_DWORD *)(v4 + 424) |= 0x80000001;
      v1 = rf_clutter_find_by_uid(*(_DWORD *)(v4 + 44));
      if ( v1 )
      {
        v3 = 10;
        if ( (*(_DWORD *)(v4 + 44) & 1) != 0 )
          v3 = 11;
        LOBYTE(v1) = rf_clutter_arm_seconds_timer_with_state680(v1, 0.5, v3);
      }
    }
  }
  return v1;
}

