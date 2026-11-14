// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498E50 rf_client_apply_ctf_flag_state_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Recovered original function [498E50,499798), cdecl(payload). Requires runtime mode1, authority0, game mode1, nonzero initialized77D6E2 and nonnull rf_world_solid. No payload
// length/null or flag-pointer validation. Packet33 association follows exact paired variable record encoding; no static incoming xrefs currently. Reads RED record then BLUE record
// with an integer cursor. Each starts raw BYTE id: FF is sentinel (native signed comparison with-1), every other id is zero-extended for player lookup. Found player sets
// corresponding carrier; unknown player leaves previous carrier/state untouched and consumes only the id byte. No score/contribution-byte mutation.
// For FF reads home BYTE: any nonzero is home, zero means 12 floats follow. Home path calls return_flag_home(selector,sound0) ONLY if instance home bit200 is currently clear; if
// already home there are no additional mutations. Away path reads3 floats into common position+60 and9 floats into common matrix+72; each native DWORD load/store is followed by x87
// fld/fstp on destination. Copies position to physical current+228 and predicted+240, recomputes bounds+400/+412 with radius+384 only when ORDERED radius>0; NaN,zero,negative
// collapse bounds. Clears common+124 mask04000000, sets definition DWORD[DWORD[flag+660]+68] bit2, clears instance+700 home bit200, stores room0 and refreshes room cache/audio.
// Physical orientation+252 is not directly copied. Neither FF branch clears global carrier pointers or arms a selected return timer directly; stale carriers can remain after
// home/away snapshots. Home reset delegate still clears BOTH return timers and arms500ms cooldown; away path does not. No sounds/notifications/network sends in this receiver itself.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662AD4 registers opcode33 (ctf_flag_update), callback0x00498E50. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_ctf_flag_state_payload(const unsigned __int8 *payload)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v5[3]; // [esp+4h] [ebp-D0h] BYREF
  float v6[3]; // [esp+10h] [ebp-C4h] BYREF
  float v7[3]; // [esp+1Ch] [ebp-B8h] BYREF
  float v8[3]; // [esp+28h] [ebp-ACh] BYREF
  float v9[3]; // [esp+34h] [ebp-A0h] BYREF
  float v10[3]; // [esp+40h] [ebp-94h] BYREF
  float v11[3]; // [esp+4Ch] [ebp-88h] BYREF
  float v12[3]; // [esp+58h] [ebp-7Ch] BYREF
  float v13[3]; // [esp+64h] [ebp-70h] BYREF
  float v14[3]; // [esp+70h] [ebp-64h] BYREF
  float v15[3]; // [esp+7Ch] [ebp-58h] BYREF
  float v16[3]; // [esp+88h] [ebp-4Ch] BYREF
  float v17[3]; // [esp+94h] [ebp-40h] BYREF
  float v18[3]; // [esp+A0h] [ebp-34h] BYREF
  float v19[3]; // [esp+ACh] [ebp-28h] BYREF
  float copy_result[3]; // [esp+B8h] [ebp-1Ch] BYREF
  _DWORD *v21; // [esp+C4h] [ebp-10h]
  _DWORD *v22; // [esp+C8h] [ebp-Ch]
  unsigned __int8 v23; // [esp+CDh] [ebp-7h]
  unsigned __int8 v24; // [esp+CEh] [ebp-6h]
  char v25; // [esp+CFh] [ebp-5h]
  int v26; // [esp+D0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && rf_multiplayer_game_mode_get() == 1
    && byte_77D6E2
    && rf_world_solid )
  {
    v26 = 0;
    v24 = *payload;
    v26 = 1;
    if ( (char)v24 == -1 )
    {
      v23 = payload[v26++];
      if ( v23 )
      {
        if ( (*(_DWORD *)(dword_77D6E4 + 700) & 0x200) == 0 )
          rf_ctf_return_flag_home(1, 0);
      }
      else
      {
        *(_DWORD *)(dword_77D6E4 + 60) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 60) = *(float *)(dword_77D6E4 + 60);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 64) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 64) = *(float *)(dword_77D6E4 + 64);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 68) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 68) = *(float *)(dword_77D6E4 + 68);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 72) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 72) = *(float *)(dword_77D6E4 + 72);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 76) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 76) = *(float *)(dword_77D6E4 + 76);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 80) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 80) = *(float *)(dword_77D6E4 + 80);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 84) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 84) = *(float *)(dword_77D6E4 + 84);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 88) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 88) = *(float *)(dword_77D6E4 + 88);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 92) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 92) = *(float *)(dword_77D6E4 + 92);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 96) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 96) = *(float *)(dword_77D6E4 + 96);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 100) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 100) = *(float *)(dword_77D6E4 + 100);
        v26 += 4;
        *(_DWORD *)(dword_77D6E4 + 104) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E4 + 104) = *(float *)(dword_77D6E4 + 104);
        v26 += 4;
        rf_vector_copy((float *)(dword_77D6E4 + 228), copy_result, (const float *)(dword_77D6E4 + 60));
        rf_vector_copy((float *)(dword_77D6E4 + 240), v19, (const float *)(dword_77D6E4 + 60));
        if ( *(float *)(dword_77D6E4 + 384) <= 0.0 )
        {
          rf_vector_copy((float *)(dword_77D6E4 + 400), v14, (const float *)(dword_77D6E4 + 228));
          rf_vector_copy((float *)(dword_77D6E4 + 412), v13, (const float *)(dword_77D6E4 + 228));
        }
        else
        {
          v1 = rf_vector3_subtract_scalar_from_components(
                 (float *)(dword_77D6E4 + 228),
                 v18,
                 *(float *)(dword_77D6E4 + 384));
          rf_vector_copy((float *)(dword_77D6E4 + 400), v17, v1);
          v2 = rf_vector3_add_scalar_to_components((float *)(dword_77D6E4 + 228), v16, *(float *)(dword_77D6E4 + 384));
          rf_vector_copy((float *)(dword_77D6E4 + 412), v15, v2);
        }
        *(_DWORD *)(dword_77D6E4 + 124) &= ~0x4000000u;
        *(_DWORD *)(*(_DWORD *)(dword_77D6E4 + 660) + 68) |= 2u;
        *(_DWORD *)(dword_77D6E4 + 700) &= ~0x200u;
        rf_object_store_room_pointer_only((_DWORD *)dword_77D6E4, 0);
        rf_object_refresh_room_cache_and_audio((void *)dword_77D6E4);
      }
    }
    else
    {
      v22 = rf_player_find_by_network_id(v24);
      if ( v22 )
        rf_ctf_red_carrier_set((int)v22);
    }
    v25 = payload[v26++];
    if ( v25 == -1 )
    {
      v23 = payload[v26++];
      if ( v23 )
      {
        if ( (*(_DWORD *)(dword_77D6E8 + 700) & 0x200) == 0 )
          rf_ctf_return_flag_home(0, 0);
      }
      else
      {
        *(_DWORD *)(dword_77D6E8 + 60) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 60) = *(float *)(dword_77D6E8 + 60);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 64) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 64) = *(float *)(dword_77D6E8 + 64);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 68) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 68) = *(float *)(dword_77D6E8 + 68);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 72) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 72) = *(float *)(dword_77D6E8 + 72);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 76) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 76) = *(float *)(dword_77D6E8 + 76);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 80) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 80) = *(float *)(dword_77D6E8 + 80);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 84) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 84) = *(float *)(dword_77D6E8 + 84);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 88) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 88) = *(float *)(dword_77D6E8 + 88);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 92) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 92) = *(float *)(dword_77D6E8 + 92);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 96) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 96) = *(float *)(dword_77D6E8 + 96);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 100) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 100) = *(float *)(dword_77D6E8 + 100);
        v26 += 4;
        *(_DWORD *)(dword_77D6E8 + 104) = *(_DWORD *)&payload[v26];
        *(float *)(dword_77D6E8 + 104) = *(float *)(dword_77D6E8 + 104);
        v26 += 4;
        rf_vector_copy((float *)(dword_77D6E8 + 228), v12, (const float *)(dword_77D6E8 + 60));
        rf_vector_copy((float *)(dword_77D6E8 + 240), v11, (const float *)(dword_77D6E8 + 60));
        if ( *(float *)(dword_77D6E8 + 384) <= 0.0 )
        {
          rf_vector_copy((float *)(dword_77D6E8 + 400), v6, (const float *)(dword_77D6E8 + 228));
          rf_vector_copy((float *)(dword_77D6E8 + 412), v5, (const float *)(dword_77D6E8 + 228));
        }
        else
        {
          v3 = rf_vector3_subtract_scalar_from_components(
                 (float *)(dword_77D6E8 + 228),
                 v10,
                 *(float *)(dword_77D6E8 + 384));
          rf_vector_copy((float *)(dword_77D6E8 + 400), v9, v3);
          v4 = rf_vector3_add_scalar_to_components((float *)(dword_77D6E8 + 228), v8, *(float *)(dword_77D6E8 + 384));
          rf_vector_copy((float *)(dword_77D6E8 + 412), v7, v4);
        }
        *(_DWORD *)(dword_77D6E8 + 124) &= ~0x4000000u;
        *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) |= 2u;
        *(_DWORD *)(dword_77D6E8 + 700) &= ~0x200u;
        rf_object_store_room_pointer_only((_DWORD *)dword_77D6E8, 0);
        rf_object_refresh_room_cache_and_audio((void *)dword_77D6E8);
      }
    }
    else
    {
      v21 = rf_player_find_by_network_id(v25);
      if ( v21 )
        rf_ctf_blue_carrier_set((int)v21);
    }
  }
}

