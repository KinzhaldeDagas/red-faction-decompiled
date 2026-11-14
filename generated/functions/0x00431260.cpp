// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431260 rf_entity_release_runtime_resources_and_unlink
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), one-shot ordered teardown, returns postdecrement global entity-count681E10 in fullEAX with native32-bit wrap.
// First403A80(entity AI+672) resets route+744 and releases AI array+524. SIGNED live-count loop over entity relation array2252 operator-deletes EVERY element pointer (includingNULL),
// then releases header/backing; no individual pointer clearing before header reset. If entity pointer EXACT global681E38, clear that global and6663C4. Ambient source2052!=-1: set
// gainFLOAT0 and invalidate-1; does NOT stop/release this source through gamesound-stop. Voice2060!=-1 and2076!=-1 each stop then invalidate-1. Model2120 nonnull destroy then clear0.
// Auxiliary record2128 nonnull destroy model at record+4 then scalar-delete record, but LEAVE entity2128 DANGLING. SIGNED re-read array2264 loop destroys each nonnull model entry;
// model5136 nonnull destroy/clear0; effect slot5076!=-1 release paired emitters/invalidate-1; then release array2264 header/backing. Assign empty CString to RFString24. Scalar-delete
// entity5084 position-array pointer unconditionally, LEAVE field unchanged. Model2124 nonnull destroy, LEAVE field unchanged. Emitter5112 nonnull destroy then clear0. Release
// array5144 BACKING ONLY, not pointed elements. Fixed64 loop: for each nonnull DWORD pointer at4452+4*i and4708+4*i scalar-delete then clear that slot0. Light5252!=-1
// calls5277A0(light,raw0) and invalidates-1 regardless result. Release headers/backing at entity1484 and1608. Entity632 nonnull scalar-delete, LEAVE field unchanged. Finally raw
// intrusive unlink: next=entity656,prev=entity652; next->652=prev, prev->656=next, then entity652/656=0. Both neighbors dereferenced unguarded; XOR EDX,EDX/JNZ backedge unreachable,
// unlink occurs once. Decrement681E10 and return it, not status. No entity-storage delete, common model128 destruction, spawn-model5260 destruction, identifier-table removal,
// complete memset, ownership deduplication, repeatability/null/neighbor guards or rollback in this body; interrupted teardown leaves partial releases/stores, and several fields
// intentionally remain stale.
// UNREALRED VERIFIED [original-target-scan-list-lifetime-20261112]: Native entity cleanup performs preceding resource teardown calls before intrusive unlink at43162D(previous.next=newnext),431645(next.previous=newprev), then43164E/43165B zeros ownnext652/prev656 and decrements681E10. Therefore do not equate dead/type7 presentation transition with entity-list retirement, and do not claim host pre-callback retirement is the native teardown call order.
int __cdecl rf_entity_release_runtime_resources_and_unlink(int a1)
{
  void **v1; // eax
  _DWORD **v2; // eax
  int i; // [esp+1Ch] [ebp-4h]
  int j; // [esp+1Ch] [ebp-4h]
  int k; // [esp+1Ch] [ebp-4h]

  rf_ai_release_embedded_route_and_pointer_array(a1 + 672);
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2252)); ++i )
  {
    v1 = (void **)sub_552200((_DWORD *)(a1 + 2252), i);
    operator delete(*v1);
  }
  rf_pointer_array_release_storage((void **)(a1 + 2252));
  if ( a1 == dword_681E38 )
  {
    dword_681E38 = 0;
    dword_6663C4 = 0;
  }
  if ( *(_DWORD *)(a1 + 2052) != -1 )
  {
    rf_ambient_voice_set_source_gain(*(_DWORD *)(a1 + 2052), 0.0);
    *(_DWORD *)(a1 + 2052) = -1;
  }
  if ( *(_DWORD *)(a1 + 2060) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 2060));
    *(_DWORD *)(a1 + 2060) = -1;
  }
  if ( *(_DWORD *)(a1 + 2076) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 2076));
    *(_DWORD *)(a1 + 2076) = -1;
  }
  if ( *(_DWORD *)(a1 + 2120) )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 2120));
    *(_DWORD *)(a1 + 2120) = 0;
  }
  if ( *(_DWORD *)(a1 + 2128) )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(*(_DWORD *)(a1 + 2128) + 4));
    operator delete(*(void **)(a1 + 2128));
  }
  for ( j = 0; j < rf_receiver_get_first_dword((void *)(a1 + 2264)); ++j )
  {
    if ( *(_DWORD *)sub_552200((_DWORD *)(a1 + 2264), j) )
    {
      v2 = (_DWORD **)sub_552200((_DWORD *)(a1 + 2264), j);
      rf_model_handle_destroy_cdecl_adapter(*v2);
    }
  }
  if ( *(_DWORD *)(a1 + 5136) )
  {
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 5136));
    *(_DWORD *)(a1 + 5136) = 0;
  }
  if ( *(_DWORD *)(a1 + 5076) != -1 )
  {
    rf_firing_effect_slot_release_paired_emitters(*(_DWORD *)(a1 + 5076));
    *(_DWORD *)(a1 + 5076) = -1;
  }
  rf_pointer_array_release_storage((void **)(a1 + 2264));
  rf_string_assign_from_cstr((_DWORD *)(a1 + 24), (char *)&byte_631AD9);
  operator delete(*(void **)(a1 + 5084));
  if ( *(_DWORD *)(a1 + 2124) )
    rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 2124));
  if ( *(_DWORD *)(a1 + 5112) )
  {
    rf_particle_emitter_destroy(*(_DWORD *)(a1 + 5112));
    *(_DWORD *)(a1 + 5112) = 0;
  }
  rf_pointer_array_release_storage((void **)(a1 + 5144));
  for ( k = 0; k < 64; ++k )
  {
    if ( *(_DWORD *)(a1 + 4 * k + 4452) )
    {
      operator delete(*(void **)(a1 + 4 * k + 4452));
      *(_DWORD *)(a1 + 4 * k + 4452) = 0;
    }
    if ( *(_DWORD *)(a1 + 4 * k + 4708) )
    {
      operator delete(*(void **)(a1 + 4 * k + 4708));
      *(_DWORD *)(a1 + 4 * k + 4708) = 0;
    }
  }
  if ( *(_DWORD *)(a1 + 5252) != -1 )
  {
    rf_renderer_light_release(*(_DWORD *)(a1 + 5252), 0);
    *(_DWORD *)(a1 + 5252) = -1;
  }
  rf_pointer_array_release_storage((void **)(a1 + 1484));
  rf_pointer_array_release_storage((void **)(a1 + 1608));
  if ( *(_DWORD *)(a1 + 632) )
    operator delete(*(void **)(a1 + 632));
  *(_DWORD *)(*(_DWORD *)(a1 + 656) + 652) = *(_DWORD *)(a1 + 652);
  *(_DWORD *)(*(_DWORD *)(a1 + 652) + 656) = *(_DWORD *)(a1 + 656);
  *(_DWORD *)(a1 + 652) = 0;
  *(_DWORD *)(a1 + 656) = 0;
  return --unk_681E10;
}

