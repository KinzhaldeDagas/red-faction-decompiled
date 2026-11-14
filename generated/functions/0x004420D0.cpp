// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004420D0 rf_toggle_local_entity_flag4_and_parent_vehicle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments, void/incidental registers. Require DWORD1809818 ANYnonzero, runtime BYTE704E81==0 (ANYnonzero
// rejects), and global entity POINTER681E38 nonnull; otherwise no own changes/delegates. Read COMMON flags DWORD[globalEntity+124] mask4 to choose branch. Initially set: clear ONLY
// mask4 on current global entity BEFORE resolving its CURRENT parent HANDLE DWORD512. Initially clear: set ONLY mask4 first, then resolve parent. Nonnull resolved parent whose
// use-vehicle437690 returns EXACTAL1 gets parent COMMON DWORD124 mask4 cleared/set in SAME chosen direction; false/non1 parent predicate or unresolved parent leaves own toggle
// intact. No relationship/health/movement/death/authority check or rollback. Native repeatedly reloads global681E38 around own writes/parent lookup rather than retaining a separate
// argument pointer.  After clear branch call44B4B0(DWORD[88E37C],0,0,NULL); after set branch call44B4B0(DWORD[88E380],0,0,NULL), ignoring result. Both embedded literal-string
// branches are unreachable because XOR register,register is immediately followed by JZ: actual message always comes from global localized pointer, not literal 'You are mortal
// again'/'You are invulnerable!'. Toggle precedes all parent/message callbacks; no direct health/damage operation or canonical success value.
void rf_toggle_local_entity_flag4_and_parent_vehicle()
{
  _DWORD *v0; // [esp+8h] [ebp-8h]
  _DWORD *v1; // [esp+Ch] [ebp-4h]

  if ( dword_1809818 && !rf_multiplayer_runtime_mode && dword_681E38 )
  {
    if ( (*(_DWORD *)(dword_681E38 + 124) & 4) != 0 )
    {
      *(_DWORD *)(dword_681E38 + 124) &= ~4u;
      v1 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
      if ( v1 )
      {
        if ( rf_object_is_use_vehicle(v1) )
          v1[31] &= ~4u;
      }
      rf_hud_message_enqueue_expand_tokens_and_rearm_head(unk_88E37C, 0, 0, nullptr);
    }
    else
    {
      *(_DWORD *)(dword_681E38 + 124) |= 4u;
      v0 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
      if ( v0 && rf_object_is_use_vehicle(v0) )
        v0[31] |= 4u;
      rf_hud_message_enqueue_expand_tokens_and_rearm_head(unk_88E380, 0, 0, nullptr);
    }
  }
}

