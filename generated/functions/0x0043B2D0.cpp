// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043B2D0 rf_entity_request_body_fire_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(required entity,BYTE alternate). Calls435390 stance selector using only the alternate low byte, then
// reads resolved body-action animation index entity2644+16*slot. Only EXACT-1 triggers fallback, and only when slot!=2: replace slot with2 and index with entity2676. If final index
// is not-1 and436540 active-slot query returns AL0, request436490(entity,slot,FLOAT1,BYTE0,BYTE1). Its outcome is ignored. Within that same admitted branch, after the request, ANY
// nonzero entity DWORD2120 calls model reset adapter565020 with that value, then RE-READS2120 and calls564F90(model2120,track0,FLOAT1,BYTE0). The slot request and auxiliary effects
// have no success/rollback coupling. No other action record prevents this slot request, and no repeated-weapon/body flags are checked in this body. Return register is incidental.
void __cdecl rf_entity_request_body_fire_action(int a1, char a2)
{
  unsigned int v2; // [esp+Ch] [ebp-8h]
  int v3; // [esp+10h] [ebp-4h]

  v2 = rf_entity_select_body_fire_slot_for_stance(a1, a2);
  v3 = *(_DWORD *)(a1 + 16 * v2 + 2644);
  if ( v3 == -1 && v2 != 2 )
  {
    v2 = 2;
    v3 = *(_DWORD *)(a1 + 2676);
  }
  if ( v3 != -1 && !rf_entity_body_action_is_active(a1, v2) )
  {
    rf_entity_request_body_action(a1, v2, 1.0, 0, 1);
    if ( *(_DWORD *)(a1 + 2120) )
    {
      rf_model_handle_reset_actions_adapter(*(_DWORD *)(a1 + 2120));
      rf_vfx_start_instance(*(int **)(a1 + 2120), 0, 1.0, 0);
    }
  }
}

