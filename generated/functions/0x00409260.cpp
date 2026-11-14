// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409260 rf_ai_update_idle_to_ready_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Owner DWORD+2064 mask0x10 or AI mode1 suppresses. Ready predicate AL==EXACT1 or unholster-pending predicate AL==EXACT1
// suppresses. Requires AI target+704 resolving to ANY common object. Owner animation slot28 record DWORD+3092==-1 immediately sets AI ready mask1 and returns: does NOT set owner
// latch0x10 or exclude humanoids in that branch. Slot exists: humanoid predicate any-nonzero suppresses. If AI mask2 clear, requests body action(owner,28,1.0,0,1), ignores outcome,
// then sets mask2. If mask2 set waits until body-action active predicate AL0; then sets ready mask1, clears mask2, and ORs owner+2064 mask0x10. Only this completion branch
// case-insensitively compares class RFString+0 with literal auto turret and writes owner selected weapon+676=-1 if equal. No own dead, distance or role gate. EAX/AL path-dependent.
// Persistent latch suppresses both ready/idle functions on later calls.
char __cdecl rf_ai_update_idle_to_ready_transition(int *a1)
{
  int v1; // eax

  LOBYTE(v1) = (_BYTE)a1;
  if ( (*(_DWORD *)(*a1 + 2064) & 0x10) == 0 )
  {
    LOBYTE(v1) = (_BYTE)a1;
    if ( a1[160] != 1 )
    {
      LOBYTE(v1) = rf_ai_is_ready_flag_set((int)a1);
      if ( (unsigned __int8)v1 != 1 )
      {
        LOBYTE(v1) = rf_ai_unholster_pending_flag_set((int)a1);
        if ( (unsigned __int8)v1 != 1 )
        {
          v1 = rf_object_resolve_handle(a1[176]);
          if ( v1 )
          {
            if ( *(_DWORD *)(*a1 + 3092) == -1 )
            {
              LOBYTE(v1) = rf_ai_set_ready_flag((int)a1);
            }
            else
            {
              LOBYTE(v1) = rf_entity_has_humanoid_flag(*a1);
              if ( !(_BYTE)v1 )
              {
                if ( (a1[332] & 2) != 0 )
                {
                  LOBYTE(v1) = rf_entity_body_action_is_active(*a1, 0x1Cu);
                  if ( !(_BYTE)v1 )
                  {
                    rf_ai_set_ready_flag((int)a1);
                    a1[332] &= ~2u;
                    *(_DWORD *)(*a1 + 2064) |= 0x10u;
                    LOBYTE(v1) = rf_string_equals_case_insensitive(*(_DWORD *)(*a1 + 660), "auto turret");
                    if ( (_BYTE)v1 )
                    {
                      *(_DWORD *)(*a1 + 676) = -1;
                      LOBYTE(v1) = (_BYTE)a1;
                    }
                  }
                }
                else
                {
                  rf_entity_request_body_action(*a1, 0x1Cu, 1.0, 0, 1);
                  v1 = a1[332] | 2;
                  a1[332] = v1;
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

