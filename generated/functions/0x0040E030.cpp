// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040E030 rf_ai_route_build
// UNREALRED VERIFIED [ai-script-animation-release-20261013] After resolving the owner entity, calls 0x40BCF0 BEFORE any route construction or admission return, including failed routes. Thus route attempts clear the custom-loop request and conditionally clear tracked action records independently of route success; scheduler bit 8 remains owned elsewhere.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Directed request uses same embedded route as panic. Resolveentity and clear scripted context BEFORE endpoint stores/admission. Preserve40DE20 request setup,40FD80 target fit,4098B0 range budget versus fitted/original endpoint distance,40E5B0 direct test then518BE0. Mode10 uses stopRadius0 in graph search; no random endpoint substitution or UE path fallback.
char __cdecl rf_ai_route_build(int a1, float *source)
{
  double v3; // st7
  float *v4; // eax
  float *v5; // eax
  double v6; // st7
  float scalar; // [esp+18h] [ebp-BCh]
  float v8[3]; // [esp+1Ch] [ebp-B8h] BYREF
  float v9[3]; // [esp+28h] [ebp-ACh] BYREF
  float v10[3]; // [esp+34h] [ebp-A0h] BYREF
  float sum_result[3]; // [esp+40h] [ebp-94h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-88h] BYREF
  float v13[3]; // [esp+58h] [ebp-7Ch] BYREF
  float v14[3]; // [esp+64h] [ebp-70h] BYREF
  float v15[3]; // [esp+70h] [ebp-64h] BYREF
  float v16[3]; // [esp+7Ch] [ebp-58h] BYREF
  float copy_result[3]; // [esp+88h] [ebp-4Ch] BYREF
  float out_vector[3]; // [esp+94h] [ebp-40h] BYREF
  float v19; // [esp+A0h] [ebp-34h]
  float v20; // [esp+A4h] [ebp-30h]
  float v21; // [esp+A8h] [ebp-2Ch]
  float v22; // [esp+ACh] [ebp-28h]
  float closest_point[3]; // [esp+B0h] [ebp-24h] BYREF
  float v24; // [esp+BCh] [ebp-18h]
  float *v25; // [esp+C0h] [ebp-14h]
  float v26; // [esp+C4h] [ebp-10h]
  float *v27; // [esp+C8h] [ebp-Ch]
  char v28; // [esp+CFh] [ebp-5h]
  int v29; // [esp+D0h] [ebp-4h]

  v27 = (float *)rf_entity_resolve_handle(a1);
  if ( !v27 )
    return 0;
  rf_ai_clear_scripted_animation_context((int *)v27 + 168);
  v25 = v27 + 354;
  rf_vector_copy(v27 + 392, copy_result, source);
  rf_vector_copy(v25 + 41, v16, source);
  unk_666408 = v25 + 38;
  if ( *((_DWORD *)v27 + 328) == 3 && *((_DWORD *)v27 + 341) == 3 )
  {
    *(_DWORD *)v25 = 2;
    *((_DWORD *)v25 + 1) = v25 + 7;
    *((_DWORD *)v25 + 2) = v25 + 38;
    rf_vector_copy(v25 + 7, v15, v27 + 15);
    rf_vector_copy(v25 + 10, v14, v27 + 15);
    v25[5] = 0.0;
    *((_DWORD *)v25 + 6) = 1;
    rf_replicator_arm_milliseconds((int *)v25 + 77, 0);
    rf_vector_copy(v25 + 83, v13, v27 + 15);
    return 1;
  }
  else
  {
    rf_ai_publish_owner_route_search_request(v27);
    *(_DWORD *)(unk_666408 + 64) = unk_66641C != 1;
    v26 = rf_ai_resolve_maximum_attack_range((int *)v27 + 168);
    v28 = sub_40FD80((int)source, v27[496], v27[497], unk_66641C, &dword_66640C, &dword_666410, 0);
    if ( unk_66641C == 1 )
    {
      if ( v28 == 1 )
      {
        if ( dword_66640C && dword_666410 )
        {
          v24 = rf_vector_distance((const float *)(dword_66640C + 12), (const float *)(dword_666410 + 12));
          if ( v24 > 0.0 )
          {
            v22 = *(float *)(dword_66640C + 16) - *(float *)(dword_66640C + 32) * 0.5;
            v20 = *(float *)(dword_666410 + 16) - *(float *)(dword_666410 + 32) * 0.5;
            rf_vector3_default_construct_noop(closest_point);
            v3 = rf_vector3_closest_point_on_segment(
                   v27 + 15,
                   (const float *)(dword_66640C + 12),
                   (const float *)(dword_666410 + 12),
                   closest_point);
            v21 = v3 / v24;
            v25[42] = v21 * v22 + (1.0 - v21) * v20 + unk_666418;
          }
        }
        else if ( dword_66640C )
        {
          v19 = *(float *)(dword_66640C + 4) - *(float *)(dword_66640C + 32) * 0.5;
          v25[42] = v19 + unk_666418;
        }
      }
      else if ( dword_66640C )
      {
        rf_vector_subtract(v25 + 38, out_vector, (const float *)(dword_66640C + 12));
        out_vector[1] = 0.0;
        rf_vector_normalize_reciprocal_sqrt(out_vector);
        scalar = *(float *)(dword_66640C + 28) - v27[496];
        v4 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
        v5 = rf_vector_add((const float *)(dword_66640C + 12), sum_result, v4);
        rf_vector_copy(v25 + 41, v10, v5);
      }
    }
    if ( *((_DWORD *)v27 + 328) == 2
      || *((_DWORD *)v27 + 328) == 16
      || (v6 = rf_vector_distance(v25 + 41, v25 + 38), v26 >= v6) )
    {
      rf_pointer_array_clear_count_keep_storage((_DWORD *)v25 + 48);
      if ( dword_66640C )
        rf_pointer_array_append_dword((_DWORD *)v25 + 48, dword_66640C);
      if ( dword_666410 )
        rf_pointer_array_append_dword((_DWORD *)v25 + 48, dword_666410);
      v29 = 0;
      if ( *((_DWORD *)v27 + 328) == 3 )
        v29 = rf_entity_resolve_handle(*((_DWORD *)v27 + 344));
      if ( rf_ai_choose_shared_route_node_or_edge_endpoints((int)(v25 + 10), (int)v27, (int)(v25 + 38), v29) == 1 )
      {
        *(_DWORD *)v25 = 2;
        *((_DWORD *)v25 + 1) = v25 + 7;
        *((_DWORD *)v25 + 2) = v25 + 38;
        v25[5] = 0.0;
        *((_DWORD *)v25 + 6) = 1;
        rf_replicator_arm_milliseconds((int *)v25 + 77, 0);
        rf_vector_copy(v25 + 83, v9, v27 + 501);
        return 1;
      }
      else
      {
        unk_66641E = 1;
        if ( *((_DWORD *)v27 + 328) == 3 )
          unk_666424 = rf_ai_resolve_maximum_attack_range((int *)v27 + 168);
        else
          unk_666424 = 0.0;
        if ( rf_nav_graph_find_path_to_request_target((void *)(rf_world_solid + 768), &dword_6663FC) )
        {
          *(_DWORD *)v25 = unk_666430;
          if ( *(int *)v25 < 2 )
          {
            return 0;
          }
          else
          {
            v25[5] = 0.0;
            *((_DWORD *)v25 + 6) = 1;
            rf_replicator_arm_milliseconds((int *)v25 + 77, 0);
            rf_vector_copy(v25 + 83, v8, v27 + 501);
            return 1;
          }
        }
        else
        {
          return 0;
        }
      }
    }
    else
    {
      return 0;
    }
  }
}

