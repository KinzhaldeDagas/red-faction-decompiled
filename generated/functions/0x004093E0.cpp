// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004093E0 rf_ai_update_ready_to_idle_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Requires owner+2064 mask0x10 clear, AI mode!=1, ready predicate any-nonzero, target+704 failing COMMON handle
// resolution, and animation slot29 record owner+3108!=-1. Missing animation returns WITHOUT clearing ready: no mirror of409260 immediate fallback. Reject class flags+1828
// mask0x08000000 (fire_outside_range), humanoid any-nonzero, or dead EXACT AL1. If AI flags mask4 clear requests body action(owner,29,1.0,0,1), ignores outcome then sets mask4.
// Otherwise waits for action active AL0; then clears ready mask1 and mask4. Does not set owner latch0x10, clear target, arm timers or change modes. EAX/AL is incidental, not uniform
// completion boolean.
char __cdecl rf_ai_update_ready_to_idle_transition(int *a1)
{
  int v1; // eax

  LOBYTE(v1) = (_BYTE)a1;
  if ( (*(_DWORD *)(*a1 + 2064) & 0x10) == 0 )
  {
    LOBYTE(v1) = (_BYTE)a1;
    if ( a1[160] != 1 )
    {
      LOBYTE(v1) = rf_ai_is_ready_flag_set((int)a1);
      if ( (_BYTE)v1 )
      {
        v1 = rf_object_resolve_handle(a1[176]);
        if ( !v1 )
        {
          v1 = *a1;
          if ( *(_DWORD *)(*a1 + 3108) != -1 )
          {
            v1 = *(_DWORD *)(*a1 + 660);
            if ( (*(_DWORD *)(v1 + 1828) & 0x8000000) == 0 )
            {
              LOBYTE(v1) = rf_entity_has_humanoid_flag(*a1);
              if ( !(_BYTE)v1 )
              {
                LOBYTE(v1) = rf_entity_is_dead(*a1);
                if ( (unsigned __int8)v1 != 1 )
                {
                  if ( (a1[332] & 4) != 0 )
                  {
                    LOBYTE(v1) = rf_entity_body_action_is_active(*a1, 0x1Du);
                    if ( !(_BYTE)v1 )
                    {
                      rf_ai_clear_ready_flag((int)a1);
                      a1[332] &= ~4u;
                      LOBYTE(v1) = (_BYTE)a1;
                    }
                  }
                  else
                  {
                    rf_entity_request_body_action(*a1, 0x1Du, 1.0, 0, 1);
                    a1[332] |= 4u;
                    LOBYTE(v1) = (_BYTE)a1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return v1;
}

