// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004031F0 rf_ai_consume_multiplayer_jump_request
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block. Only any-nonzero runtime/splitscreen AND AI flags+1328 mask0x01000000 proceed. Clears request mask BEFORE
// crouch/death/use-vehicle admission, so rejected request is consumed. Any nonzero AL from those predicates rejects. Otherwise calls entity try-jump-launch(owner) WITHOUT checking
// its result, then if AI flags mask0x02800000 clear calls402D70(block,LOWBYTE1), even if jump itself failed. Does not retry or restore request. No independently constructed success
// return; AL/EAX incidental.
char __cdecl rf_ai_consume_multiplayer_jump_request(int *a1)
{
  unsigned int v1; // eax

  LOBYTE(v1) = rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode;
  if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
  {
    v1 = (unsigned int)&unk_1000000 & a1[332];
    if ( v1 )
    {
      a1[332] &= ~0x1000000u;
      LOBYTE(v1) = rf_entity_is_crouched_state810(*a1);
      if ( !(_BYTE)v1 )
      {
        LOBYTE(v1) = rf_entity_is_dead(*a1);
        if ( !(_BYTE)v1 )
        {
          LOBYTE(v1) = rf_object_is_use_vehicle((_DWORD *)*a1);
          if ( !(_BYTE)v1 )
          {
            rf_entity_try_jump_launch(*a1);
            LOBYTE(v1) = (_BYTE)a1;
            if ( (a1[332] & 0x2800000) == 0 )
              LOBYTE(v1) = rf_ai_build_alternative_route_from_global_points(a1, 1);
          }
        }
      }
    }
  }
  return v1;
}

