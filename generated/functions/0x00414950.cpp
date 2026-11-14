// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00414950 rf_clutter_update_lifetime_and_death
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Lifetime/death update: a zero-life source remains a common type4 blocker until deferred deletion. Corpse branch arms object+0x2B4 for 75ms, then calls 0x415190(corpse_class,empty_script,old_handle,position,orientation,0) and marks SOURCE for deletion regardless of corpse allocation success. No-corpse and shatter damage indices greater than 2 mark immediately; that unsigned comparison is broader than explosive-only damage. Bash/bullet/armor-piercing bullet use the low-index particle/corpse branch. Neither lethal life nor corpse visuals directly clear blocker flag 0x00400000.
// UNREALRED VERIFIED [indirect-source-20261029] Lethal clutter explosion calls448DC0 with class VClip, transformed offset, radius and damage scale. The shared helper supplies anonymous radial source -1; the source of the hit that destroyed the clutter is not forwarded to this blast. Existing class-level50ms VClip deadline and75ms corpse replacement remain separate contracts.
// UNREALRED VERIFIED [clutter-clock-20261029] While source life<=0 and class VClip exists, test the shared class+0x70 deadline every object update. If elapsed emit448DC0 then arm class gate50ms. This precedes per-object75ms corpse replacement, so a source retained for corpse replacement may emit again on later updates, including the update that retires it. Shared class arbitration depends on update order. Do not substitute one explosion per death or an independent50ms timer per object.
// UNREALRED VERIFIED [clutter-vclip-debris]: On dead clutter with valid class VClip, 0x414A6B obtains signed particle count; positive count sets local suppression before checking shared explosion deadline. At 0x414E81..0x414E87 suppression skips authored mesh debris even when the VClip did not emit this update. Zero/negative counts do not suppress. Corpse/shatter eligibility is evaluated separately; this does not disable corpse creation or glass particles.
void __cdecl rf_clutter_update_lifetime_and_death(int a1)
{
  float *v1; // eax
  int v2; // eax
  float *v3; // ecx
  int v4; // edx
  int first_dword; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  const char *v10; // eax
  int v11; // [esp-4h] [ebp-108h] BYREF
  int scalar; // [esp+0h] [ebp-104h]
  float v13; // [esp+4h] [ebp-100h]
  float v14; // [esp+8h] [ebp-FCh]
  unsigned int v15; // [esp+Ch] [ebp-F8h]
  float v16[3]; // [esp+14h] [ebp-F0h] BYREF
  float v17[3]; // [esp+20h] [ebp-E4h] BYREF
  float v18[3]; // [esp+2Ch] [ebp-D8h] BYREF
  float scaled_result[3]; // [esp+38h] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+44h] [ebp-C0h] BYREF
  float v21[3]; // [esp+50h] [ebp-B4h] BYREF
  float rhs[3]; // [esp+5Ch] [ebp-A8h] BYREF
  int j; // [esp+68h] [ebp-9Ch]
  char v24[36]; // [esp+6Ch] [ebp-98h] BYREF
  float destination[3]; // [esp+90h] [ebp-74h] BYREF
  float v26[3]; // [esp+9Ch] [ebp-68h] BYREF
  float v27[10]; // [esp+A8h] [ebp-5Ch] BYREF
  _BYTE v28[4]; // [esp+D0h] [ebp-34h] BYREF
  _BYTE v29[4]; // [esp+D4h] [ebp-30h] BYREF
  int v30; // [esp+D8h] [ebp-2Ch]
  int v31; // [esp+DCh] [ebp-28h]
  int v32; // [esp+E4h] [ebp-20h]
  float sum_result[3]; // [esp+ECh] [ebp-18h] BYREF
  int v34; // [esp+F8h] [ebp-Ch]
  bool v35; // [esp+FCh] [ebp-8h]
  char v36; // [esp+FDh] [ebp-7h]
  char v37; // [esp+FEh] [ebp-6h]
  char v38; // [esp+FFh] [ebp-5h]
  int i; // [esp+100h] [ebp-4h]

  if ( rf_replicator_has_elapsed((int *)(a1 + 676)) )
  {
    rf_object_mark_for_deferred_delete(a1);
    if ( *(_DWORD *)(a1 + 680) != -1 )
      rf_gamesound_play_positional_event(*(_DWORD *)(a1 + 680), (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
  }
  if ( *(_DWORD *)(a1 + 672) != -1 )
    rf_positioned_voice_update(*(_DWORD *)(a1 + 672), (float *)(a1 + 60), a1 + 324, 1.0);
  if ( rf_replicator_has_elapsed((int *)(a1 + 688)) )
  {
    rf_replicator_reset((_DWORD *)(a1 + 688));
    for ( i = *(_DWORD *)(a1 + 616); i; i = *(_DWORD *)(i + 336) )
      *(_BYTE *)(i + 320) = 0;
  }
  if ( *(float *)(a1 + 52) <= 0.0 )
  {
    v35 = 0;
    if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 88) != -1 )
    {
      v34 = sub_507830(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 88));
      v35 = v34 > 0;
      if ( rf_replicator_has_elapsed((int *)(*(_DWORD *)(a1 + 660) + 112)) )
      {
        v1 = rf_vector3_transform_by_matrix_rows((float *)(*(_DWORD *)(a1 + 660) + 100), v21, (float *)(a1 + 72));
        rf_vector_add((const float *)(a1 + 60), sum_result, v1);
        v14 = 0.0;
        v2 = *(_DWORD *)(a1 + 660);
        v13 = *(float *)&v3;
        v13 = *(float *)(v2 + 96);
        v4 = *(_DWORD *)(a1 + 660);
        scalar = a1;
        scalar = *(int *)(v4 + 92);
        first_dword = rf_receiver_get_first_dword((void *)a1);
        sub_448DC0(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 88), first_dword, 0, sum_result, *(float *)&scalar, v13, 0);
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(a1 + 660) + 112), 50);
      }
    }
    v36 = 1;
    v38 = 1;
    v37 = 0;
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 116) & 0x10) != 0 )
    {
      v15 = *(_DWORD *)(a1 + 684);
      if ( v15 > 2 )
      {
        v36 = 1;
        v38 = 0;
        v37 = 0;
        rf_object_mark_for_deferred_delete(a1);
      }
      else
      {
        v36 = 0;
        v38 = 1;
        v37 = 1;
      }
    }
    if ( v37 == 1 && !*(_BYTE *)(a1 + 716) )
    {
      *(_BYTE *)(a1 + 716) = 1;
      unk_666B7C = 0;
      rf_particle_descriptor76_construct_noop((int)v26);
      v27[5] = 0.0;
      LODWORD(v27[8]) = rf_bitmap_load_with_optional_mipmap_generation("glasshard_A.tga", (void *)0xFFFFFFFF, 1);
      rf_color4_set_bytes_return_destination(v28, 255, 255, 255, 255);
      v30 = 524;
      v31 = 0;
      v27[6] = 1.0;
      rf_color4_set_bytes_return_destination(v29, 255, 255, 255, 0);
      v27[4] = 0.0;
      v27[7] = 3.0;
      LODWORD(v27[9]) = 1;
      v27[3] = 0.2;
      v32 = 0;
      rf_vector3_default_construct_noop(destination);
      if ( *(int *)(*(_DWORD *)(a1 + 660) + 152) <= -1 )
      {
        rf_vector_copy(destination, copy_result, (const float *)(a1 + 60));
      }
      else
      {
        rf_matrix3_construct(v24);
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a1 + 128),
          *(_DWORD *)(*(_DWORD *)(a1 + 660) + 152),
          (float *)(a1 + 72),
          a1 + 60,
          (int)v24,
          destination);
      }
      for ( j = 0; j < 16; ++j )
      {
        rf_vector3_default_construct_noop(rhs);
        rhs[0] = sub_567730();
        rhs[1] = sub_567730();
        rhs[2] = sub_567730();
        v14 = COERCE_FLOAT(rhs);
        v13 = COERCE_FLOAT(v17);
        v6 = rf_vector_multiply_scalar((const float *)(a1 + 84), scaled_result, 0.1);
        v7 = rf_vector_add(destination, v18, v6);
        v8 = rf_vector_add(v7, (float *)LODWORD(v13), (const float *)LODWORD(v14));
        rf_vector_copy(v26, v16, v8);
        v14 = 0.44;
        rf_vector3_copy_return_destination((float *)&v11, (float *)(a1 + 84));
        rf_random_unit_vector_in_cone(v27, *(float *)&v11, *(float *)&scalar, v13, v14);
        v14 = rf_random_float_range(1.0, 5.0);
        rf_vector3_scale_in_place_return_self(v27, v14);
        v14 = 0.0;
        v13 = 0.0;
        *(float *)&scalar = NAN;
        v11 = (int)destination;
        v9 = rf_receiver_get_first_dword((void *)a1);
        rf_particle_allocate_and_initialize(0, (int)v26, v9, v11, scalar, (_DWORD *)LODWORD(v13), SLODWORD(v14));
      }
    }
    if ( v38 )
    {
      if ( *(_DWORD *)(a1 + 668) == -1 )
      {
        rf_object_mark_for_deferred_delete(a1);
      }
      else
      {
        v36 = 0;
        if ( rf_replicator_is_armed((_DWORD *)(a1 + 692)) )
        {
          if ( rf_replicator_has_elapsed((int *)(a1 + 692)) )
          {
            rf_clutter_runtime_create(
              *(_DWORD *)(a1 + 668),
              (char *)&byte_6312BA,
              *(_DWORD *)(a1 + 44),
              a1 + 60,
              a1 + 72,
              0);
            rf_object_mark_for_deferred_delete(a1);
          }
        }
        else
        {
          rf_replicator_arm_milliseconds((int *)(a1 + 692), 75);
        }
      }
    }
    if ( v36 == 1
      && !v35
      && rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(a1 + 660) + 24, (char *)&byte_6312BB) )
    {
      LODWORD(v14) = *(_DWORD *)(a1 + 660) + 32;
      v13 = *(float *)(a1 + 660);
      v13 = *(float *)(LODWORD(v13) + 120);
      scalar = 4000;
      v11 = -1;
      v10 = rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 24));
      rf_clutter_spawn_authored_debris(a1, (int)v10, v11, scalar, v13, (std::exception *)LODWORD(v14));
    }
  }
}

