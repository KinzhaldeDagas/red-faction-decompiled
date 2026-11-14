// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD2A0 rf_powerup_remove_player_kind_and_clear_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(player,kind). Find FIRST matching node. If found update circular root/head/singleton/neighbors, clear links, delete node. Regardless of hit/miss, if player
// nonNULL resolve player+20 as entity, then kind0 clears814mask40000,kind1 clears20000; others no flags changed. Entity work occurs AFTER deletion and never reads freed node;
// function uses original args. Does not clear80000 for kind4, restore kind2/3 stats, play sounds or check runtime/authority. NULL player can still match/delete a NULL-key node before
// entity guard.
void __cdecl rf_powerup_remove_player_kind_and_clear_entity(int a1, int a2)
{
  int v2; // [esp+8h] [ebp-8h]
  _DWORD *v3; // [esp+Ch] [ebp-4h] BYREF

  v3 = nullptr;
  if ( rf_powerup_node_find_player_kind(a1, a2, &v3) )
  {
    if ( (_DWORD *)unk_7B2548 == v3 )
    {
      if ( (_DWORD *)v3[3] == v3 )
      {
        v3[3] = 0;
        v3[4] = 0;
        unk_7B2548 = 0;
LABEL_7:
        operator delete(v3);
        goto LABEL_8;
      }
      unk_7B2548 = v3[3];
    }
    *(_DWORD *)(v3[4] + 12) = v3[3];
    *(_DWORD *)(v3[3] + 16) = v3[4];
    v3[3] = 0;
    v3[4] = 0;
    goto LABEL_7;
  }
LABEL_8:
  if ( a1 )
  {
    v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v2 )
    {
      if ( a2 )
      {
        if ( a2 == 1 )
          rf_entity_clear_state814_mask20000(v2);
      }
      else
      {
        rf_entity_clear_state814_mask40000(v2);
      }
    }
  }
}

