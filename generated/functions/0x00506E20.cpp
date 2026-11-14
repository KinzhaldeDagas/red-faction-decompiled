// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506E20 rf_vclip_spawn_runtime_effect
// UNREALRED VERIFIED [combat-vclip-world-frame]: Inline particle source position is definition+0x3C added directly to arg_C world origin at 0x5072BC..0x5072CD, with no optional-direction rotation. arg_18 is an optional direction vector, not an orientation matrix: nonnull copies that vector at 0x5072E3..0x5072F4; null copies authored definition+0x48 at 0x5072FB..0x50730F. RF global (X,Y,Z) maps through importer to UE (X,-Z,Y); the world-inline emitter frame must use right=UE+X, up=UE+Z, forward=UE-Y. Explosion graph direction also consumes arg_18 or defaults RF+Y at 0x507202..0x50723F; that graph path is separate from inline particle source fields.
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Inline source position+0x3C is added in global RF coordinates, independent of optional arg_18 direction. Nonnull arg_18 replaces source direction; null uses definition+0x48. Each inline particle normalizes that base with unguarded559200 at50743A, always cone-samples5597C0, then adds sampledDirection*definitionSpawnRadius(+0x68)*effectSize to origin (50746B..5074BD): no independent random-radius draw. dirdepend bit8 speed is randomSpeed*dot(sampled,normalizedBase), not dot-squared (5074DB..50751E x87 fmul). Draw order is cone, speed, radius, life. Null direction separately supplies graph axis RF+Y; do not use inline authored direction for graph. Exact zero normalization is undefined natively; any finite-output adapter policy must be explicit.
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Creation order VFX -> independent VBM billboard -> explosion graph -> inline particles. At507096..5071F0, lazy-load VBM metadata, suppress billboard whenVClipFlags bit1(liquid_surface), otherwise allocate exactlyone stationary particle at arg_C worldorigin, radius=2*effectSize, life=float(frameCount)/integerFPS. Flags random_orient0x200, optionalVBMGlow2, optionalconditionalno_z_check0x2000; white start, no color-change/loop/hold/gravity/wind/collision/sourceoffset, parent-1/emitter0/roomretained. Destinationcolor read fromdefinition+0xA8 is unused without clr_change. CORRECTION to earlier emission interpretation: inline minimumDot is clamped[-1,+1] at5073E4..507400 BEFOREloop50741E; inline alwayssamples afterthisclamp, unlike graph sparks raw cone bound.
int __cdecl rf_vclip_spawn_runtime_effect(
        unsigned int a1,
        void *a2,
        float *a3,
        float *source,
        float *a5,
        int a6,
        float *a7,
        char a8)
{
  int v9; // eax
  float *v10; // eax
  const float *v11; // eax
  char *v12; // eax
  _DWORD *instance; // eax
  float *v14; // ecx
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  double v18; // st7
  float *v19; // ecx
  double v20; // st7
  float *v21; // ecx
  float *v22; // [esp+4h] [ebp-1C4h] BYREF
  float scalar; // [esp+8h] [ebp-1C0h]
  float v24; // [esp+Ch] [ebp-1BCh]
  float v25; // [esp+10h] [ebp-1B8h]
  float v26; // [esp+14h] [ebp-1B4h]
  float v27; // [esp+18h] [ebp-1B0h]
  float v28; // [esp+1Ch] [ebp-1ACh]
  double v29; // [esp+20h] [ebp-1A8h]
  float v30[3]; // [esp+28h] [ebp-1A0h] BYREF
  float v31[3]; // [esp+34h] [ebp-194h] BYREF
  float v32[3]; // [esp+40h] [ebp-188h] BYREF
  float scaled_result[4]; // [esp+4Ch] [ebp-17Ch] BYREF
  float v34[3]; // [esp+5Ch] [ebp-16Ch] BYREF
  float v35[3]; // [esp+68h] [ebp-160h] BYREF
  float v36[3]; // [esp+74h] [ebp-154h] BYREF
  float v37[3]; // [esp+80h] [ebp-148h] BYREF
  float v38[3]; // [esp+8Ch] [ebp-13Ch] BYREF
  float v39[3]; // [esp+98h] [ebp-130h] BYREF
  float v40[3]; // [esp+A4h] [ebp-124h] BYREF
  _BYTE v41[36]; // [esp+B0h] [ebp-118h] BYREF
  float copy_result[3]; // [esp+D4h] [ebp-F4h] BYREF
  int i; // [esp+E0h] [ebp-E8h]
  _DWORD *v44; // [esp+E4h] [ebp-E4h]
  float sum_result[3]; // [esp+E8h] [ebp-E0h] BYREF
  float v46[3]; // [esp+F4h] [ebp-D4h] BYREF
  float v47[3]; // [esp+100h] [ebp-C8h] BYREF
  float vector[3]; // [esp+10Ch] [ebp-BCh] BYREF
  float v49; // [esp+118h] [ebp-B0h]
  float v50; // [esp+11Ch] [ebp-ACh]
  float v51; // [esp+120h] [ebp-A8h]
  float v52; // [esp+124h] [ebp-A4h]
  float v53; // [esp+128h] [ebp-A0h]
  int v54; // [esp+12Ch] [ebp-9Ch]
  int v55; // [esp+130h] [ebp-98h]
  int v56; // [esp+134h] [ebp-94h]
  int v57; // [esp+138h] [ebp-90h]
  int v58; // [esp+13Ch] [ebp-8Ch]
  int v59; // [esp+140h] [ebp-88h]
  float v60[3]; // [esp+154h] [ebp-74h] BYREF
  int v61; // [esp+160h] [ebp-68h]
  _DWORD *v62; // [esp+164h] [ebp-64h]
  float destination[3]; // [esp+168h] [ebp-60h] BYREF
  float v64[10]; // [esp+174h] [ebp-54h] BYREF
  _BYTE v65[4]; // [esp+19Ch] [ebp-2Ch] BYREF
  int v66; // [esp+1A0h] [ebp-28h]
  int v67; // [esp+1A4h] [ebp-24h]
  int v68; // [esp+1A8h] [ebp-20h]
  char *v69; // [esp+1B8h] [ebp-10h]
  int first_free_runtime_slot; // [esp+1BCh] [ebp-Ch]
  int v71; // [esp+1C0h] [ebp-8h]
  char *v72; // [esp+1C4h] [ebp-4h]

  if ( a1 >= 0x40 )
    return -1;
  v72 = (char *)&unk_90DC80 + 224 * a1;
  v71 = 0;
  if ( a2 )
  {
    if ( a3 )
    {
      if ( rf_vector_distance_squared(a3, source) <= 0.0 )
      {
        v71 = (int)a2;
      }
      else
      {
        v71 = (int)rf_world_resolve_cached_room((void *)rf_world_solid, a2, a3, source, 0);
        if ( !v71 )
          v71 = (int)a2;
      }
    }
    else
    {
      v71 = (int)a2;
    }
  }
  else
  {
    v71 = (int)rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, source, source, 0);
    if ( !v71 )
      return -1;
  }
  if ( a8 && *((_DWORD *)v72 + 11) != -1 )
  {
    v25 = 0.0;
    v24 = COERCE_FLOAT(flt_17F10B0);
    scalar = 1.0;
    v22 = source;
    v9 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 11));
    rf_gamesound_play_positional_event(v9, source, 1.0, (int)flt_17F10B0, 0);
  }
  if ( rf_rf_string_not_equals_cstring_case_insensitive((int)(v72 + 36), (char *)&byte_63E52A) )
  {
    first_free_runtime_slot = rf_vclip_find_first_free_runtime_slot();
    if ( first_free_runtime_slot == -1 )
      return -1;
    v69 = (char *)&unk_90B880 + 72 * first_free_runtime_slot;
    rf_vector_copy((float *)v69 + 3, copy_result, source);
    if ( a7 )
    {
      rf_orientation_matrix_from_normalized_direction((float *)v69 + 6, a7);
    }
    else
    {
      v25 = COERCE_FLOAT(rf_vector3_set_components_return_destination(v40, 0.0, 0.0, 1.0));
      v24 = COERCE_FLOAT(rf_vector3_set_components_return_destination(v39, 0.0, 1.0, 0.0));
      v10 = rf_vector3_set_components_return_destination(v38, 1.0, 0.0, 0.0);
      v11 = (const float *)rf_matrix3_construct_from_three_rows(
                             (int)v41,
                             v10,
                             (float *)LODWORD(v24),
                             (float *)LODWORD(v25));
      rf_matrix3_copy((float *)v69 + 6, v11);
    }
    v12 = (char *)rf_string_object_c_str_or_empty(v72 + 36);
    instance = rf_vfx_load_instance(v12, (int)byte_98967F);
    *((_DWORD *)v69 + 2) = instance;
    rf_model_handle_reset_actions_adapter(*((_DWORD *)v69 + 2));
    rf_vfx_start_instance(*((int **)v69 + 2), 0, 1.0, 0);
    v69[60] = 1;
    *((float *)v69 + 16) = *((float *)v72 + 47);
    *((_DWORD *)v69 + 17) = v71;
    *((_DWORD *)v69 + 1) = unk_90B83C;
    *(_DWORD *)v69 = &dword_90B838;
    *unk_90B83C = v69;
    unk_90B83C = v69;
  }
  if ( *((_DWORD *)v72 + 5) == -1 && (int)rf_string_length_from_cstr((const char **)v72 + 3) > 0 )
  {
    rf_vclip_preload_bitmap_and_vfx_stub(a1);
    if ( *((_DWORD *)v72 + 5) == -1 )
      rf_string_assign_from_cstr((_DWORD *)v72 + 3, (char *)&byte_63E52B);
  }
  if ( *((_DWORD *)v72 + 5) != -1 && (*((_DWORD *)v72 + 12) & 1) == 0 )
  {
    rf_particle_descriptor76_construct_noop((int)destination);
    rf_vector_copy(destination, v37, source);
    rf_vector3_zero_return_destination(v64);
    v64[3] = *(float *)&a5 + *(float *)&a5;
    v64[4] = 0.0;
    v64[5] = 0.0;
    v64[6] = 0.0;
    v64[7] = (double)*((int *)v72 + 6) / (double)*((int *)v72 + 7);
    v64[8] = *((float *)v72 + 5);
    v64[9] = *((float *)v72 + 6);
    rf_color4_set_bytes_return_destination(v65, 255, 255, 255, 255);
    v66 = *((_DWORD *)v72 + 42);
    v67 = 512;
    v68 = 0;
    if ( v72[32] == 1 )
      v67 |= 2u;
    if ( (*((_DWORD *)v72 + 12) & 4) != 0 )
    {
      v62 = (_DWORD *)rf_entity_resolve_handle(a6);
      if ( v62 )
      {
        if ( sub_438B00(v62) )
          v67 |= 0x2000u;
      }
    }
    rf_particle_allocate_and_initialize(0, destination, v71, 0, -1, nullptr, 0);
  }
  if ( (*((_DWORD *)v72 + 12) & 8) != 0 )
  {
    rf_vector3_default_construct_noop(v60);
    if ( a7 )
      rf_vector_copy(v60, v36, a7);
    else
      rf_vector3_set_components_thiscall(v60, 0.0, 1.0, 0.0);
    v61 = 0;
    if ( v72[192] )
    {
      if ( *(_BYTE *)(v71 + 388) )
        v61 = rf_liquid_room_contains_point(v71, (int)source);
      rf_explosion_graph_create_runtime(v72 + 192, source, v60, *(float *)&a5, v71, v61);
    }
  }
  if ( *((int *)v72 + 13) > 0 )
  {
    rf_particle_descriptor76_construct_noop((int)v47);
    rf_vector_add(source, sum_result, (const float *)v72 + 15);
    rf_vector3_default_construct_noop(v46);
    if ( a7 )
      rf_vector_copy(v46, v35, a7);
    else
      rf_vector_copy(v46, v34, (const float *)v72 + 18);
    v50 = *((float *)v72 + 32);
    v51 = *((float *)v72 + 33);
    v52 = *((float *)v72 + 34);
    v54 = *((_DWORD *)v72 + 39);
    v55 = *((_DWORD *)v72 + 40);
    v56 = *((_DWORD *)v72 + 41);
    v57 = *((_DWORD *)v72 + 42);
    v58 = *((_DWORD *)v72 + 43);
    v59 = 0;
    if ( (*((_DWORD *)v72 + 12) & 4) != 0 )
    {
      v44 = (_DWORD *)rf_entity_resolve_handle(a6);
      if ( v44 )
      {
        if ( sub_438B00(v44) )
          v58 |= 0x2000u;
      }
    }
    rf_float_clamp_in_place((float *)v72 + 21, -1.0, 1.0);
    for ( i = 0; (double)*((int *)v72 + 13) * *(float *)&a5 > (double)i; ++i )
    {
      rf_vector_normalize_reciprocal_sqrt(v46);
      v25 = *(float *)&v14;
      v25 = *((float *)v72 + 21);
      rf_vector3_copy_return_destination((float *)&v22, v46);
      rf_random_unit_vector_in_cone(vector, *(float *)&v22, scalar, v24, v25);
      v25 = *(float *)&a5;
      v24 = COERCE_FLOAT(v32);
      scalar = *(float *)&v72;
      v15 = rf_vector_multiply_scalar(vector, scaled_result, *((float *)v72 + 26));
      v16 = rf_vector_multiply_scalar(v15, (float *)LODWORD(v24), v25);
      v17 = rf_vector_add(sum_result, v31, v16);
      rf_vector_copy(v47, v30, v17);
      if ( (*((_WORD *)v72 + 54) & 8) != 0 )
      {
        v18 = rf_vector_dot(vector, v46);
        v25 = *(float *)&v19;
        v25 = *((float *)v72 + 23);
        v24 = *(float *)&v19;
        v24 = *((float *)v72 + 22);
        v29 = v18;
        v20 = rf_random_float_range(v24, v25);
        v28 = v20 * v29;
        rf_vector3_scale_in_place_return_self(vector, v28);
      }
      else
      {
        v25 = *(float *)&v72;
        v25 = *((float *)v72 + 23);
        v24 = *(float *)&v72;
        v25 = rf_random_float_range(*((float *)v72 + 22), v25);
        rf_vector3_scale_in_place_return_self(vector, v25);
      }
      if ( (*((_DWORD *)v72 + 12) & 2) != 0 )
      {
        v27 = *((float *)v72 + 31) * *(float *)&a5;
        v25 = v27;
        v26 = *((float *)v72 + 30) * *(float *)&a5;
        v49 = rf_random_float_range(v26, v27);
      }
      else
      {
        v25 = *(float *)&v72;
        v25 = *((float *)v72 + 31);
        v24 = *(float *)&v72;
        v49 = rf_random_float_range(*((float *)v72 + 30), v25);
      }
      v25 = *(float *)&v21;
      v25 = *((float *)v72 + 29);
      v24 = *(float *)&v72;
      v53 = rf_random_float_range(*((float *)v72 + 28), v25);
      rf_particle_allocate_and_initialize(0, v47, v71, (int)source, -1, nullptr, 0);
    }
  }
  return 0;
}

