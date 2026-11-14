// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8F70 rf_multiplayer_apply_entity_update_payload38
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): Recovered callback [4A8F70,4A99C6), registry row38 at662B10. Cdecl(payload,sourceEndpoint), no payload length; loops DWORD identity until-1
// sentinel, reads maskBYTE. Client runtime1/authority0 arms shared450ms deadline then resolves each identity by UID; others resolve handle. Resolves entity through object.handle44;
// entity2064 bit1 OR common124 bit0x40 suppresses entity application but payload still consumed. No source-to-identity ownership check in this body. Per record zeroes velocity and
// both angle vectors; timestampWORD initialized0 ONCE before loop, position/final-vector default constructors are no-ops. Motion bit1: timestampWORD,position3FLOAT32,copy shared
// vector17F10B0 into final vector, SIGNED angleWORD/32767*DOUBLE1.600000023841858 and SIGNED angleWORD/32767*DOUBLE6.33318567276001,actionBYTE apply(selector0) when entity exists.
// Velocity: SIGNED x/y BYTE divided127 to float32; if ORDERED x+y==0 sets z=1 (sum test, NOT x==0 AND y==0), else z=sqrt(round32(1-(x*x+y*y))) with no radicand clamp. Packed
// magnitudeBYTE highbit negates z,low7 scales vector. ONLY runtime1/authorityEXACT1 consumes extra SIGNED weapon-selectionBYTE; with entity/buffer and sender, applies owned-selection
// when timestamp delta>=0. Delta uses65535 (not65536): new>60535 &&old<5000 ->new+old-65535; else old>60535 &&new<5000 ->new+65535-old; else new-old; no prior sample ->delta0.
// Remaining fields consumed in order: bit0x80 powerupBYTE/apply; bit8 hit list/decode, failure aborts entire callback. Existing remote entity: bit0x40
// ->4222C0(handle,currentWeapon,bool(mask&0x10)), else stop firing. Bit2 consumes unsigned statisticsWORD; authorityEXACT1 re-finds source player, writes
// net1456=round32(1-word/netSIGNED528), clamps[0,1], resets net statistics window; no divisor-zero guard. Bit4 consumes SIGNED weaponBYTE; if entity alive,weapon>=0 and differs,
// grants inventory then maps owning player: local entity/local player marks remote-charge special case and sets pending weapon/disarms timer184; remote owner selects by class.
// Bit0x20 consumes health/armorWORD(low/high unsignedBYTE) plus damageBYTE; local ordered decrease triggers red tint, optional direction bits and420B40 when
// round32((oldHealth-newHealth)/classMaxHealth)>0.001; then writes health/armor for any admitted entity. Finally any admitted NONLOCAL entity with motion buffer appends
// sample(delay0) even if motion bit absent: position/final vector may remain unset/retained and timestamp carries last record. No no-op constructors turned into zeroing, packet
// rollback, size/count bound, blanket server/client admission or timestamp-based whole-record rejection.
void __cdecl rf_multiplayer_apply_entity_update_payload38(void *a1, void *a2)
{
  float v2; // [esp+4h] [ebp-F0h]
  float v3; // [esp+18h] [ebp-DCh]
  float copy_result[3]; // [esp+2Ch] [ebp-C8h] BYREF
  float v5; // [esp+38h] [ebp-BCh]
  float v6; // [esp+3Ch] [ebp-B8h]
  float v7; // [esp+40h] [ebp-B4h]
  char v8; // [esp+47h] [ebp-ADh]
  __int16 v9; // [esp+48h] [ebp-ACh]
  int player; // [esp+4Ch] [ebp-A8h]
  char v11; // [esp+53h] [ebp-A1h]
  _DWORD *v12; // [esp+54h] [ebp-A0h]
  unsigned __int16 v13; // [esp+58h] [ebp-9Ch]
  int v14; // [esp+5Ch] [ebp-98h]
  char v15; // [esp+63h] [ebp-91h] BYREF
  int v16; // [esp+64h] [ebp-90h]
  char v17; // [esp+69h] [ebp-8Bh]
  char v18; // [esp+6Ah] [ebp-8Ah]
  char v19; // [esp+6Bh] [ebp-89h]
  __int16 v20; // [esp+6Ch] [ebp-88h]
  __int16 v21; // [esp+70h] [ebp-84h]
  unsigned __int8 v22; // [esp+77h] [ebp-7Dh] BYREF
  int v23; // [esp+78h] [ebp-7Ch]
  int v24; // [esp+7Ch] [ebp-78h]
  float v25[3]; // [esp+80h] [ebp-74h] BYREF
  float v26[3]; // [esp+8Ch] [ebp-68h] BYREF
  _DWORD v27[3]; // [esp+98h] [ebp-5Ch] BYREF
  unsigned __int16 v28; // [esp+A4h] [ebp-50h]
  int v29; // [esp+A8h] [ebp-4Ch]
  float v30; // [esp+ACh] [ebp-48h] BYREF
  float v31; // [esp+B0h] [ebp-44h]
  float v32; // [esp+B4h] [ebp-40h]
  char v33[39]; // [esp+B8h] [ebp-3Ch] BYREF
  unsigned __int8 v34; // [esp+DFh] [ebp-15h]
  _DWORD *v35; // [esp+E0h] [ebp-14h]
  int v36; // [esp+E4h] [ebp-10h]
  float destination[3]; // [esp+E8h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v27);
  rf_vector3_default_construct_noop(&v30);
  rf_vector3_default_construct_noop(destination);
  rf_matrix3_construct(v33);
  v28 = 0;
  v36 = 0;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    rf_multiplayer_arm_deadline_704F0C_450ms();
  v35 = rf_player_find_by_network_endpoint((int)a2);
  while ( 1 )
  {
    v29 = *(_DWORD *)((char *)a1 + v36);
    v36 += 4;
    if ( v29 == -1 )
      break;
    v34 = *((_BYTE *)a1 + v36++);
    v24 = 0;
    v23 = 0;
    if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      v24 = rf_object_resolve_handle(v29);
    else
      v24 = rf_object_find_by_uid(v29);
    if ( v24 )
      v23 = rf_entity_resolve_handle(*(_DWORD *)(v24 + 44));
    if ( v23 && ((*(_DWORD *)(v23 + 2064) & 1) != 0 || (*(_DWORD *)(v23 + 124) & 0x40) != 0) )
    {
      v23 = 0;
      v24 = 0;
    }
    rf_vector3_default_construct_noop(v25);
    rf_vector3_default_construct_noop(v26);
    rf_vector3_zero_return_destination(&v30);
    rf_vector3_zero_return_destination(v25);
    rf_vector3_zero_return_destination(v26);
    if ( ((unsigned __int8)word_662BE8 & v34) != 0 )
    {
      v28 = *(_WORD *)((char *)a1 + v36);
      v36 += 2;
      v27[0] = *(_DWORD *)((char *)a1 + v36);
      v36 += 4;
      v27[1] = *(_DWORD *)((char *)a1 + v36);
      v36 += 4;
      v27[2] = *(_DWORD *)((char *)a1 + v36);
      v36 += 4;
      rf_vector_copy(destination, copy_result, flt_17F10B0);
      v21 = *(_WORD *)((char *)a1 + v36);
      v36 += 2;
      v26[0] = (double)v21 / 32767.0 * 1.600000023841858;
      v20 = *(_WORD *)((char *)a1 + v36);
      v36 += 2;
      v25[1] = (double)v20 / 32767.0 * 6.33318567276001;
      v22 = 0;
      v22 = *((_BYTE *)a1 + v36++);
      if ( v23 )
        rf_replication_encode_or_apply_entity_action_bits((_DWORD *)v23, &v22, 0);
      v19 = *((_BYTE *)a1 + v36++);
      v30 = (double)v19 / 127.0;
      v19 = *((_BYTE *)a1 + v36++);
      v31 = (double)v19 / 127.0;
      if ( v30 + v31 == 0.0 )
      {
        v32 = 1.0;
      }
      else
      {
        v3 = 1.0 - (v30 * v30 + v31 * v31);
        v32 = rf_sqrt_float(v3);
      }
      v18 = *((_BYTE *)a1 + v36++);
      if ( v18 < 0 )
        v32 = v32 * -1.0;
      v2 = (float)(v18 & 0x7F);
      rf_vector3_scale_in_place_return_self(&v30, v2);
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        v17 = *((_BYTE *)a1 + v36++);
        if ( v23 )
        {
          if ( *(_DWORD *)(v23 + 632) )
          {
            v16 = 0;
            if ( *(int *)(*(_DWORD *)(v23 + 632) + 1332) > 0 )
            {
              if ( 0xFFFF - v28 >= 5000
                || *(unsigned __int16 *)(*(_DWORD *)(v23 + 632) + 2 * *(_DWORD *)(*(_DWORD *)(v23 + 632) + 1332) + 1278) >= 0x1388u )
              {
                if ( 0xFFFF
                   - *(unsigned __int16 *)(*(_DWORD *)(v23 + 632) + 2 * *(_DWORD *)(*(_DWORD *)(v23 + 632) + 1332) + 1278) >= 5000
                  || v28 >= 0x1388u )
                {
                  v16 = v28
                      - *(unsigned __int16 *)(*(_DWORD *)(v23 + 632)
                                            + 2 * *(_DWORD *)(*(_DWORD *)(v23 + 632) + 1332)
                                            + 1278);
                }
                else
                {
                  v16 = v28
                      + 0xFFFF
                      - *(unsigned __int16 *)(*(_DWORD *)(v23 + 632)
                                            + 2 * *(_DWORD *)(*(_DWORD *)(v23 + 632) + 1332)
                                            + 1278);
                }
              }
              else
              {
                v16 = *(unsigned __int16 *)(*(_DWORD *)(v23 + 632)
                                          + 2 * *(_DWORD *)(*(_DWORD *)(v23 + 632) + 1332)
                                          + 1278)
                    + v28
                    - 0xFFFF;
              }
            }
            if ( v35 && v16 >= 0 )
              rf_player_apply_owned_network_weapon_selection((int)v35, v23, v17);
          }
        }
      }
    }
    if ( ((unsigned __int8)word_662C20 & v34) != 0 )
    {
      v15 = 0;
      v15 = *((_BYTE *)a1 + v36++);
      if ( v23 )
        rf_replication_apply_entity_powerup_bits(v23, &v15);
    }
    if ( ((unsigned __int8)word_662C00 & v34) != 0 )
    {
      v14 = rf_replication_decode_hit_samples((unsigned __int8 *)a1 + v36, v23);
      if ( v14 < 0 )
        return;
      v36 += v14;
    }
    if ( v23 && v23 != dword_681E38 )
    {
      if ( ((unsigned __int8)word_662C18 & v34) != 0 )
        rf_entity_begin_weapon_firing_state_and_effects(
          *(_DWORD *)(v23 + 44),
          *(_DWORD *)(v23 + 676),
          (unsigned __int8)(word_662C08 & v34) != 0);
      else
        rf_entity_stop_weapon_firing(*(_DWORD *)(v23 + 44), *(_DWORD *)(v23 + 676));
    }
    if ( ((unsigned __int8)word_662BF0 & v34) != 0 )
    {
      v13 = *(_WORD *)((char *)a1 + v36);
      v36 += 2;
      if ( rf_multiplayer_server_authority == 1 )
      {
        v12 = rf_player_find_by_network_endpoint((int)a2);
        if ( v12 )
        {
          *(float *)(v12[1152] + 1456) = 1.0 - (double)v13 / (double)*(int *)(v12[1152] + 528);
          rf_float_clamp_in_place((float *)(v12[1152] + 1456), 0.0, 1.0);
          rf_net_statistics_reset_packet38_window((int *)(v12[1152] + 28));
        }
      }
    }
    if ( ((unsigned __int8)word_662BF8 & v34) != 0 )
    {
      v11 = *((_BYTE *)a1 + v36++);
      if ( v23 )
      {
        if ( !rf_entity_is_dead(v23) && v11 >= 0 && v11 != *(_DWORD *)(v23 + 676) )
        {
          rf_entity_inventory_grant_weapon((int *)(v23 + 672), v11, -1);
          player = (int)sub_4DD720(*(_DWORD *)(v23 + 44));
          if ( v23 == dword_681E38 )
          {
            if ( player && player == rf_local_fpgun_player )
            {
              if ( v11 == dword_911C78 )
                rf_local_fpgun_mark_remote_charge_selected();
              rf_player_set_pending_weapon_and_disarm_timer184(rf_local_fpgun_player, v11);
            }
          }
          else if ( player && player != rf_local_fpgun_player )
          {
            rf_player_apply_weapon_selection_by_class(player, v11);
          }
        }
      }
    }
    if ( ((unsigned __int8)word_662C10 & v34) != 0 )
    {
      v9 = *(_WORD *)((char *)a1 + v36);
      v36 += 2;
      v8 = *((_BYTE *)a1 + v36++);
      if ( v23 )
      {
        v7 = (float)(unsigned __int8)v9;
        v6 = (float)((v9 & 0xFF00) >> 8);
        if ( (*(float *)(v23 + 52) > (double)v7 || *(float *)(v23 + 56) > (double)v6) && v23 == dword_681E38 )
        {
          rf_player_hud_damage_tint_red();
          if ( v8 )
            rf_player_or_direction_nibble_into_flags(rf_local_fpgun_player, v8);
          v5 = (*(float *)(v23 + 52) - v7) / *(float *)(*(_DWORD *)(v23 + 660) + 68);
          if ( v5 > 0.001 )
            rf_entity_play_damage_or_once_death_sound(v23, v5);
        }
        *(float *)(v23 + 52) = v7;
        *(float *)(v23 + 56) = v6;
      }
    }
    if ( v23 && v23 != dword_681E38 )
    {
      if ( *(_DWORD *)(v23 + 632) )
        rf_motion_sample_buffer_insert_and_extend_curve(
          *(_DWORD *)(v23 + 632),
          v23,
          (int)v27,
          (int)v25,
          (int)v26,
          (int)&v30,
          (int)destination,
          v28,
          0.0);
    }
  }
}

