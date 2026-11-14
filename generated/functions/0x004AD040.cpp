// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD040 rf_powerup_apply_or_refresh_player_kind
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(player,kind,milliseconds). First find existing exact key in root7B2548; hit only rearms node deadline+8 with signed milliseconds and RETURNS immediately,
// without replaying sounds/entity flag setters or checking timed-kind table. Miss uses UNCHECKED DWORD662C38[kind], original five rows[1,1,0,0,0]. Table==1 allocates20 bytes,
// constructs only deadline+8, writes player0/kind4, arms deadline, appends circular TAIL (new head only if empty); NULL allocation path is subsequently dereferenced, not graceful
// failure. Other table values: only runtime1 authority EXACT1 and kind2/3 resolve object from player+20 WITHOUT NULL player/object checks; set object float56(kind2) or52(kind3) to200
// under second runtime!=1 OR authority!=0 gate, then gamesound event(0,0,0.0,1.0). All miss paths then, if player nonNULL and entity handle+20 resolves to entity, kind0 sets
// Entity814mask40000 via43C680;kind1 sets20000 via43C610; other kinds no flag setter. This final flag application has no own runtime gate. No range check for kind, no time clamp, no
// max(previous,new) policy; refresh replaces deadline. EAX incidental/delegate return, not uniform status.
int __cdecl rf_powerup_apply_or_refresh_player_kind(int a1, int a2, int a3)
{
  int result; // eax
  _DWORD *v4; // [esp+10h] [ebp-2Ch]
  void *v5; // [esp+14h] [ebp-28h]
  int v6; // [esp+20h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-18h]
  int v8; // [esp+2Ch] [ebp-10h] BYREF
  int v9; // [esp+38h] [ebp-4h]

  v8 = 0;
  result = (unsigned __int8)rf_powerup_node_find_player_kind(a1, a2, &v8);
  if ( (_BYTE)result )
    return rf_replicator_arm_milliseconds((int *)(v8 + 8), a3);
  if ( dword_662C38[a2] == 1 )
  {
    v5 = operator new(0x14u);
    v9 = 0;
    if ( v5 )
      v4 = (_DWORD *)rf_powerup_node_construct_deadline_only((int)v5);
    else
      v4 = nullptr;
    v9 = -1;
    *v4 = a1;
    v4[1] = a2;
    rf_replicator_arm_milliseconds(v4 + 2, a3);
    if ( unk_7B2548 )
    {
      v4[4] = *(_DWORD *)(unk_7B2548 + 16);
      v4[3] = unk_7B2548;
      *(_DWORD *)(*(_DWORD *)(unk_7B2548 + 16) + 12) = v4;
      result = (int)v4;
      *(_DWORD *)(unk_7B2548 + 16) = v4;
    }
    else
    {
      v4[3] = v4;
      result = (int)v4;
      v4[4] = v4;
      unk_7B2548 = v4;
    }
    goto LABEL_22;
  }
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    result = rf_multiplayer_server_authority;
    if ( rf_multiplayer_server_authority == 1 )
    {
      if ( a2 == 2 )
      {
        v7 = rf_object_resolve_handle(*(_DWORD *)(a1 + 20));
        if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
          *(float *)(v7 + 56) = 200.0;
LABEL_21:
        result = rf_gamesound_play_event(0, 0, 0.0, 1.0);
        goto LABEL_22;
      }
      if ( a2 == 3 )
      {
        v6 = rf_object_resolve_handle(*(_DWORD *)(a1 + 20));
        if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
          *(float *)(v6 + 52) = 200.0;
        goto LABEL_21;
      }
    }
  }
LABEL_22:
  if ( a1 )
  {
    result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( result )
    {
      if ( a2 )
      {
        if ( a2 == 1 )
          return rf_entity_set_state814_mask20000_with_sound84(result);
      }
      else
      {
        return rf_entity_set_state814_mask40000_with_sound86(result);
      }
    }
  }
  return result;
}

