// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042C520 rf_entity_render_runtime_vfx
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), multiple sequential render passes; no normalized success/pointer return despite saved type. Construct ONE render-options
// record at entry and REUSE through all passes; default colors12/24/40 are uninitialized, matrix44 identity and flags0 from561B70/561BC0. First SIGNED i=0..<live entity array2264
// count: nonnull current entry plus class660 inline tag at+496,i !=EXACT-1 required, no class-tag count bound. Compose entity model128/tag with COMMON matrix72/position60 into
// locals. Update handle with six raw slots(handle,FLOATframeDeltaSeconds,0,position,matrix,1), then RE-READ array entry and submit(handle,position,matrix,options); neither delegated
// result nor post-update handle rechecked. Debug BYTE681E7A any nonzero sets global RGBA(255,0,0,255) and draws sphere F32.10000000149011612 at composed point. Next entity model2120
// nonnull plus class tag244!=-1 composes COMMON72/60 and renders. Next class tag248!=-1 composes with RETAINED matrix2016 but COMMON position60; mode1312==11 selects
// sizeF32.20000000298023224 and texture681E68 iff entity1364==9, else681E20; mode15 selects sizeF32.10000000149011612 and green681E20 iff target1376==-1, else red681E68. Only
// selected texture!=-1 submits pending textures(texture,-1), billboard(position,FLOAT0,size,global glow-state187CC84); other modes still compose but do not draw billboard. Next
// entity2064mask200000 plus SIGNED class tag1764>=0 and model5136 nonnull: compose COMMON72/60; EXACT global87C640 BYTE4016==1 ORoptionsflags2 and set color12 green(0,32,0,255), ELSE
// ORflags80, options40=entity rawRGBA5236, options44=COMMON matrix72. These option mutations persist into all later passes. Class1832mask200 plus476D00 AL any nonzero subtracts exact
// DOUBLE0.029999999329447746 from composed position Z, finalfloat32, before rendering5136. Jeep predicate EXACT AL1 plus global model681E80 nonnull: compose entity model128/tag5204
// (no tag validity check) with COMMON72/60. Second-relation predicate4390E0 EXACT1 then resolve relation-array2252 element1 DWORD+4 as ENTITY; found entity overrides ONLY local
// orientation from its COMMON72. If that entity has player5168 and its camera slot state==0, suppress this jeep model; no local-player identity comparison. Missing
// relation/ENTITY/player or other camera state renders normally, original composed position retained. Next43BFA0 AL any nonzero(class1828mask02000000, entityFLOAT56 ORDERED>0,
// entity2068mask20clear):4BD150 computes node/common point, ignored return, render model DWORD[entity2128+4] with entityCOMMON72; predicate itself does NOT ensure2128nonnull. Finally
// nonnull model5260 renders at COMMON60/72 ONLY when entity pointer!=global681E38; this local-first-person suppression applies ONLY to final5260 pass, not all previous effects. No
// own null/model-kind/liveness/visibility/finite validation, transform-status checks, option/color/texture restoration or rollback; no-write node delegates may leave local transforms
// indeterminate. Final EAX/AL comes from last predicate/render or entity pointer bits on suppressed5260 path.
char __cdecl rf_entity_render_runtime_vfx(float *a1)
{
  int first_dword; // eax
  int *v2; // eax
  int **v3; // eax
  int *v4; // eax
  int v5; // eax
  char result; // al
  float v7; // [esp+0h] [ebp-178h]
  _BYTE v8[12]; // [esp+14h] [ebp-164h] BYREF
  int v9; // [esp+20h] [ebp-158h]
  float v10[3]; // [esp+24h] [ebp-154h] BYREF
  char v11; // [esp+33h] [ebp-145h]
  float v12[9]; // [esp+34h] [ebp-144h] BYREF
  char v13[36]; // [esp+58h] [ebp-120h] BYREF
  float v14[2]; // [esp+7Ch] [ebp-FCh] BYREF
  float v15; // [esp+84h] [ebp-F4h]
  int v16[3]; // [esp+88h] [ebp-F0h] BYREF
  int v17; // [esp+94h] [ebp-E4h]
  float v18; // [esp+98h] [ebp-E0h]
  char v19[36]; // [esp+9Ch] [ebp-DCh] BYREF
  float v20[3]; // [esp+C0h] [ebp-B8h] BYREF
  char v21[36]; // [esp+CCh] [ebp-ACh] BYREF
  char v22[36]; // [esp+F0h] [ebp-88h] BYREF
  int v23[3]; // [esp+114h] [ebp-64h] BYREF
  char v24[12]; // [esp+120h] [ebp-58h] BYREF
  _BYTE v25[28]; // [esp+12Ch] [ebp-4Ch] BYREF
  int v26; // [esp+148h] [ebp-30h]
  float v27[10]; // [esp+14Ch] [ebp-2Ch] BYREF
  int i; // [esp+174h] [ebp-4h]

  rf_model_render_options_construct(v24);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(a1 + 566);
    if ( i >= first_dword )
      break;
    if ( *(_DWORD *)sub_552200((_DWORD *)a1 + 566, i) )
    {
      rf_vector3_default_construct_noop(v23);
      rf_matrix3_construct(v22);
      if ( *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(*((_DWORD *)a1 + 165) + 496), i) != -1 )
      {
        v2 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(*((_DWORD *)a1 + 165) + 496), i);
        rf_vmesh_compose_prop_world_transform(
          *((_DWORD *)a1 + 32),
          *v2,
          a1 + 18,
          (int)(a1 + 15),
          (int)v22,
          (float *)v23);
        v7 = rf_frame_delta_seconds;
        v3 = (int **)sub_552200((_DWORD *)a1 + 566, i);
        rf_vfx_update_instance(*v3, v7, 0, (int)v23, (int)v22, 1);
        v4 = (int *)sub_552200((_DWORD *)a1 + 566, i);
        rf_model_handle_render_all_adapter(*v4, (int)v23, (int)v22, (int)v24);
        if ( unk_681E7A )
        {
          rf_render_color_set_rgba8(255, 0, 0, 255);
          rf_debug_draw_wire_sphere_backend_dispatch((int)v23, 0.1, dword_187CC5C);
        }
      }
    }
  }
  if ( *((_DWORD *)a1 + 530) )
  {
    rf_vector3_default_construct_noop(v20);
    rf_matrix3_construct(v21);
    if ( *(_DWORD *)(*((_DWORD *)a1 + 165) + 244) != -1 )
    {
      rf_vmesh_compose_prop_world_transform(
        *((_DWORD *)a1 + 32),
        *(_DWORD *)(*((_DWORD *)a1 + 165) + 244),
        a1 + 18,
        (int)(a1 + 15),
        (int)v21,
        v20);
      rf_model_handle_render_all_adapter(*((_DWORD *)a1 + 530), (int)v20, (int)v21, (int)v24);
    }
  }
  if ( *(_DWORD *)(*((_DWORD *)a1 + 165) + 248) != -1 )
  {
    rf_vector3_default_construct_noop(v16);
    rf_matrix3_construct(v19);
    rf_vmesh_compose_prop_world_transform(
      *((_DWORD *)a1 + 32),
      *(_DWORD *)(*((_DWORD *)a1 + 165) + 248),
      a1 + 504,
      (int)(a1 + 15),
      (int)v19,
      (float *)v16);
    v17 = -1;
    v18 = 1.0;
    if ( *((_DWORD *)a1 + 328) == 11 )
    {
      v18 = 0.2;
      if ( *((_DWORD *)a1 + 341) == 9 )
        v17 = dword_681E68;
      else
        v17 = dword_681E20;
    }
    if ( *((_DWORD *)a1 + 328) == 15 )
    {
      v18 = 0.1;
      if ( *((_DWORD *)a1 + 344) == -1 )
        v17 = dword_681E20;
      else
        v17 = dword_681E68;
    }
    if ( v17 != -1 )
    {
      rf_renderer_set_pending_texture_handles(v17, -1);
      rf_renderer_world_billboard_aspect_backend_dispatch((int)v16, 0.0, v18, rf_particle_glow_billboard_render_state);
    }
  }
  if ( ((_DWORD)a1[516] & 0x200000) != 0 )
  {
    rf_vector3_default_construct_noop(v14);
    rf_matrix3_construct(v13);
    if ( *(int *)(*((_DWORD *)a1 + 165) + 1764) >= 0 )
    {
      if ( *((_DWORD *)a1 + 1284) )
      {
        rf_vmesh_compose_prop_world_transform(
          *((_DWORD *)a1 + 32),
          *(_DWORD *)(*((_DWORD *)a1 + 165) + 1764),
          a1 + 18,
          (int)(a1 + 15),
          (int)v13,
          v14);
        if ( *(_BYTE *)(unk_87C640 + 4016) == 1 )
        {
          *(_DWORD *)v24 |= 2u;
          rf_color4_set_bytes_return_destination(v25, 0, 32, 0, 255);
        }
        else
        {
          *(_DWORD *)v24 |= 0x80u;
          v26 = *((_DWORD *)a1 + 1309);
          rf_matrix3_copy(v27, a1 + 18);
        }
        if ( (*(_DWORD *)(*((_DWORD *)a1 + 165) + 1832) & 0x200) != 0 && rf_unhide_global_owner_present() )
          v15 = v15 - 0.02999999932944775;
        rf_model_handle_render_all_adapter(*((_DWORD *)a1 + 1284), (int)v14, (int)v13, (int)v24);
      }
    }
  }
  if ( rf_entity_has_jeep_flag((int)a1) && unk_681E80 )
  {
    rf_vector3_default_construct_noop(v10);
    rf_matrix3_construct((char *)v12);
    rf_vmesh_compose_prop_world_transform(
      *((_DWORD *)a1 + 32),
      *((_DWORD *)a1 + 1301),
      a1 + 18,
      (int)(a1 + 15),
      (int)v12,
      v10);
    v11 = 1;
    if ( rf_entity_jeep_second_relation_resolves_object((int)a1) )
    {
      v5 = sub_552200((_DWORD *)a1 + 563, 1);
      v9 = rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v5 + 4));
      if ( v9 )
      {
        rf_matrix3_copy(v12, (const float *)(v9 + 72));
        if ( *(_DWORD *)(v9 + 5168) )
        {
          if ( !rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(v9 + 5168) + 196)) )
            v11 = 0;
        }
      }
    }
    if ( v11 == 1 )
      rf_model_handle_render_all_adapter(unk_681E80, (int)v10, (int)v12, (int)v24);
  }
  result = rf_entity_class_flag2000000_positive_scalar56((int)a1);
  if ( result )
  {
    rf_vector3_default_construct_noop(v8);
    rf_object_copy_node_or_common_world_position((int)a1, (int)v8);
    result = rf_model_handle_render_all_adapter(
               *(_DWORD *)(*((_DWORD *)a1 + 532) + 4),
               (int)v8,
               (int)(a1 + 18),
               (int)v24);
  }
  if ( *((_DWORD *)a1 + 1315) )
  {
    result = (char)a1;
    if ( a1 != (float *)dword_681E38 )
      return rf_model_handle_render_all_adapter(*((_DWORD *)a1 + 1315), (int)(a1 + 15), (int)(a1 + 18), (int)v24);
  }
  return result;
}

