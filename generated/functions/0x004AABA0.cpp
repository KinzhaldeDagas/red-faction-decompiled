// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AABA0 rf_client_apply_object_kill_payload39
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered original callback [4AABA0,4AB4E4), registry row39 at662B1C. Cdecl(payload,ignored source); no payload length.
// Executes ONLY runtime==1 AND authority==0. Fixed13-byte header: serverID DWORD0,health FLOAT4 (native FLD/FSTP),object flagBYTE8,BYTE9 consumed but otherwise unused,SIGNED
// WORD10,optional-item maskBYTE12. Bits1 and2 INDEPENDENTLY append one identical item record each (both bits can create two). Each: unbounded strlen of wire NUL name, strncpy255 into
// local name then NUL at index254; cursor becomes LOW16(cursor+LOW16(strlen)+1), so skips full original wire name despite bounded copy and can wrap. Then objectBYTE40, four
// DWORDs(itemType,quantity,UID,serverID),position3FLOAT andmatrix9FLOAT in native FLD/FSTP order. Calls item_spawn(itemType,copiedName,UID,-1,position,matrix,quantity,0,1); success
// writes itemBYTE40,sets itemDWORD700 bit8,binds received serverID to new local handle44. Optional item spawns occur BEFORE resolving killed object, and are not rolled back if it is
// absent. Afterwards map fixed serverID to handle then resolve object; if found write health+52,headerBYTE8->object+624,clear commonDWORD124 bit8,set bit0x40,call420B40(object,1.0).
// Only if object kindDWORD36==0 AND SIGNED headerWORD10!=-1, stores sign-extended value at object+2084 AFTER damage helper. Source/BYTE9 unused; no size,string-bound,UID/owner
// validation, malformed-record rollback or direct deletion/allocation of killed object in own body. Restored definition excludes INT3 alignment.
void __cdecl rf_client_apply_object_kill_payload39(void *a1, void *a2)
{
  __int16 v2; // [esp+Ch] [ebp-194h]
  char *v3; // [esp+10h] [ebp-190h]
  __int16 v4; // [esp+1Ch] [ebp-184h]
  char *v5; // [esp+20h] [ebp-180h]
  int v6; // [esp+2Ch] [ebp-174h]
  int v7; // [esp+34h] [ebp-16Ch]
  int v8; // [esp+38h] [ebp-168h] BYREF
  int v9; // [esp+3Ch] [ebp-164h]
  int v10; // [esp+40h] [ebp-160h]
  int v11; // [esp+44h] [ebp-15Ch]
  char v12; // [esp+4Ah] [ebp-156h]
  char v13; // [esp+4Bh] [ebp-155h]
  int v14; // [esp+4Ch] [ebp-154h]
  int v15; // [esp+50h] [ebp-150h]
  __int16 v16; // [esp+54h] [ebp-14Ch]
  float v17; // [esp+58h] [ebp-148h]
  int v18; // [esp+5Ch] [ebp-144h] BYREF
  int v19; // [esp+60h] [ebp-140h]
  int v20; // [esp+64h] [ebp-13Ch]
  int v21; // [esp+68h] [ebp-138h]
  int v22; // [esp+6Ch] [ebp-134h]
  int v23; // [esp+70h] [ebp-130h]
  int v24; // [esp+74h] [ebp-12Ch]
  int v25; // [esp+78h] [ebp-128h]
  int v26; // [esp+7Ch] [ebp-124h]
  char Destination[254]; // [esp+80h] [ebp-120h] BYREF
  char v28; // [esp+17Eh] [ebp-22h]
  int v29; // [esp+188h] [ebp-18h]
  int v30; // [esp+18Ch] [ebp-14h]
  char v31; // [esp+192h] [ebp-Eh]
  char v32; // [esp+193h] [ebp-Dh]
  int v33; // [esp+194h] [ebp-Ch]
  int v34; // [esp+198h] [ebp-8h]
  int v35; // [esp+19Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v30 = 0;
    v29 = *(_DWORD *)a1;
    v30 = 4;
    v17 = *((float *)a1 + 1);
    v30 = 8;
    v31 = *((_BYTE *)a1 + 8);
    v30 = 9;
    v13 = *((_BYTE *)a1 + 9);
    v30 = 10;
    v16 = *((_WORD *)a1 + 5);
    v30 = 12;
    v32 = *((_BYTE *)a1 + 12);
    v30 = 13;
    rf_vector3_default_construct_noop(&v8);
    rf_matrix3_construct((char *)&v18);
    if ( (v32 & 1) != 0 )
    {
      v4 = v30 + (_WORD)a1 + 1;
      v5 = (char *)a1 + v30 + strlen((const char *)a1 + v30) + 1;
      strncpy(Destination, (const char *)a1 + v30, 0xFFu);
      v28 = 0;
      v30 = (unsigned __int16)(v30 + (_WORD)v5 - v4 + 1);
      v12 = *((_BYTE *)a1 + v30);
      v14 = *(_DWORD *)((char *)a1 + ++v30);
      v30 += 4;
      v11 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v33 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v34 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v8 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v9 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v10 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v18 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v19 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v20 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v21 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v22 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v23 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v24 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v25 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v26 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v7 = rf_item_instance_spawn(v14, Destination, v33, -1, (float *)&v8, (float *)&v18, v11, 0, 1);
      if ( v7 )
      {
        *(_BYTE *)(v7 + 40) = v12;
        *(_DWORD *)(v7 + 700) |= 8u;
        rf_replication_bind_server_id_to_local_handle(v34, *(_DWORD *)(v7 + 44));
      }
    }
    if ( (v32 & 2) != 0 )
    {
      v2 = v30 + (_WORD)a1 + 1;
      v3 = (char *)a1 + v30 + strlen((const char *)a1 + v30) + 1;
      strncpy(Destination, (const char *)a1 + v30, 0xFFu);
      v28 = 0;
      v30 = (unsigned __int16)(v30 + (_WORD)v3 - v2 + 1);
      v12 = *((_BYTE *)a1 + v30);
      v14 = *(_DWORD *)((char *)a1 + ++v30);
      v30 += 4;
      v11 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v33 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v34 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v8 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v9 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v10 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v18 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v19 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v20 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v21 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v22 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v23 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v24 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v25 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v26 = *(_DWORD *)((char *)a1 + v30);
      v30 += 4;
      v6 = rf_item_instance_spawn(v14, Destination, v33, -1, (float *)&v8, (float *)&v18, v11, 0, 1);
      if ( v6 )
      {
        *(_BYTE *)(v6 + 40) = v12;
        *(_DWORD *)(v6 + 700) |= 8u;
        rf_replication_bind_server_id_to_local_handle(v34, *(_DWORD *)(v6 + 44));
      }
    }
    v35 = rf_replication_server_id_to_local_handle(v29);
    v15 = rf_object_resolve_handle(v35);
    if ( v15 )
    {
      *(float *)(v15 + 52) = v17;
      *(_BYTE *)(v15 + 624) = v31;
      *(_DWORD *)(v15 + 124) &= ~8u;
      *(_DWORD *)(v15 + 124) |= 0x40u;
      rf_entity_play_damage_or_once_death_sound(v15, 1.0);
      if ( !*(_DWORD *)(v15 + 36) && v16 != -1 )
        *(_DWORD *)(v15 + 2084) = v16;
    }
  }
}

