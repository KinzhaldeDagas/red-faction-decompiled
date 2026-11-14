// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A7F20 rf_multiplayer_apply_weapon_fire_payload48
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): Recovered native callback [4A7F20,4A8326), existing original registry row48 at662B88 ->this address. Cdecl(payload,source endpoint), no payload
// length. Read weapon BYTE SIGNED when forwarded, flagsBYTE; mode normalized flags&1. Client runtime1/authority0 then reads unsigned shooter netID BYTE, resolves player/entity or
// returns. Flag4 set calls422CC0(entity,signedWeapon,outPosition,outMatrix,0,1) to reconstruct pose; otherwise reads3 float32 and3 SIGNED WORD directions*original
// DOUBLE3.0517499908455648e-05 (not exact1/32767), storing float32 and constructing orientation matrix. Client ignores source endpoint here. Other runtime/authority path reads
// full18-byte pose immediately after weapon/flags (no shooter ID), then resolves sender by source endpoint and its entity; flag2 decodes hit list at cursor20, negative decoder result
// aborts. Both admitted paths call4A7580(entity,signedWeapon,position,matrix,mode). Does not own size, weapon/finite/vector-length or client-source admission checks. Restored
// function definition/prototype only; original instructions/registry unchanged.
void __cdecl rf_multiplayer_apply_weapon_fire_payload48(void *a1, void *a2)
{
  int v2; // [esp+18h] [ebp-78h]
  __int16 v3; // [esp+1Ch] [ebp-74h]
  __int16 v4; // [esp+1Ch] [ebp-74h]
  __int16 v5; // [esp+1Ch] [ebp-74h]
  float v6[3]; // [esp+20h] [ebp-70h] BYREF
  _DWORD *v7; // [esp+2Ch] [ebp-64h]
  char v8; // [esp+33h] [ebp-5Dh]
  __int16 v9; // [esp+34h] [ebp-5Ch]
  float v10[3]; // [esp+38h] [ebp-58h] BYREF
  char v11; // [esp+47h] [ebp-49h]
  _DWORD *v12; // [esp+48h] [ebp-48h]
  char v13; // [esp+4Fh] [ebp-41h]
  float v14[9]; // [esp+50h] [ebp-40h] BYREF
  float *v15; // [esp+74h] [ebp-1Ch]
  char v16; // [esp+7Bh] [ebp-15h]
  int v17; // [esp+7Ch] [ebp-14h] BYREF
  int v18; // [esp+80h] [ebp-10h]
  int v19; // [esp+84h] [ebp-Ch]
  char v20; // [esp+8Bh] [ebp-5h]
  int v21; // [esp+8Ch] [ebp-4h]

  rf_vector3_default_construct_noop(&v17);
  rf_matrix3_construct((char *)v14);
  v21 = 0;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    rf_vector3_default_construct_noop(v6);
    v16 = *((_BYTE *)a1 + v21);
    v8 = *((_BYTE *)a1 + ++v21);
    ++v21;
    v20 = (v8 & 1) != 0;
    v17 = *(_DWORD *)((char *)a1 + v21);
    v21 += 4;
    v18 = *(_DWORD *)((char *)a1 + v21);
    v21 += 4;
    v19 = *(_DWORD *)((char *)a1 + v21);
    v21 += 4;
    v3 = *(_WORD *)((char *)a1 + v21);
    v21 += 2;
    v6[0] = (double)v3 * 0.00003051749990845565;
    v4 = *(_WORD *)((char *)a1 + v21);
    v21 += 2;
    v6[1] = (double)v4 * 0.00003051749990845565;
    v5 = *(_WORD *)((char *)a1 + v21);
    v21 += 2;
    v6[2] = (double)v5 * 0.00003051749990845565;
    rf_orientation_matrix_from_normalized_direction(v14, v6);
    v7 = rf_player_find_by_network_endpoint((int)a2);
    if ( v7 )
    {
      v15 = (float *)rf_entity_resolve_handle(v7[5]);
      if ( v15 )
      {
        if ( (v8 & 2) != 0 )
        {
          v2 = rf_replication_decode_hit_samples((unsigned __int8 *)a1 + v21, (int)v15);
          if ( v2 < 0 )
            return;
          v21 += v2;
        }
        goto LABEL_13;
      }
    }
  }
  else
  {
    rf_vector3_default_construct_noop(v10);
    v16 = *((_BYTE *)a1 + v21);
    v13 = *((_BYTE *)a1 + ++v21);
    ++v21;
    v20 = (v13 & 1) != 0;
    v11 = *((_BYTE *)a1 + v21++);
    v12 = rf_player_find_by_network_id(v11);
    if ( v12 )
    {
      v15 = (float *)rf_entity_resolve_handle(v12[5]);
      if ( v15 )
      {
        if ( (v13 & 4) != 0 )
        {
          rf_entity_resolve_firing_transform(v15, v16, (float *)&v17, v14, 0, 1);
        }
        else
        {
          v17 = *(_DWORD *)((char *)a1 + v21);
          v21 += 4;
          v18 = *(_DWORD *)((char *)a1 + v21);
          v21 += 4;
          v19 = *(_DWORD *)((char *)a1 + v21);
          v21 += 4;
          v9 = *(_WORD *)((char *)a1 + v21);
          v21 += 2;
          v10[0] = (double)v9 * 0.00003051749990845565;
          v9 = *(_WORD *)((char *)a1 + v21);
          v21 += 2;
          v10[1] = (double)v9 * 0.00003051749990845565;
          v9 = *(_WORD *)((char *)a1 + v21);
          v21 += 2;
          v10[2] = (double)v9 * 0.00003051749990845565;
          rf_orientation_matrix_from_normalized_direction(v14, v10);
        }
LABEL_13:
        rf_multiplayer_apply_received_weapon_fire((int)v15, v16, (float *)&v17, v14, v20);
      }
    }
  }
}

