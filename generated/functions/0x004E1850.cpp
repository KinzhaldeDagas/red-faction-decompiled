// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1850 rf_player_rebuild_forward_point_light
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): NULL player no-op. Release existing light handle+224 with argument0 and set -1 BEFORE resolving own entity UID+20 or checking eligibility. Build only with entity and (global byte87C63E nonzero OR entity runtime DWORD2064 mask0x4000). Desired target=entity point+2004 + forward+2040 * globalF32662E3C. Sweep from point to target: zero radius, request flags4 direct-world, world query final argument1 resets best fraction. If hit, target=hitpoint-forward*0.5. Then flags0; traverse mover ring704BCC/sentinel704940 via next+652, populate transform position60/matrix72 and query mover world pointer660 with final argument0. These calls preserve prior best fraction; accepted mover hits replace target after transform to world, constrained by
// nearest/equal accumulated bound, not unconstrained last-hit. Original sweep endpoints remain unchanged across movers. Create point light(target,range662E44,RGB scalar662E38,R=G=B=1,category1,opaque1,attenuation0), store returned handle+224. No handle reuse, view-target lookup, own alive test or finite/zero-direction checks.
void __cdecl rf_player_rebuild_forward_point_light(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v7[3]; // [esp+20h] [ebp-140h] BYREF
  float v8[3]; // [esp+2Ch] [ebp-134h] BYREF
  float v9[3]; // [esp+38h] [ebp-128h] BYREF
  float v10[3]; // [esp+44h] [ebp-11Ch] BYREF
  float v11[3]; // [esp+50h] [ebp-110h] BYREF
  float v12[3]; // [esp+5Ch] [ebp-104h] BYREF
  float v13[3]; // [esp+68h] [ebp-F8h] BYREF
  float v14[3]; // [esp+74h] [ebp-ECh] BYREF
  float out_vector[3]; // [esp+80h] [ebp-E0h] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+98h] [ebp-C8h] BYREF
  float v18[3]; // [esp+A4h] [ebp-BCh] BYREF
  _DWORD v19[2]; // [esp+B0h] [ebp-B0h] BYREF
  float v20[8]; // [esp+B8h] [ebp-A8h] BYREF
  char v21[4]; // [esp+D8h] [ebp-88h] BYREF
  float v22[3]; // [esp+DCh] [ebp-84h] BYREF
  float v23[9]; // [esp+E8h] [ebp-78h] BYREF
  float rhs[3]; // [esp+10Ch] [ebp-54h] BYREF
  float destination[4]; // [esp+118h] [ebp-48h] BYREF
  int v26; // [esp+128h] [ebp-38h]
  float lhs[3]; // [esp+14Ch] [ebp-14h] BYREF
  int i; // [esp+158h] [ebp-8h]
  int v29; // [esp+15Ch] [ebp-4h]

  if ( a1 )
  {
    if ( *(_DWORD *)(a1 + 224) != -1 )
    {
      rf_renderer_light_release(*(_DWORD *)(a1 + 224), 0);
      *(_DWORD *)(a1 + 224) = -1;
    }
    v29 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v29 && (unk_87C63E || rf_entity_flags810_has_mask4000(v29)) )
    {
      v1 = rf_vector_multiply_scalar((const float *)(v29 + 2040), scaled_result, flt_662E3C);
      rf_vector_add((const float *)(v29 + 2004), lhs, v1);
      rf_solid_collision_query_construct_clear_face_hint(v21);
      rf_solid_collision_result_construct_noop((int)v19);
      v26 = 4;
      rf_vector_copy(rhs, copy_result, (const float *)(v29 + 2004));
      v2 = rf_vector_subtract(lhs, out_vector, rhs);
      rf_vector_copy(destination, v14, v2);
      destination[3] = 0.0;
      rf_world_collision_sweep((char *)rf_world_solid, (int)v21, (int)v19, 1);
      if ( v19[0] > 0 )
      {
        v3 = rf_vector_multiply_scalar((const float *)(v29 + 2040), v13, 0.5);
        v4 = rf_vector_subtract(v20, v12, v3);
        rf_vector_copy(lhs, v11, v4);
      }
      v26 = 0;
      for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
      {
        rf_vector_copy(v22, v10, (const float *)(i + 60));
        rf_matrix3_copy(v23, (const float *)(i + 72));
        rf_world_collision_sweep(*(char **)(i + 660), (int)v21, (int)v19, 0);
        if ( v19[0] > 0 )
        {
          rf_matrix3_rotate_vector(v20, v18, (float *)(i + 72));
          rf_vector_accumulate(v18, (float *)(i + 60));
          v5 = rf_vector_multiply_scalar((const float *)(v29 + 2040), v9, 0.5);
          v6 = rf_vector_subtract(v18, v8, v5);
          rf_vector_copy(lhs, v7, v6);
        }
      }
      *(_DWORD *)(a1 + 224) = rf_renderer_point_light_create((int)lhs, flt_662E44, flt_662E38, 1.0, 1.0, 1.0, 1, 1, 0);
    }
  }
}

