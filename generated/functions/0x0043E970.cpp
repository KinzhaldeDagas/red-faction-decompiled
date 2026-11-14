// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E970 sub_43E970
// UNREALRED VERIFIED [indirect-source-20261029] Successful fire-effect allocation stores victim entity handle at record+0x10 and supplied ignition source handle at+0x34, then links the record into the active fire list. Allocation has separate body/action, subtype and masako exclusions; complete burn update/expiry/replication parity is not established by this allocation trace.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Strict allocation requires free slot, valid entity,40D280 model-kind/body-action gate,43BFA0 false, class name not masako, all4ordered bone bindings. Creates flame emitters0,1,2 then smoke3 with explicit enabled1; stores owner and independent ignition source. Links allocated record at active tail. Partial native emitter failure can leave active record skipped by43F270; headless logical control storage must be documented separately from native global-emitter pressure.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM/callee closure] Attempts all FOUR4CEC90 emitter creates without NULL tests, then voice attempt and owner/source/gain/fade stores, THEN moves burn record free->active and returns nonNULL even if one or more emitter pointersNULL. Real native poolNULL is a completed creation outcome, not a source-provider Unavailable. A necessary host pending-input continuation must be separate from native active/completed allocation: preserve original owner/source/definitions/bones/time and already completed calls; do not retry real native NULL or publish pending as successful native ignition.
// UNREALRED VERIFIED [combat-emitter-burn-parent-20261112]: All four 4CEC90 factory calls in 43E970 (43EAAB,43EAD2,43EAFA,43EB3B) pass the resolved entity DWORD +0x2C (+44) as the raw full32 parent handle: each MOV [entity+2Ch] is pushed as argument1. The separately pushed room=NULL, previous-emitter=NULL and enabled=1 are arguments3/4/5, not parent=0. This does not identify a host logical body ID with an RF slot/generation handle.
int __cdecl sub_43E970(int a1, int a2)
{
  int v3; // [esp+Ch] [ebp-94h]
  int v4; // [esp+10h] [ebp-90h]
  int v5; // [esp+14h] [ebp-8Ch]
  float self[34]; // [esp+18h] [ebp-88h] BYREF

  rf_particle_emitter_definition_construct_noop(self);
  v5 = unk_6E650C;
  if ( !unk_6E650C )
    return 0;
  v4 = rf_entity_resolve_handle(a1);
  if ( !v4 )
    return 0;
  if ( !rf_entity_admits_speech_body_actions(v4) )
    return 0;
  if ( rf_entity_class_flag2000000_positive_scalar56(v4) )
    return 0;
  if ( rf_string_equals_case_insensitive(*(_DWORD *)(v4 + 660), "masako") )
    return 0;
  if ( !sub_43ECF0((_DWORD *)v5, v4) )
  {
    *(_DWORD *)(v5 + 20) = -1;
    *(_DWORD *)(v5 + 24) = -1;
    *(_DWORD *)(v5 + 28) = -1;
    *(_DWORD *)(v5 + 32) = -1;
    return 0;
  }
  rf_particle_emitter_definition_assign132(self, dword_867800[dword_661568]);
  *(_DWORD *)v5 = rf_particle_emitter_create(*(_DWORD *)(v4 + 44), self, 0, 0, 1);
  *(_DWORD *)(v5 + 4) = rf_particle_emitter_create(*(_DWORD *)(v4 + 44), self, 0, 0, 1);
  *(_DWORD *)(v5 + 8) = rf_particle_emitter_create(*(_DWORD *)(v4 + 44), self, 0, 0, 1);
  rf_particle_emitter_definition_assign132(self, dword_867800[dword_66156C]);
  *(_DWORD *)(v5 + 12) = rf_particle_emitter_create(*(_DWORD *)(v4 + 44), self, 0, 0, 1);
  *(_DWORD *)(v5 + 16) = a1;
  v3 = rf_foley_choose_random_sound(dword_661564);
  *(_DWORD *)(v5 + 36) = rf_gamesound_play_positional_event(v3, (float *)(v4 + 60), 1.0, (int)&unk_17F10B0, 0);
  *(float *)(v5 + 40) = 1.0;
  *(_BYTE *)(v5 + 44) = 0;
  *(float *)(v5 + 48) = 0.0;
  *(_DWORD *)(v5 + 52) = a2;
  if ( unk_6E650C != v5 )
    goto LABEL_17;
  if ( *(_DWORD *)(v5 + 56) != v5 )
  {
    unk_6E650C = *(_DWORD *)(v5 + 56);
LABEL_17:
    *(_DWORD *)(*(_DWORD *)(v5 + 60) + 56) = *(_DWORD *)(v5 + 56);
    *(_DWORD *)(*(_DWORD *)(v5 + 56) + 60) = *(_DWORD *)(v5 + 60);
    *(_DWORD *)(v5 + 56) = 0;
    *(_DWORD *)(v5 + 60) = 0;
    goto LABEL_18;
  }
  *(_DWORD *)(v5 + 56) = 0;
  *(_DWORD *)(v5 + 60) = 0;
  unk_6E650C = 0;
LABEL_18:
  if ( unk_6E6508 )
  {
    *(_DWORD *)(v5 + 60) = *(_DWORD *)(unk_6E6508 + 60);
    *(_DWORD *)(v5 + 56) = unk_6E6508;
    *(_DWORD *)(*(_DWORD *)(unk_6E6508 + 60) + 56) = v5;
    *(_DWORD *)(unk_6E6508 + 60) = v5;
  }
  else
  {
    *(_DWORD *)(v5 + 56) = v5;
    *(_DWORD *)(v5 + 60) = v5;
    unk_6E6508 = v5;
  }
  return v5;
}

