// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00484E60 rf_geomod_operation_admit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl(float requested_radius,owner_handle,room_ptr,world_position3f*,impact_normal3f*,cutter_id,BYTE input_flags), returns AL. Rejects only mode byte==1 with authority0; exact
// mode1/authority1 further requires global DWORD0x704EEC nonzero and, unless byte6FCCF9 nonzero, network-history count<that signed limit. This compares global DWORD value, not
// dereferenced pointer content. Other nonzero authority values bypass exact-server quota. Requires nonnull room pointer and resolved cutter. Native requested-radius gate admits
// ordered>=1 OR unordered (TEST AH,5/JP), not finite-only validation.
// Constructs no-op operation100, stores cutter id0,room DWORD+32 as id4,flags56=0,impact normal64=input normal. Scale60=1 if input bit8, otherwise
// F32(requested_radius/cutter.radius96) without zero guard. Calls georegions_apply(world_position,op,1); AL0 rejects. If input bit8 set, forces scale back to1 AFTER region
// admission/hardness work. Resolves owner handle; input bit4 copies owner common matrix72 when found, otherwise identity, and bit4 absent uses random orientation. Input bit1 OR
// global6FCCFA sets operation flag1 (no physical debris). Input bit0x10 OR same global sets operation flag4 (decal suppression). Input bit0x20 sets operation flag8 and zeroes
// constraint76/88; region-derived flag0x10 (ice) is separate from those input bits.
// Duplicate scan walks saved32-byte records at0x6FCD00,count6FCCF4: same ZERO-EXTENDED u16 cutter id versus full operation id AND room DWORD+4, decode saved position8 using current
// world bounds, compare squared distance to original caller world_position. Ordered<=exact double0.04000000283122063 OR UNORDERED rejects; other flags/orientation/scale are ignored
// for duplicate identity. Scan occurs after region/owner/RNG work. No decoded-position cache or raw original-float comparison.
// Only signed saved count<128 encloses BOTH execution_queue_append(op) AND saved-record write/count increment. Queue result not checked. Record32 layout: u16 cutter0,u16(flags|1)
// at2,roomDWORD4,position3*u16 at8,normal3*s16 at14,quaternion4*s16 at20,scaleFLOAT28. Forces saved flag1 regardless live op, suppressing physical debris on replay. Position encodes
// ORIGINAL world_position while sidecar0x6FDD50+36*i stores adjusted op.position8 and constraint76/88; quaternion packs runtime matrix, normal packs copied input normal. Does not
// serialize sidecar as part of32-byte record. At count>=128 skips queue AND save but proceeds to presentation and can return1; AL1 does not prove terrain was scheduled.
// Unless global presentation BYTE704E83==1: when input bit1 clear and global6FCCFA zero, spawns impact fragments at adjusted op.position using scale*cutter radius, ORIGINAL input
// normal, selected base/ice bitmap and caller room. Sound selection uses local player's referenced room to test ORIGINAL world_position for liquid; if true random events22..24, else
// ice flag0x10 random25..27, else projectile-specific weapon GeoMod event or fallback6..8. Positional gain1, global sound context,flags0. No local-player pointer guard. Presentation
// skipped by byte==1 does not alter accepted queue/save path. Does not run operation synchronously or mutate terrain directly.
char __cdecl rf_geomod_operation_admit(float a1, int a2, int a3, float *world_position, float *source, int a6, char a7)
{
  int v8; // eax
  int v9; // eax
  float v10[3]; // [esp+10h] [ebp-E0h] BYREF
  float v11[3]; // [esp+1Ch] [ebp-D4h] BYREF
  float v12[3]; // [esp+28h] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-BCh] BYREF
  int v14; // [esp+40h] [ebp-B0h]
  int v15; // [esp+44h] [ebp-ACh]
  float v16; // [esp+48h] [ebp-A8h]
  int v17; // [esp+4Ch] [ebp-A4h]
  int room; // [esp+50h] [ebp-A0h]
  float v19[4]; // [esp+54h] [ebp-9Ch] BYREF
  float v20[3]; // [esp+64h] [ebp-8Ch] BYREF
  __int16 *v21; // [esp+70h] [ebp-80h]
  int operation; // [esp+78h] [ebp-78h] BYREF
  int v24; // [esp+7Ch] [ebp-74h]
  float v25[3]; // [esp+80h] [ebp-70h] BYREF
  float v26[9]; // [esp+8Ch] [ebp-64h] BYREF
  int v27; // [esp+B0h] [ebp-40h]
  float v28; // [esp+B4h] [ebp-3Ch]
  float destination[3]; // [esp+B8h] [ebp-38h] BYREF
  float v30[3]; // [esp+C4h] [ebp-2Ch] BYREF
  float v31[5]; // [esp+D0h] [ebp-20h] BYREF
  int i; // [esp+E4h] [ebp-Ch]
  int v33; // [esp+E8h] [ebp-8h]
  int v34; // [esp+ECh] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1 )
    goto LABEL_11;
  if ( !*(_DWORD *)unk_704EEC )
    return 0;
  if ( !unk_6FCCF9 && rf_geomod_network_history_count_get() >= *(int *)unk_704EEC )
    return 0;
LABEL_11:
  if ( !a3 )
    return 0;
  v34 = rf_geomod_cutter_resolve(a6);
  if ( !v34 )
    return 0;
  if ( a1 < 1.0 )
    return 0;
  rf_geomod_operation_init((char *)&operation);
  operation = a6;
  rf_vector_copy(destination, copy_result, source);
  v24 = *(_DWORD *)(a3 + 32);
  v27 = 0;
  v28 = 1.0;
  if ( (a7 & 8) == 0 )
    v28 = a1 / *(float *)(v34 + 96);
  if ( !rf_geomod_georegions_apply(world_position, &operation, 1u) )
    return 0;
  if ( (a7 & 8) != 0 )
    v28 = 1.0;
  v33 = rf_object_resolve_handle(a2);
  if ( (a7 & 4) != 0 )
  {
    if ( v33 )
      rf_matrix3_copy(v26, (const float *)(v33 + 72));
    else
      rf_identity_orientation_matrix(v26);
  }
  else
  {
    rf_random_orientation_matrix(v26);
  }
  if ( (a7 & 1) != 0 || unk_6FCCFA )
    v27 |= 1u;
  if ( (a7 & 0x10) != 0 || unk_6FCCFA )
    v27 |= 4u;
  if ( (a7 & 0x20) != 0 )
  {
    v27 |= 8u;
    rf_vector3_zero_return_destination(v30);
    rf_vector3_zero_return_destination(v31);
  }
  for ( i = 0; i < rf_geomod_save_record_count; ++i )
  {
    v21 = &rf_geomod_save_records[16 * i];
    if ( (unsigned __int16)*v21 == operation && *((_DWORD *)v21 + 1) == v24 )
    {
      rf_vector3_default_construct_noop(v20);
      rf_geomod_saved_position_decode_u16((const float *)rf_world_solid, (const unsigned __int16 *)v21 + 4, v20);
      if ( rf_vector_distance_squared(v20, world_position) <= 0.04000000283122063 )
        return 0;
    }
  }
  if ( rf_geomod_save_record_count < 128 )
  {
    rf_geomod_execution_queue_append((int)&operation);
    rf_geomod_save_records[16 * rf_geomod_save_record_count] = operation;
    unk_6FCD04[8 * rf_geomod_save_record_count] = v24;
    rf_geomod_saved_position_encode_u16(
      (const float *)rf_world_solid,
      world_position,
      (unsigned __int16 *)&unk_6FCD08 + 16 * rf_geomod_save_record_count);
    rf_quaternion_set_from_matrix3_normalized_legacy(v19, v26);
    rf_snapshot_pack_quaternion_s16_times16383((_WORD *)&unk_6FCD14 + 16 * rf_geomod_save_record_count, v19);
    unk_6FCD02[16 * rf_geomod_save_record_count] = v27 | 1;
    unk_6FCD1C[8 * rf_geomod_save_record_count] = v28;
    rf_snapshot_pack_normalized_vector_s16(destination, (_WORD *)&unk_6FCD0E + 16 * rf_geomod_save_record_count);
    rf_vector_copy((float *)&unk_6FDD50 + 9 * rf_geomod_save_record_count, v12, v25);
    rf_vector_copy((float *)&unk_6FDD5C + 9 * rf_geomod_save_record_count, v11, v30);
    rf_vector_copy(&flt_6FDD68[9 * rf_geomod_save_record_count], v10, v31);
    ++rf_geomod_save_record_count;
  }
  if ( byte_704E83 != 1 )
  {
    if ( (a7 & 1) == 0 && !unk_6FCCFA )
    {
      v16 = v28 * *(float *)(v34 + 96);
      v17 = unk_6FC338;
      if ( (v27 & 0x10) != 0 )
        v17 = rf_bitmap_load_with_optional_mipmap_generation("ice_ice01.tga", (void *)0xFFFFFFFF, 1);
      rf_geomod_impact_fragment_spawn((int)v25, v16, (int)source, v17, a3);
    }
    room = rf_camera_slot_get_room(*(void ***)(rf_local_fpgun_player + 196));
    if ( room && rf_liquid_room_contains_point(room, (int)world_position) )
    {
      v8 = rand();
      rf_gamesound_play_positional_event(v8 % 3 + 22, world_position, 1.0, (int)&unk_17F10B0, 0);
    }
    else if ( (v27 & 0x10) != 0 )
    {
      v9 = rand();
      rf_gamesound_play_positional_event(v9 % 3 + 25, world_position, 1.0, (int)&unk_17F10B0, 0);
    }
    else
    {
      v14 = -1;
      v15 = rf_projectile_resolve_uid_type2(a2);
      if ( v15 )
        v14 = rf_weapon_choose_geomod_sound(*(_DWORD *)(v15 + 664));
      if ( v14 == -1 )
        v14 = rand() % 3 + 6;
      rf_gamesound_play_positional_event(v14, world_position, 1.0, (int)&unk_17F10B0, 0);
    }
  }
  return 1;
}

