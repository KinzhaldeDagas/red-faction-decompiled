// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557D00 rf_world_assign_face_runtime_room_portal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): ECX world plus face,roomA,roomB. Scans roomA portal array48 for first portal whose room0 OR room4 equals roomB, without independently checking other endpoint. If absent allocates56-byte registered portal557C80 and initializes bounds from face16/28. Encodes portal index into metadata WORD Face52 via557F00, sets bitmap48=-1 and lightmap WORD54=-1, then expands portal bounds with face bounds. Does not set Face68 owner or room attachment; no allocation-null or finalize checks.
void __thiscall rf_world_assign_face_runtime_room_portal(void *this, int a2, int a3, int a4)
{
  float *v4; // [esp+4h] [ebp-3Ch]
  float v6[3]; // [esp+Ch] [ebp-34h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-28h] BYREF
  void *v8; // [esp+24h] [ebp-1Ch]
  float *v9; // [esp+28h] [ebp-18h]
  int i; // [esp+2Ch] [ebp-14h]
  float *v11; // [esp+30h] [ebp-10h]
  int v12; // [esp+3Ch] [ebp-4h]

  v11 = nullptr;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a3 + 48)); ++i )
  {
    if ( **(_DWORD **)sub_552200((_DWORD *)(a3 + 48), i) == a4
      || *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a3 + 48), i) + 4) == a4 )
    {
      v11 = *(float **)sub_552200((_DWORD *)(a3 + 48), i);
      break;
    }
  }
  if ( !v11 )
  {
    v8 = operator new(0x38u);
    v12 = 0;
    if ( v8 )
      v4 = (float *)rf_runtime_portal_construct_register(v8, (int)this, a3, a4);
    else
      v4 = nullptr;
    v9 = v4;
    v12 = -1;
    v11 = v4;
    rf_vector_copy(v4 + 2, copy_result, (const float *)(a2 + 16));
    rf_vector_copy(v11 + 5, v6, (const float *)(a2 + 28));
  }
  rf_face_metadata_set_portal_index_plus_two((_WORD *)(a2 + 40), *((_DWORD *)v11 + 8));
  *(_DWORD *)(a2 + 48) = -1;
  *(_WORD *)(a2 + 54) = -1;
  rf_aabb_union_componentwise_in_place(v11 + 2, v11 + 5, (const float *)(a2 + 16), (const float *)(a2 + 28));
}

