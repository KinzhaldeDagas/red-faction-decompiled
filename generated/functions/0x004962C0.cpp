// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004962C0 rf_ctf_flags_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Requires raw game mode 1 and nonzero initialized byte 77D6E2. For each nonnull red/blue carrier, resolves player entity handle +20 and skips unresolved entities. Uses carrier and
// flag model +128 $prop_flag nodes; composes carrier transform M,L, then composes the flag node using its OLD common matrix +72 and parent position L. Final flag position is L+(L-R),
// retaining temporary-vector rounding. Writes common/current/predicted positions +60/+228/+240; expands bounds +400/+412 only for ORDERED physical radius +384 > 0, otherwise
// collapses both bounds to the point (including NaN). Clears common flags +124 mask 04000000, then copies M to common matrix +72 and carrier room DWORD0 to flag room. Physical
// orientation +252 is not directly written. No model/node/flag validation.
// Only runtime mode 1 and authority exactly 1 processes return timers, red 77D710 first then blue 77D75C, accepting elapsed result exactly 1. Resets selected timer, returns flag home
// with sound, broadcasts packet34, and emits null-player return feedback. Returning either flag home clears BOTH return timers: red processing can cancel the pending blue deadline
// before its check. Packet34 does not rearm either timer. Independently of authority, sound timer 77D730 elapsed exactly 1 plays event79 and resets it. No stable semantic return
// value.
int rf_ctf_flags_update()
{
  int result; // eax
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  int first_dword; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  int v8; // eax
  float v9[3]; // [esp+8h] [ebp-1E8h] BYREF
  float v10[3]; // [esp+14h] [ebp-1DCh] BYREF
  float v11[3]; // [esp+20h] [ebp-1D0h] BYREF
  int v12[3]; // [esp+2Ch] [ebp-1C4h] BYREF
  float v13[3]; // [esp+38h] [ebp-1B8h] BYREF
  int v14[3]; // [esp+44h] [ebp-1ACh] BYREF
  float v15[3]; // [esp+50h] [ebp-1A0h] BYREF
  float v16[3]; // [esp+5Ch] [ebp-194h] BYREF
  float v17[3]; // [esp+68h] [ebp-188h] BYREF
  float v18[3]; // [esp+74h] [ebp-17Ch] BYREF
  float v19[3]; // [esp+80h] [ebp-170h] BYREF
  float v20[3]; // [esp+8Ch] [ebp-164h] BYREF
  float v21[3]; // [esp+98h] [ebp-158h] BYREF
  int v22[3]; // [esp+A4h] [ebp-14Ch] BYREF
  float v23[3]; // [esp+B0h] [ebp-140h] BYREF
  int v24[3]; // [esp+BCh] [ebp-134h] BYREF
  float v25[3]; // [esp+C8h] [ebp-128h] BYREF
  float v26[3]; // [esp+D4h] [ebp-11Ch] BYREF
  float copy_result[3]; // [esp+E0h] [ebp-110h] BYREF
  float sum_result[3]; // [esp+ECh] [ebp-104h] BYREF
  float v29[3]; // [esp+F8h] [ebp-F8h] BYREF
  float v30[3]; // [esp+104h] [ebp-ECh] BYREF
  int v31; // [esp+110h] [ebp-E0h]
  float v32[3]; // [esp+114h] [ebp-DCh] BYREF
  float v33[9]; // [esp+120h] [ebp-D0h] BYREF
  int v34; // [esp+144h] [ebp-ACh]
  char v35[36]; // [esp+148h] [ebp-A8h] BYREF
  int v36; // [esp+16Ch] [ebp-84h]
  float lhs[3]; // [esp+170h] [ebp-80h] BYREF
  float out_vector[3]; // [esp+17Ch] [ebp-74h] BYREF
  int v39; // [esp+188h] [ebp-68h]
  float rhs[3]; // [esp+18Ch] [ebp-64h] BYREF
  float v41[9]; // [esp+198h] [ebp-58h] BYREF
  int node_adapter; // [esp+1BCh] [ebp-34h]
  char v43[36]; // [esp+1C0h] [ebp-30h] BYREF
  int v44; // [esp+1E4h] [ebp-Ch]
  int v45; // [esp+1E8h] [ebp-8h]
  int v46; // [esp+1ECh] [ebp-4h]

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    result = (unsigned __int8)byte_77D6E2;
    if ( byte_77D6E2 )
    {
      v46 = rf_ctf_red_carrier_get();
      if ( v46 )
      {
        v44 = rf_entity_resolve_handle(*(_DWORD *)(v46 + 20));
        if ( v44 )
        {
          node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(v44 + 128), "$prop_flag");
          rf_matrix3_construct((char *)v41);
          rf_vector3_default_construct_noop(lhs);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(v44 + 128),
            node_adapter,
            (float *)(v44 + 72),
            v44 + 60,
            (int)v41,
            lhs);
          v39 = rf_model_handle_find_node_adapter(*(_DWORD *)(dword_77D6E4 + 128), "$prop_flag");
          rf_matrix3_construct(v43);
          rf_vector3_default_construct_noop(rhs);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(dword_77D6E4 + 128),
            v39,
            (float *)(dword_77D6E4 + 72),
            (int)lhs,
            (int)v43,
            rhs);
          rf_vector_subtract(lhs, out_vector, rhs);
          v1 = rf_vector_add(lhs, sum_result, out_vector);
          rf_vector_copy((float *)(dword_77D6E4 + 60), copy_result, v1);
          rf_vector_copy((float *)(dword_77D6E4 + 228), v26, (const float *)(dword_77D6E4 + 60));
          rf_vector_copy((float *)(dword_77D6E4 + 240), v25, (const float *)(dword_77D6E4 + 60));
          if ( *(float *)(dword_77D6E4 + 384) <= 0.0 )
          {
            rf_vector_copy((float *)(dword_77D6E4 + 400), v20, (const float *)(dword_77D6E4 + 228));
            rf_vector_copy((float *)(dword_77D6E4 + 412), v19, (const float *)(dword_77D6E4 + 228));
          }
          else
          {
            v2 = rf_vector3_subtract_scalar_from_components(
                   (float *)(dword_77D6E4 + 228),
                   (float *)v24,
                   *(float *)(dword_77D6E4 + 384));
            rf_vector_copy((float *)(dword_77D6E4 + 400), v23, v2);
            v3 = rf_vector3_add_scalar_to_components(
                   (float *)(dword_77D6E4 + 228),
                   (float *)v22,
                   *(float *)(dword_77D6E4 + 384));
            rf_vector_copy((float *)(dword_77D6E4 + 412), v21, v3);
          }
          *(_DWORD *)(dword_77D6E4 + 124) &= ~0x4000000u;
          rf_matrix3_copy((float *)(dword_77D6E4 + 72), v41);
          first_dword = rf_receiver_get_first_dword((void *)v44);
          rf_object_store_room_pointer_only((_DWORD *)dword_77D6E4, first_dword);
        }
      }
      v45 = rf_ctf_blue_carrier_get();
      if ( v45 )
      {
        v36 = rf_entity_resolve_handle(*(_DWORD *)(v45 + 20));
        if ( v36 )
        {
          v34 = rf_model_handle_find_node_adapter(*(_DWORD *)(v36 + 128), "$prop_flag");
          rf_matrix3_construct((char *)v33);
          rf_vector3_default_construct_noop(v29);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(v36 + 128),
            v34,
            (float *)(v36 + 72),
            v36 + 60,
            (int)v33,
            v29);
          v31 = rf_model_handle_find_node_adapter(*(_DWORD *)(dword_77D6E8 + 128), "$prop_flag");
          rf_matrix3_construct(v35);
          rf_vector3_default_construct_noop(v32);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(dword_77D6E8 + 128),
            v31,
            (float *)(dword_77D6E8 + 72),
            (int)v29,
            (int)v35,
            v32);
          rf_vector_subtract(v29, v30, v32);
          v5 = rf_vector_add(v29, v18, v30);
          rf_vector_copy((float *)(dword_77D6E8 + 60), v17, v5);
          rf_vector_copy((float *)(dword_77D6E8 + 228), v16, (const float *)(dword_77D6E8 + 60));
          rf_vector_copy((float *)(dword_77D6E8 + 240), v15, (const float *)(dword_77D6E8 + 60));
          if ( *(float *)(dword_77D6E8 + 384) <= 0.0 )
          {
            rf_vector_copy((float *)(dword_77D6E8 + 400), v10, (const float *)(dword_77D6E8 + 228));
            rf_vector_copy((float *)(dword_77D6E8 + 412), v9, (const float *)(dword_77D6E8 + 228));
          }
          else
          {
            v6 = rf_vector3_subtract_scalar_from_components(
                   (float *)(dword_77D6E8 + 228),
                   (float *)v14,
                   *(float *)(dword_77D6E8 + 384));
            rf_vector_copy((float *)(dword_77D6E8 + 400), v13, v6);
            v7 = rf_vector3_add_scalar_to_components(
                   (float *)(dword_77D6E8 + 228),
                   (float *)v12,
                   *(float *)(dword_77D6E8 + 384));
            rf_vector_copy((float *)(dword_77D6E8 + 412), v11, v7);
          }
          *(_DWORD *)(dword_77D6E8 + 124) &= ~0x4000000u;
          rf_matrix3_copy((float *)(dword_77D6E8 + 72), v33);
          v8 = rf_receiver_get_first_dword((void *)v36);
          rf_object_store_room_pointer_only((_DWORD *)dword_77D6E8, v8);
        }
      }
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( rf_replicator_has_elapsed(&unk_77D710) )
        {
          rf_replicator_reset(&unk_77D710);
          rf_ctf_return_flag_home(1, 1);
          rf_ctf_broadcast_flag_returned_packet34(1, 0);
          rf_ctf_flag_return_notification(0, 1);
        }
        if ( rf_replicator_has_elapsed(&unk_77D75C) )
        {
          rf_replicator_reset(&unk_77D75C);
          rf_ctf_return_flag_home(0, 1);
          rf_ctf_broadcast_flag_returned_packet34(0, 0);
          rf_ctf_flag_return_notification(0, 0);
        }
      }
      result = rf_replicator_has_elapsed(&unk_77D730);
      if ( (unsigned __int8)result == 1 )
      {
        rf_gamesound_play_event(79, 0, 0.0, 1.0);
        return (int)rf_replicator_reset(&unk_77D730);
      }
    }
  }
  return result;
}

