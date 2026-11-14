// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B82E0 rf_object_allocate_by_type
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl(type,eventSubtype), returns common pointer orNULL. Unsigned type0..10 jump table verified against original PE. Type0 operator-new0x1494 then entity ctor412740; type1 item pool0x2C4 only when signed pool in-use<200; type2 projectile pool0x314 only below50; type3 debris pool0x2B4 only below50; type4 heap0x2D8 plus clutter ctor; type5 heap0x30C plus trigger ctor4BDB50; type6 event factory(eventSubtype) then returns event+4 when nonnull; type7 corpse pool0x318 only below30; type8 heap0x32C plus48BEB0; type9 heap0x298 plus48BF80; type10 heap0x2EC plus glare ctor. Unsupported type/failed allocation returnsNULL before common-list publication. POOLED branches invoke no member constructor here;
// heap-spill permission does not bypass these factory in-use caps. Success zeros fields636 and616, calls room/cache setter(roomNULL), which copies CURRENT preexisting common position60 into cached4, then increments global object count7B4DF8 with signed high-water7B8E10 update and tail-links common NEXT16/PREV20 into sentinel7D0C80. Does not assign final type/UID/handle/pose/health,zero whole object, validate event subtype, or roll back pool delegate side effects if it returnedNULL. Those common initialization stages belong to4B7E00.
float *__cdecl rf_object_allocate_by_type(int a1, int a2)
{
  char *v3; // [esp+4h] [ebp-64h]
  char *v4; // [esp+8h] [ebp-60h]
  char *v5; // [esp+Ch] [ebp-5Ch]
  char *v6; // [esp+10h] [ebp-58h]
  char *v7; // [esp+14h] [ebp-54h]
  char *v8; // [esp+18h] [ebp-50h]
  char *v9; // [esp+1Ch] [ebp-4Ch]
  char *v10; // [esp+20h] [ebp-48h]
  char *v11; // [esp+28h] [ebp-40h]
  char *v12; // [esp+30h] [ebp-38h]
  char *v13; // [esp+38h] [ebp-30h]
  char *v14; // [esp+40h] [ebp-28h]
  char *v15; // [esp+48h] [ebp-20h]
  char *v16; // [esp+50h] [ebp-18h]
  float *v17; // [esp+58h] [ebp-10h]

  v17 = nullptr;
  switch ( a1 )
  {
    case 0:
      v15 = (char *)operator new(0x1494u);
      if ( v15 )
        v9 = rf_entity_construct_members(v15);
      else
        v9 = nullptr;
      v17 = (float *)v9;
      break;
    case 1:
      if ( unk_7F3BC8 < 200 )
        v17 = (float *)rf_item_pool_allocate(dword_7D1290);
      break;
    case 2:
      if ( unk_7C8530 < 50 )
        v17 = (float *)rf_projectile_pool_allocate(dword_7BEB30);
      break;
    case 3:
      if ( rf_physical_debris_pool_in_use_count < 50 )
        v17 = (float *)rf_physical_debris_pool_allocate(rf_physical_debris_object_pool);
      break;
    case 4:
      v16 = (char *)operator new(0x2D8u);
      if ( v16 )
        v10 = rf_clutter_runtime_construct_members(v16);
      else
        v10 = nullptr;
      v17 = (float *)v10;
      break;
    case 5:
      v12 = (char *)operator new(0x30Cu);
      if ( v12 )
        v4 = rf_trigger_runtime_construct_members(v12);
      else
        v4 = nullptr;
      v17 = (float *)v4;
      break;
    case 6:
      v8 = rf_mission_event_create_by_type(a2);
      if ( v8 )
        v7 = v8 + 4;
      else
        v7 = nullptr;
      v17 = (float *)v7;
      break;
    case 7:
      if ( unk_7BEB08 < 30 )
        v17 = (float *)rf_corpse_pool_allocate(dword_7B8E20);
      break;
    case 8:
      v14 = (char *)operator new(0x32Cu);
      if ( v14 )
        v6 = rf_mover_construct_members(v14);
      else
        v6 = nullptr;
      v17 = (float *)v6;
      break;
    case 9:
      v13 = (char *)operator new(0x298u);
      if ( v13 )
        v5 = rf_moving_solid_construct_members(v13);
      else
        v5 = nullptr;
      v17 = (float *)v5;
      break;
    case 10:
      v11 = (char *)operator new(0x2ECu);
      if ( v11 )
        v3 = rf_glare_runtime_construct_common_and_vector_members(v11);
      else
        v3 = nullptr;
      v17 = (float *)v3;
      break;
    default:
      break;
  }
  if ( !v17 )
    return nullptr;
  v17[159] = 0.0;
  v17[154] = 0.0;
  rf_object_set_room_and_cache_position(v17, 0);
  if ( ++dword_7B4DF8 > dword_7B8E10 )
    dword_7B8E10 = dword_7B4DF8;
  *((_DWORD *)v17 + 5) = unk_7D0C94;
  *((_DWORD *)v17 + 4) = &unk_7D0C80;
  *(_DWORD *)(unk_7D0C94 + 16) = v17;
  unk_7D0C94 = v17;
  return v17;
}

