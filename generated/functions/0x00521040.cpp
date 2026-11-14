// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521040 rf_world_render_room_liquid_and_effect_pass
// UNREALRED VERIFIED [decal-face-links-20261028]: Calls0x51F710(flag,room,0), checks room bounds through0x581EB0(room+8,room+20); result==1 skips remaining pass. If room byte+388 nonzero scans room face list+40, collects liquid faces passing0x581910 into global0xA604F8 with no local capacity check. Face flag0x400 marks procedural bitmap handle+48 used. Packs face+44=bitmap<<16 | lightmap nested value+20 (or0 for negative lightmap index). Adds collected count to0xA42058, updates marked procedural bitmaps only when count>0. Renders0x4C46B0(room), glass-shard room bucket,0x51F910(room,solid,count,array), then0x51EDD0. Returns final helper value; not rendered-face count.
char __cdecl rf_world_render_room_liquid_and_effect_pass(int a1, int a2, char a3)
{
  int v3; // eax
  int v5; // [esp+0h] [ebp-18h]
  int v6; // [esp+4h] [ebp-14h]
  int v7; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  int v9; // [esp+10h] [ebp-8h]

  rf_world_submit_room_effect_callbacks(a3, a2, 0);
  v9 = 0;
  v3 = rf_frustum_classify_aabb(a2 + 8, a2 + 20);
  if ( v3 != 1 )
  {
    if ( *(_BYTE *)(a2 + 388) )
    {
      for ( i = rf_receiver_get_first_dword((void *)(a2 + 40)); i; i = rf_face_next_room_link(i) )
      {
        if ( rf_face_is_liquid((_DWORD *)(i + 40)) && rf_renderer_face_passes_view_test(i) )
        {
          unk_A604F8[v9++] = i;
          if ( (*(_DWORD *)(i + 40) & 0x400) != 0 )
            rf_procedural_bitmap_mark_used_by_handle(*(_DWORD *)(i + 48));
          v5 = *(_DWORD *)(i + 48);
          v6 = *(__int16 *)(i + 54);
          if ( v6 >= 0 )
            v7 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 192), v6) + 12) + 20);
          else
            v7 = 0;
          *(_DWORD *)(i + 44) = v7 | (v5 << 16);
        }
      }
    }
    *(_DWORD *)&byte_98967F[756185] += v9;
    if ( v9 > 0 )
      rf_procedural_bitmap_update_marked_records();
    rf_geomod_impact_chunks_render_for_room(a2);
    rf_glass_shard_bucket_render((_DWORD *)a2);
    rf_world_draw_sorted_callbacks_around_liquid((_BYTE *)a2, a1, v9, (int)unk_A604F8);
    LOBYTE(v3) = rf_world_flush_see_through_face_batch();
  }
  return v3;
}

