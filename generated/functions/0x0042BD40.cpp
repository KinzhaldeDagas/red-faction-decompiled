// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042BD40 rf_entity_render_body_and_attachments_with_view_gates
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), void/incidental return; requires global player pointer P=DWORD87C640, entity/player/view/model storage valid. FIRST
// constructs render options561B70 and captures current renderer view position/orientation581FA0, then COMMON-resolves P DWORD+180 once. Entire render is suppressed if entity player
// pointer+5168==P AND its view-wrapper DWORD+8==0 AND global BYTE6807E0==0 AND captured resolutionNULL. Any differing/nonzero term admits next gates. No own entity/P NULL guard.
// Near-view body suppression is attempted only humanoid predicate EXACT AL1, dead predicate ANY-nonzero false, numeric entity DWORD+1312!=1. Computes halfHeight=FLOAT32(entity
// FLOAT+1988*DOUBLE0.5); viewY must be ORDERED STRICTLY>entityY-halfHeight and ORDERED STRICTLY<entityY+halfHeight. Equality/NaN skips this suppression attempt. Copies entity COMMON
// position, replaces its Y with viewY and compares5598C0 squared distance directly against DOUBLE0.125; only ORDERED distance<0.125 suppresses ENTIRE function
// (body/debug/attachments/VFX), equal/NaN continues. Helper squared sum itself roundsFLOAT32; no extra caller store.  Next, attached-use-vehicle436A80 EXACT AL1 resolves entity+512
// as ENTITY and requires jeep40D400 ANY nonzero, otherwise entire render exits; predicate bytes other than1 bypass this exclusion. Next suppresses only conjunction:
// local/related4BCE50 ANY nonzero, matching entry4BCED0==P, entity full handle differs from entry+20, entry view-wrapper state FULL EAX0,43C910 AL0 (gameplay class primary flags
// DWORD+1828 mask0x1000 clear),turret40D300 AL0,jeep-second-relation4390E0 AL0. These calls short-circuit in order; any failed conjunct allows rendering. Entry=NULL differs from
// required nonnull P and short-circuits before dereference.  Global debug BYTE681E78 EXACT1 sets current RGBA(0,255,0,255), draws wire
// sphere(entity+60,FLOAT0.10000000149011612,backend187CC5C), skips normal model/options/state work, then reaches common attachment/VFX tail; no color restore here. Every other debug
// byte uses normal body path. Render-option defaults: flags0,selector4=-1,alpha8=255,DWORD16=0,FLOAT20=-1,DWORD28=0,texture selectors32/36=-1,matrix44 identity; color bytes12/24/40
// remain uninitialized until explicitly written. If40D280 ANY nonzero AND signed class DWORD+5048>0 AND476D00 AL0, sets option DWORD+4=439140(entity COMMON position,signed
// IDIV((classPointer-683548),5396)); wrapper has no class alignment check; delegated selector admits signed indices0..liveCount INCLUSIVE, invalid returns-1. Selector returns first
// LOD threshold ORDERED strictly>float32 scaled distance, otherwise class LOD count (NaN advances). Entity flags+2064 mask0x40000 ORs option flags0x10.  P BYTE+4016 EXACT1 ORs option
// flag2; if P BYTE+4017 EXACT1 also ORs flag1 and copies unaligned DWORD[P+4018] into color+12; every other byte instead sets that color RGBA(0,32,0,255). Inside4016==1 ONLY, COMMON
// flags entity+124 mask0x800000 AND dead predicate AL0 calls model-reset-cyclic565000, model-reset-actions565020, model-set-cyclic-mix564F60(model,entity DWORD+2276,FLOAT1), in that
// order. This mutates model action state during rendering; prior near-view dead predicate is not cached.  Copies entity COMMON matrix+72 into localMatrix. Turret ANY nonzero AND
// local/related predicate ANY nonzero replaces localMatrix with retained entity matrix+2016. ALWAYS ORs option flag0x80, stores entity DWORD+5236 into options DWORD+40 and copies
// localMatrix into options matrix+44. Use-vehicle437690 ANY nonzero OR secondary-class-mask20 predicate41F0C0 ANY nonzero ORs flag0x100; second predicate called only if first0.
// Entity DWORD+2068 mask0x20000 sets options DWORD+32=global66130C and, if also0x40000, DWORD+36=global661308; if only0x40000 set, DWORD+32=661308 and+36 stays default-1.
// Calls564BB0(model+128,entity position+60,localMatrix,&options), ignores result.  Common tail (including debug path): P BYTE+4017 ANY nonzero skips BOTH attachment42C240 and
// runtime-VFX42C520 calls; exact0 calls both in order. Thus byte2 bypasses exact1 tint-source choice yet still suppresses this tail. Every earlier whole-function rejection suppresses
// tail too. No own model/pose rollback, position writes or null/finite validation; delegate cache/model/VFX/render-color effects remain.
void __cdecl rf_entity_render_body_and_attachments_with_view_gates(int a1)
{
  float v1[9]; // [esp+8h] [ebp-C0h] BYREF
  int local_player_entry_or_related_owner; // [esp+2Ch] [ebp-9Ch]
  int v3; // [esp+30h] [ebp-98h]
  float v4[3]; // [esp+34h] [ebp-94h] BYREF
  float v5; // [esp+40h] [ebp-88h]
  int v6; // [esp+44h] [ebp-84h]
  _DWORD v7[3]; // [esp+48h] [ebp-80h] BYREF
  _DWORD v8[5]; // [esp+54h] [ebp-74h] BYREF
  int v9; // [esp+68h] [ebp-60h]
  int v10; // [esp+6Ch] [ebp-5Ch]
  int v11; // [esp+70h] [ebp-58h]
  float v12[9]; // [esp+74h] [ebp-54h] BYREF
  float v13; // [esp+98h] [ebp-30h] BYREF
  float v14; // [esp+9Ch] [ebp-2Ch]
  float v15[9]; // [esp+A4h] [ebp-24h] BYREF

  rf_model_render_options_construct((char *)v7);
  rf_vector3_default_construct_noop(&v13);
  rf_matrix3_construct((char *)v15);
  rf_renderer_copy_current_view_transform(&v13, v15);
  v6 = rf_object_resolve_handle(*(_DWORD *)(unk_87C640 + 180));
  if ( *(_DWORD *)(a1 + 5168) != unk_87C640
    || rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196))
    || unk_6807E0
    || v6 )
  {
    if ( !rf_entity_has_humanoid_flag(a1)
      || rf_entity_is_dead(a1)
      || *(_DWORD *)(a1 + 1312) == 1
      || (v5 = *(float *)(a1 + 1988) * 0.5,
          rf_vector3_copy_return_destination(v4, (float *)(a1 + 60)),
          v14 <= *(float *)(a1 + 64) - v5)
      || v14 >= *(float *)(a1 + 64) + v5
      || (v4[1] = v14, rf_vector_distance_squared(v4, &v13) >= 0.125) )
    {
      if ( !rf_entity_has_attached_use_vehicle(a1)
        || (v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 512)), rf_entity_has_jeep_flag(v3)) )
      {
        if ( !rf_entity_matches_local_player_or_related_handle(a1)
          || (local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner(a1),
              local_player_entry_or_related_owner != unk_87C640)
          || *(_DWORD *)(a1 + 44) == *(_DWORD *)(local_player_entry_or_related_owner + 20)
          || rf_view_wrapper_get_dword8(*(_DWORD *)(local_player_entry_or_related_owner + 196))
          || rf_entity_class_flag1000(a1)
          || rf_entity_has_turret_flag(a1)
          || rf_entity_jeep_second_relation_resolves_object(a1) )
        {
          if ( unk_681E78 == 1 )
          {
            rf_render_color_set_rgba8(0, 255, 0, 255);
            rf_debug_draw_wire_sphere_backend_dispatch(a1 + 60, 0.1, dword_187CC5C);
          }
          else
          {
            if ( rf_entity_admits_speech_body_actions(a1)
              && *(int *)(*(_DWORD *)(a1 + 660) + 5048) > 0
              && !rf_unhide_global_owner_present() )
            {
              v7[1] = rf_entity_choose_definition_lod(
                        (const float *)(a1 + 60),
                        (*(_DWORD *)(a1 + 660) - (int)rf_entity_info_definitions) / 5396);
            }
            if ( (*(_DWORD *)(a1 + 2064) & 0x40000) != 0 )
              v7[0] |= 0x10u;
            if ( *(_BYTE *)(unk_87C640 + 4016) == 1 )
            {
              v7[0] |= 2u;
              if ( *(_BYTE *)(unk_87C640 + 4017) == 1 )
              {
                v7[0] |= 1u;
                v8[0] = *(_DWORD *)(unk_87C640 + 4018);
              }
              else
              {
                rf_color4_set_bytes_return_destination(v8, 0, 32, 0, 255);
              }
              if ( ((unsigned int)&unk_800000 & *(_DWORD *)(a1 + 124)) != 0 && !rf_entity_is_dead(a1) )
              {
                rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(a1 + 128));
                rf_model_handle_reset_actions_adapter(*(_DWORD *)(a1 + 128));
                rf_model_handle_set_cyclic_mix_adapter(*(int **)(a1 + 128), *(_DWORD *)(a1 + 2276), 1.0);
              }
            }
            rf_matrix3_copy_construct((int)v1, (const void *)(a1 + 72));
            if ( rf_entity_has_turret_flag(a1) && rf_entity_matches_local_player_or_related_handle(a1) )
              rf_matrix3_copy(v1, (const float *)(a1 + 2016));
            v7[0] |= 0x80u;
            v11 = *(_DWORD *)(a1 + 5236);
            rf_matrix3_copy(v12, v1);
            if ( rf_object_is_use_vehicle((_DWORD *)a1) || rf_entity_class_has_secondary_flag20(a1) )
              v7[0] |= 0x100u;
            if ( (*(_DWORD *)(a1 + 2068) & 0x20000) != 0 )
            {
              v9 = dword_66130C;
              if ( (*(_DWORD *)(a1 + 2068) & 0x40000) != 0 )
                v10 = dword_661308;
            }
            else if ( (*(_DWORD *)(a1 + 2068) & 0x40000) != 0 )
            {
              v9 = dword_661308;
            }
            rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 128), a1 + 60, (int)v1, (int)v7);
          }
          if ( !*(_BYTE *)(unk_87C640 + 4017) )
          {
            rf_entity_render_selected_weapon_attachments(a1);
            rf_entity_render_runtime_vfx((_DWORD *)a1);
          }
        }
      }
    }
  }
}

