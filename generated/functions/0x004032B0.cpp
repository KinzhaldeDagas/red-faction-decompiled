// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004032B0 rf_ai_maybe_queue_jump_for_different_target_owner
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): Cdecl(entity,second record). Player-flag entity or nonentity predicate returns without queuing. Otherwise consumes rand() and executes SIGNED
// IDIV with divisor(8-DWORD6612A4) BEFORE runtime/splitscreen test. No divisor-zero or difficulty-range guard; remainder0 AND any nonzero runtime/splitscreen admits. Compares entity
// embedded AI target DWORD+1376 with second record DWORD+48; unequal ORs AI flags entity+2000 mask0x01000000, equal leaves unchanged. No second-record null guard on admitted path.
// EAX/AL contains incidental quotient/pointer/predicate values, not queue-success boolean.
char __cdecl rf_ai_maybe_queue_jump_for_different_target_owner(int a1, int a2)
{
  int v2; // eax
  int v3; // eax
  int v4; // et2

  LOBYTE(v2) = rf_object_has_player_flag(a1);
  if ( !(_BYTE)v2 )
  {
    LOBYTE(v2) = rf_object_is_entity(a1);
    if ( (_BYTE)v2 )
    {
      v3 = rand();
      v4 = v3 % (8 - dword_6612A4);
      v2 = v3 / (8 - dword_6612A4);
      if ( !v4 && (rf_multiplayer_runtime_mode || (LOBYTE(v2) = rf_splitscreen_runtime_active) != 0) )
      {
        LOBYTE(v2) = a1 - 96;
        if ( *(_DWORD *)(a1 + 1376) != *(_DWORD *)(a2 + 48) )
        {
          *(_DWORD *)(a1 + 2000) |= (unsigned int)&unk_1000000;
          LOBYTE(v2) = a1 - 96;
        }
      }
    }
  }
  return v2;
}

