// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BB670 rf_entity_find_best_use_candidate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): Cdecl(required source entity,required node-output pointer when entity candidate wins); returns selected common-object pointer in EAX,
// initializedNULL. Reference point is source+2004 and direction source+2040. Best float score starts FLT_MAX. Uses fast vector length, unchecked normalization, float32-rounded
// distance/dot score, ordered STRICT comparisons; equal scores retain earlier candidate. Pass1 entity list next+652: excludes dead predicate, inactive predicate, class use
// index(+660)->+436==0 and source itself. Index9 uses common position+60, raw distance<class range+440 and best; sets node output=-1 WITHOUT facing/occlusion test. Other indices
// iterate pointer array+2252, dereference each node record DWORD0, obtain node transform(model+128,node), ignore adapter result, rotate local point by entity matrix+72, add entity
// position+60 minus source reference. Require raw distance<range and dot(normalized offset,source direction)>0, then score=distance/dot<best. Only class use1/4 additionally reject
// geometry obstruction(source reference,ENTITY COMMON position+60,public mask1,NULL)==EXACT AL1; this is not a node-position visibility ray. Entity win writes actual node DWORD0.
// Pass2 intrusive list6807E4 entries with DWORD+8==0 resolve clutter UID+12, reject pending-delete common bit2; require distance<class range+72, dot>0, score<best; no node-output
// write. Pass3 corpses only when splitscreen BYTE==0, model+128 nonnull: node/common world-position helper with common-position fallback on AL0, distance<DOUBLE2.5, dot>DOUBLE0.85,
// score<best. Pass4 triggers with flags+688 bit1 and eligibility(trigger,source,1) nonzero AL: raw distance<best, dot>0, score<best; no independent distance cap. Pass5 projectile
// type DWORD+664==global911C78 and physics-state predicate(object+136) AL!=EXACT1: raw distance<best AND<DOUBLE2, dot>DOUBLE0.7, score<best. Final TWO separate complete clutter-list
// passes use identical rules: class use-sound DWORD+84!=-1 and voice query(object+720)==EAX0, raw distance<best and<class range+72, dot>DOUBLE0.7, score<best. Neither final pass
// tests common delete/inactive bits or runs occlusion. Preserve duplicate passes and repeated voice queries. All nonentity wins update best/pointer only: node output retains last
// winning entity value, or caller prior/uninitialized value if no entity ever won. No global output initialization, general team/health/multiplayer gate, global occlusion filter, dot
// clamp, zero-length guard, or descriptor/model fallback. Live lists advance after helper calls. Native callers4DAA7E and4DB014 each pass two stack arguments and consume EAX as
// object pointer.
float *__cdecl rf_entity_find_best_use_candidate(_DWORD *a1, _DWORD *a2)
{
  float *v2; // eax
  int first_dword; // eax
  int **v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  _BYTE v20[12]; // [esp+0h] [ebp-180h] BYREF
  float v21[3]; // [esp+Ch] [ebp-174h] BYREF
  float v22[3]; // [esp+18h] [ebp-168h] BYREF
  _BYTE v23[12]; // [esp+24h] [ebp-15Ch] BYREF
  float v24[3]; // [esp+30h] [ebp-150h] BYREF
  float v25[3]; // [esp+3Ch] [ebp-144h] BYREF
  _BYTE v26[12]; // [esp+48h] [ebp-138h] BYREF
  float v27[3]; // [esp+54h] [ebp-12Ch] BYREF
  float v28[3]; // [esp+60h] [ebp-120h] BYREF
  _BYTE v29[12]; // [esp+6Ch] [ebp-114h] BYREF
  float v30[3]; // [esp+78h] [ebp-108h] BYREF
  float v31[3]; // [esp+84h] [ebp-FCh] BYREF
  _BYTE v32[12]; // [esp+90h] [ebp-F0h] BYREF
  float v33[3]; // [esp+9Ch] [ebp-E4h] BYREF
  float v34[3]; // [esp+A8h] [ebp-D8h] BYREF
  float v35[3]; // [esp+B4h] [ebp-CCh] BYREF
  _BYTE v36[12]; // [esp+C0h] [ebp-C0h] BYREF
  float v37[3]; // [esp+CCh] [ebp-B4h] BYREF
  float v38[3]; // [esp+D8h] [ebp-A8h] BYREF
  _BYTE v39[12]; // [esp+E4h] [ebp-9Ch] BYREF
  float v40[3]; // [esp+F0h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+FCh] [ebp-84h] BYREF
  float out_vector[3]; // [esp+108h] [ebp-78h] BYREF
  float lhs[3]; // [esp+114h] [ebp-6Ch] BYREF
  int m; // [esp+120h] [ebp-60h]
  char v45; // [esp+127h] [ebp-59h]
  char v46[36]; // [esp+128h] [ebp-58h] BYREF
  int j; // [esp+14Ch] [ebp-34h]
  float *n; // [esp+150h] [ebp-30h]
  int i; // [esp+154h] [ebp-2Ch]
  float v50; // [esp+158h] [ebp-28h]
  float v51; // [esp+15Ch] [ebp-24h]
  int ii; // [esp+160h] [ebp-20h]
  _DWORD *k; // [esp+164h] [ebp-1Ch]
  float *v54; // [esp+168h] [ebp-18h]
  float destination[3]; // [esp+16Ch] [ebp-14h] BYREF
  int jj; // [esp+178h] [ebp-8h]
  float v57; // [esp+17Ch] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  v50 = 3.4028235e38;
  v54 = nullptr;
  for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( !rf_entity_is_dead(i)
      && !rf_object_has_respawn_inactive_flag(i)
      && *(_DWORD *)(*(_DWORD *)(i + 660) + 436)
      && (_DWORD *)i != a1 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(i + 660) + 436) == 9 )
      {
        v2 = rf_vector_subtract((const float *)(i + 60), out_vector, (const float *)a1 + 501);
        rf_vector_copy(destination, copy_result, v2);
        v51 = rf_vector_fast_length(destination);
        if ( *(float *)(*(_DWORD *)(i + 660) + 440) > (double)v51 && v50 > (double)v51 )
        {
          v50 = v51;
          *a2 = -1;
          v54 = (float *)i;
        }
      }
      else
      {
        for ( j = 0; ; ++j )
        {
          first_dword = rf_receiver_get_first_dword((void *)(i + 2252));
          if ( j >= first_dword )
            break;
          rf_matrix3_construct(v46);
          v4 = (int **)sub_552200((_DWORD *)(i + 2252), j);
          rf_model_handle_get_node_transform_adapter(*(_DWORD *)(i + 128), (int)destination, (int)v46, **v4);
          rf_vector_rotate_by_matrix3(destination, (float *)(i + 72));
          v5 = rf_vector_subtract((const float *)(i + 60), v40, (const float *)a1 + 501);
          rf_vector_accumulate(destination, v5);
          v51 = rf_vector_fast_length(destination);
          if ( *(float *)(*(_DWORD *)(i + 660) + 440) > (double)v51 )
          {
            v6 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v39);
            v57 = rf_vector_dot(v6, (float *)a1 + 510);
            if ( v57 > 0.0 )
            {
              v51 = v51 / v57;
              if ( v50 > (double)v51 )
              {
                v45 = 1;
                if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 436) == 1 || *(_DWORD *)(*(_DWORD *)(i + 660) + 436) == 4)
                  && rf_geometry_segment_is_obstructed((int)(a1 + 501), i + 60, 1, 0) == 1 )
                {
                  v45 = 0;
                }
                if ( v45 )
                {
                  v50 = v51;
                  *a2 = **(_DWORD **)sub_552200((_DWORD *)(i + 2252), j);
                  v54 = (float *)i;
                }
              }
            }
          }
        }
      }
    }
  }
  for ( k = (_DWORD *)dword_6807E4; k != &dword_6807E4; k = (_DWORD *)*k )
  {
    if ( !k[2] )
    {
      jj = rf_clutter_find_by_uid(k[3]);
      if ( jj )
      {
        if ( (*(_DWORD *)(jj + 124) & 2) == 0 )
        {
          v7 = rf_vector_subtract((const float *)(jj + 60), v38, (const float *)a1 + 501);
          rf_vector_copy(destination, v37, v7);
          v51 = rf_vector_fast_length(destination);
          if ( *(float *)(*(_DWORD *)(jj + 660) + 72) > (double)v51 )
          {
            v8 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v36);
            v57 = rf_vector_dot(v8, (float *)a1 + 510);
            if ( v57 > 0.0 )
            {
              v51 = v51 / v57;
              if ( v50 > (double)v51 )
              {
                v50 = v51;
                v54 = (float *)jj;
              }
            }
          }
        }
      }
    }
  }
  if ( !rf_splitscreen_runtime_active )
  {
    rf_vector3_default_construct_noop(lhs);
    for ( m = rf_corpse_list_head; (_UNKNOWN *)m != &unk_681AF8; m = *(_DWORD *)(m + 652) )
    {
      if ( *(_DWORD *)(m + 128) )
      {
        if ( !rf_object_copy_node_or_common_world_position(m, (int)lhs) )
          rf_vector_copy(lhs, v35, (const float *)(m + 60));
        v9 = rf_vector_subtract(lhs, v34, (const float *)a1 + 501);
        rf_vector_copy(destination, v33, v9);
        v51 = rf_vector_fast_length(destination);
        if ( v51 < 2.5 )
        {
          v10 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v32);
          v57 = rf_vector_dot(v10, (float *)a1 + 510);
          if ( v57 > 0.85 )
          {
            v51 = v51 / v57;
            if ( v50 > (double)v51 )
            {
              v50 = v51;
              v54 = (float *)m;
            }
          }
        }
      }
    }
  }
  for ( n = (float *)rf_trigger_runtime_list_head; n != (float *)&unk_90B510; n = *((float **)n + 163) )
  {
    if ( ((_DWORD)n[172] & 1) != 0 && rf_trigger_activation_eligible((int *)n, a1, 1) )
    {
      v11 = rf_vector_subtract(n + 15, v31, (const float *)a1 + 501);
      rf_vector_copy(destination, v30, v11);
      v51 = rf_vector_fast_length(destination);
      if ( v50 > (double)v51 )
      {
        v12 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v29);
        v57 = rf_vector_dot(v12, (float *)a1 + 510);
        if ( v57 > 0.0 )
        {
          v51 = v51 / v57;
          if ( v50 > (double)v51 )
          {
            v50 = v51;
            v54 = n;
          }
        }
      }
    }
  }
  for ( ii = dword_911F74; (_UNKNOWN *)ii != &unk_911CE8; ii = *(_DWORD *)(ii + 652) )
  {
    if ( *(_DWORD *)(ii + 664) == dword_911C78 && !rf_physics_state_test_enabled_al(ii + 136) )
    {
      v13 = rf_vector_subtract((const float *)(ii + 60), v28, (const float *)a1 + 501);
      rf_vector_copy(destination, v27, v13);
      v51 = rf_vector_fast_length(destination);
      if ( v50 > (double)v51 && v51 < 2.0 )
      {
        v14 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v26);
        v57 = rf_vector_dot(v14, (float *)a1 + 510);
        if ( v57 > 0.7 )
        {
          v51 = v51 / v57;
          if ( v50 > (double)v51 )
          {
            v50 = v51;
            v54 = (float *)ii;
          }
        }
      }
    }
  }
  for ( jj = rf_clutter_list_head; (_UNKNOWN *)jj != &unk_666D18; jj = *(_DWORD *)(jj + 652) )
  {
    if ( *(_DWORD *)(*(_DWORD *)(jj + 660) + 84) != -1 && !rf_gamesound_voice_is_playing(*(_DWORD *)(jj + 720)) )
    {
      v15 = rf_vector_subtract((const float *)(jj + 60), v25, (const float *)a1 + 501);
      rf_vector_copy(destination, v24, v15);
      v51 = rf_vector_fast_length(destination);
      if ( v50 > (double)v51 && *(float *)(*(_DWORD *)(jj + 660) + 72) > (double)v51 )
      {
        v16 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v23);
        v57 = rf_vector_dot(v16, (float *)a1 + 510);
        if ( v57 > 0.7 )
        {
          v51 = v51 / v57;
          if ( v50 > (double)v51 )
          {
            v50 = v51;
            v54 = (float *)jj;
          }
        }
      }
    }
  }
  for ( jj = rf_clutter_list_head; (_UNKNOWN *)jj != &unk_666D18; jj = *(_DWORD *)(jj + 652) )
  {
    if ( *(_DWORD *)(*(_DWORD *)(jj + 660) + 84) != -1 && !rf_gamesound_voice_is_playing(*(_DWORD *)(jj + 720)) )
    {
      v17 = rf_vector_subtract((const float *)(jj + 60), v22, (const float *)a1 + 501);
      rf_vector_copy(destination, v21, v17);
      v51 = rf_vector_fast_length(destination);
      if ( v50 > (double)v51 && *(float *)(*(_DWORD *)(jj + 660) + 72) > (double)v51 )
      {
        v18 = (float *)rf_vector3_normalized_copy_unchecked(destination, (int)v20);
        v57 = rf_vector_dot(v18, (float *)a1 + 510);
        if ( v57 > 0.7 )
        {
          v51 = v51 / v57;
          if ( v50 > (double)v51 )
          {
            v50 = v51;
            v54 = (float *)jj;
          }
        }
      }
    }
  }
  return v54;
}

