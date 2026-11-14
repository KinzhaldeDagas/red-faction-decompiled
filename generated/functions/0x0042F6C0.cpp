// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042F6C0 sub_42F6C0
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Modelclass+29C setup caches eye lookup+1EC and local standing+9C/crouch+A8 vectors. Requests canonical state0 Entity+8E4 mix1 before standing node transform; finds exact bytes eye\0 at632988 (push OFFSET, not a pointer loaded from its bytes). On no node storeszero vector. For humanoid40D150 zeroes rawX/Z after composition.4354D0 admits crouch if state9+974 or state8+964 handle!=-1; resets cyclic state,requests canonical8/mix1,updates .2 with finalflag1,then caches crouch and restores0/mix1 with .2 update. Host camera substring/bone/bounds heuristics are not this provider.
// UNREALRED VERIFIED [combat-speech-eye-phase-20261111]: CORRECTION to simplified fixed-.2 crouch description: standcache reads pose after prior constructor stand-state advancement by frameDelta. Reset565000->562D40->5877B0 does NOT reset shared statephase7428; requesting crouch8 then advance.2 inherits standing normalized phase. Crouch cache is not a bare bindpose or independent crouch.2 sample. Exact eye bytes632988=65 79 65 00, assemblypushOFFSET. Restoringstand also preserves inheritedphase and advances.2. Instance clock/phase and first-model-class-cache lifetime are required inputs.
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: Shared MODELclass Entity+29C, not gameplayclass+294: loops authored48-byte records atclass+B68 in sourceorder;564DD0 finds first CI PREFIX model sphere. Unmatched negative index skips all writes. For matching class40-byte standing record at+CEC: ALWAYS replace SP+8/MP+12, replace radius+0 onlyif authored radius>0; replace spring+10/+14 onlyif constant>0; activefactor+4 selectsSP/MP. Thus later duplicate overrides replace factors but nonpositive later radius preserves prior positive radius. Geometry is initialized once under class+724 bit40000000; this is distinct from current-pose sphere-center queries.
// [UnrealRed physical spheres 2026-11-12; verified ASM] Standing class40 projection uses GAMEPLAYclass Entity+294 flags+724 mask0x24000; crouch center projection uses MODELclass Entity+29C flags+724 same mask. Class40 standing/Crouch arrays at modelclass+CEC/E30; crouch copy predates override loop and only sphere center is resampled (getter radius ignored). Positive source radius/K overrides modify standing only; perbody24 takes radius/K/L from standing and later stance copies XYZ only. Clearance modelclass+F74=max(0,float(standY-crouchY)), but4361B0 reads GAMEPLAYclass+F74; alternate class identities cannot be blindly aliased.
unsigned __int8 __cdecl sub_42F6C0(void **a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  int first_dword; // eax
  int v5; // eax
  int v6; // esi
  int v7; // esi
  float *v8; // esi
  int v9; // esi
  int v10; // esi
  int v11; // esi
  int v12; // esi
  int v13; // eax
  int element_address; // eax
  unsigned __int8 result; // al
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // ecx
  float v24; // [esp-8h] [ebp-214h] BYREF
  int v25; // [esp-4h] [ebp-210h]
  int v26; // [esp+0h] [ebp-20Ch]
  int v27; // [esp+4h] [ebp-208h]
  int v28; // [esp+8h] [ebp-204h] BYREF
  float *v29; // [esp+Ch] [ebp-200h]
  float *v30; // [esp+10h] [ebp-1FCh]
  float *v31; // [esp+14h] [ebp-1F8h]
  char *v32; // [esp+18h] [ebp-1F4h]
  float v33; // [esp+1Ch] [ebp-1F0h]
  float v34[3]; // [esp+24h] [ebp-1E8h] BYREF
  float v35[3]; // [esp+30h] [ebp-1DCh] BYREF
  float v36[3]; // [esp+3Ch] [ebp-1D0h] BYREF
  float v37[3]; // [esp+48h] [ebp-1C4h] BYREF
  float v38[3]; // [esp+54h] [ebp-1B8h] BYREF
  _BYTE v39[36]; // [esp+60h] [ebp-1ACh] BYREF
  float v40[4]; // [esp+84h] [ebp-188h] BYREF
  float v41[7]; // [esp+94h] [ebp-178h] BYREF
  float copy_result[3]; // [esp+B0h] [ebp-15Ch] BYREF
  float v43[3]; // [esp+BCh] [ebp-150h] BYREF
  float v44[3]; // [esp+C8h] [ebp-144h] BYREF
  float v45[3]; // [esp+D4h] [ebp-138h] BYREF
  float v46[3]; // [esp+E0h] [ebp-12Ch] BYREF
  _BYTE v47[36]; // [esp+ECh] [ebp-120h] BYREF
  float v48[3]; // [esp+110h] [ebp-FCh] BYREF
  float v49; // [esp+11Ch] [ebp-F0h]
  char v50[4]; // [esp+120h] [ebp-ECh] BYREF
  char v51[36]; // [esp+124h] [ebp-E8h] BYREF
  float destination[4]; // [esp+148h] [ebp-C4h] BYREF
  float v53; // [esp+158h] [ebp-B4h]
  float v54; // [esp+15Ch] [ebp-B0h]
  char v55[4]; // [esp+160h] [ebp-ACh] BYREF
  float v56; // [esp+164h] [ebp-A8h]
  float v57; // [esp+170h] [ebp-9Ch]
  char v58[4]; // [esp+178h] [ebp-94h] BYREF
  float v59; // [esp+17Ch] [ebp-90h]
  int v60; // [esp+184h] [ebp-88h]
  float v61[6]; // [esp+188h] [ebp-84h] BYREF
  char v62[12]; // [esp+1A0h] [ebp-6Ch] BYREF
  int v63; // [esp+1ACh] [ebp-60h]
  char v64[36]; // [esp+1B0h] [ebp-5Ch] BYREF
  char v65[36]; // [esp+1D4h] [ebp-38h] BYREF
  char v66[12]; // [esp+1F8h] [ebp-14h] BYREF
  int named_sphere_adapter; // [esp+204h] [ebp-8h]
  int i; // [esp+208h] [ebp-4h]

  rf_matrix3_construct(v65);
  rf_vector3_default_construct_noop(v66);
  *((_DWORD *)a1[167] + 457) |= 0x40000000u;
  if ( (int)a1[569] >= 0 )
    rf_model_handle_set_cyclic_mix_adapter((int *)a1[32], (int)a1[569], 1.0);
  *((_DWORD *)a1[167] + 123) = rf_model_handle_find_node_adapter((int)a1[32], (char *)off_632988);
  if ( *((_DWORD *)a1[167] + 123) == -1 )
  {
    v3 = rf_vector3_set_components_return_destination(v43, 0.0, 0.0, 0.0);
    rf_vector_copy((float *)a1[167] + 39, copy_result, v3);
  }
  else
  {
    rf_matrix3_construct(v64);
    LODWORD(v33) = (char *)a1[167] + 156;
    v31 = rf_vector3_set_components_return_destination(v48, 0.0, 0.0, 0.0);
    v30 = rf_vector3_set_components_return_destination(v46, 0.0, 0.0, 1.0);
    v29 = rf_vector3_set_components_return_destination(v45, 0.0, 1.0, 0.0);
    v1 = rf_vector3_set_components_return_destination(v44, 1.0, 0.0, 0.0);
    v2 = (float *)rf_matrix3_construct_from_three_rows((int)v47, v1, v29, v30);
    rf_vmesh_compose_prop_world_transform(
      (int)a1[32],
      *((_DWORD *)a1[167] + 123),
      v2,
      (int)v31,
      (int)v64,
      (float *)LODWORD(v33));
    if ( rf_entity_has_humanoid_flag((int)a1) )
    {
      *((float *)a1[167] + 39) = 0.0;
      *((float *)a1[167] + 41) = 0.0;
    }
  }
  named_sphere_adapter = rf_model_handle_named_sphere_count_adapter(a1[32]);
  if ( named_sphere_adapter )
  {
    for ( i = 0; i < named_sphere_adapter; ++i )
    {
      rf_record_vector_at24_default_construct_noop(v55);
      v56 = 1.0;
      v57 = -1.0;
      v60 = i;
      rf_model_handle_get_named_sphere_adapter(a1[32], i, (float *)v58, (float *)v55);
      if ( (*((_DWORD *)a1[165] + 457) & 0x24000) != 0 )
        rf_vector3_set_components_thiscall((float *)v58, 0.0, v59, 0.0);
      rf_float6_vector3_dword40_assign(&v24, (float *)v55);
      sub_43CD10((float *)a1[167] + 827, v24, v25, v26, v27, v28, (int)v29, (int)v30, (int)v31, (int)v32, SLODWORD(v33));
      if ( rf_entity_has_record_at974_or964((int)a1) )
      {
        rf_float6_vector3_dword40_assign(&v24, (float *)v55);
        sub_43CD10(
          (float *)a1[167] + 908,
          v24,
          v25,
          v26,
          v27,
          v28,
          (int)v29,
          (int)v30,
          (int)v31,
          (int)v32,
          SLODWORD(v33));
      }
    }
  }
  else
  {
    rf_record_vector_at24_default_construct_noop((char *)v61);
    rf_vector3_zero_return_destination((float *)v62);
    v61[1] = 1.0;
    v61[4] = -1.0;
    v61[0] = *((float *)a1[167] + 16);
    v63 = -1;
    rf_float6_vector3_dword40_assign(&v24, v61);
    sub_43CD10((float *)a1[167] + 827, v24, v25, v26, v27, v28, (int)v29, (int)v30, (int)v31, (int)v32, SLODWORD(v33));
    if ( rf_entity_has_record_at974_or964((int)a1) )
    {
      rf_float6_vector3_dword40_assign(&v24, v61);
      sub_43CD10((float *)a1[167] + 908, v24, v25, v26, v27, v28, (int)v29, (int)v30, (int)v31, (int)v32, SLODWORD(v33));
    }
  }
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)a1[167] + 2920);
    if ( i >= first_dword )
      break;
    v5 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
    named_sphere_adapter = rf_model_handle_find_named_sphere_adapter(a1[32], (char *)(v5 + 24));
    if ( named_sphere_adapter >= 0 )
    {
      v6 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
      *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 8) = *(float *)(v6 + 8);
      v7 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
      *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 12) = *(float *)(v7 + 12);
      if ( *(float *)rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i) > 0.0 )
      {
        v8 = (float *)rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
        *(float *)rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) = *v8;
      }
      if ( *(float *)(rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i) + 16) > 0.0 )
      {
        v9 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 16) = *(float *)(v9 + 16);
        v10 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 20) = *(float *)(v10 + 20);
      }
      if ( rf_multiplayer_runtime_mode )
      {
        v11 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 4) = *(float *)(v11 + 12);
      }
      else
      {
        v12 = rf_inline_record48_element_unchecked((char *)a1[167] + 2920, i);
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, named_sphere_adapter) + 4) = *(float *)(v12 + 8);
      }
    }
  }
  rf_pointer_array_release_storage(a1 + 97);
  a1[106] = (void *)((unsigned int)a1[106] & 0xFFFFDFFF);
  for ( i = 0; ; ++i )
  {
    v13 = rf_receiver_get_first_dword((char *)a1[167] + 3308);
    if ( i >= v13 )
      break;
    rf_vector_prefix_construct_noop(destination);
    element_address = rf_inline_array40_get_element_address((char *)a1[167] + 3308, i);
    rf_vector_copy(destination, v41, (const float *)(element_address + 24));
    destination[3] = *(float *)rf_inline_array40_get_element_address((char *)a1[167] + 3308, i);
    v53 = *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, i) + 16);
    v54 = *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3308, i) + 20);
    if ( v53 > 0.0 )
      a1[106] = (void *)((unsigned int)a1[106] | 0x2000);
    rf_record24_copy_construct_six_floats((float *)&v28, destination);
    rf_array24_append_record_by_value(
      (int *)a1 + 97,
      *(float *)&v28,
      (int)v29,
      (int)v30,
      (int)v31,
      (int)v32,
      SLODWORD(v33));
  }
  rf_physics_shape_recompute_radius_and_axis_bounds((int)(a1 + 34));
  result = rf_entity_has_record_at974_or964((int)a1);
  if ( result )
  {
    rf_model_handle_reset_cyclic_adapter((int)a1[32]);
    rf_model_handle_set_cyclic_mix_adapter((int *)a1[32], (int)a1[601], 1.0);
    rf_vfx_update_instance((int *)a1[32], 0.2, 0, 0, 0, 1);
    if ( *((_DWORD *)a1[167] + 123) == -1 )
    {
      v18 = rf_vector3_set_components_return_destination(v35, 0.0, 0.0, 0.0);
      rf_vector_copy((float *)a1[167] + 42, v34, v18);
    }
    else
    {
      rf_matrix3_construct(v51);
      LODWORD(v33) = (char *)a1[167] + 168;
      v32 = v51;
      v31 = rf_vector3_set_components_return_destination(v40, 0.0, 0.0, 0.0);
      v30 = rf_vector3_set_components_return_destination(v38, 0.0, 0.0, 1.0);
      v29 = rf_vector3_set_components_return_destination(v37, 0.0, 1.0, 0.0);
      v16 = rf_vector3_set_components_return_destination(v36, 1.0, 0.0, 0.0);
      v17 = (float *)rf_matrix3_construct_from_three_rows((int)v39, v16, v29, v30);
      rf_vmesh_compose_prop_world_transform(
        (int)a1[32],
        *((_DWORD *)a1[167] + 123),
        v17,
        (int)v31,
        (int)v32,
        (float *)LODWORD(v33));
      if ( rf_entity_has_humanoid_flag((int)a1) )
      {
        *((float *)a1[167] + 42) = 0.0;
        *((float *)a1[167] + 44) = 0.0;
      }
    }
    *((float *)a1[167] + 989) = 0.0;
    for ( i = 0; ; ++i )
    {
      v19 = rf_receiver_get_first_dword((char *)a1[167] + 3632);
      if ( i >= v19 )
        break;
      v33 = COERCE_FLOAT(v50);
      v20 = rf_inline_array40_get_element_address((char *)a1[167] + 3632, i);
      rf_model_handle_get_named_sphere_adapter(a1[32], i, (float *)(v20 + 24), (float *)LODWORD(v33));
      if ( (*((_DWORD *)a1[167] + 457) & 0x24000) != 0 )
      {
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3632, i) + 24) = 0.0;
        *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3632, i) + 32) = 0.0;
      }
      v21 = rf_inline_array40_get_element_address((char *)a1[167] + 3308, i);
      v49 = *(float *)(v21 + 28) - *(float *)(rf_inline_array40_get_element_address((char *)a1[167] + 3632, i) + 28);
      v33 = v49;
      v22 = (int)a1[167];
      v32 = (char *)v23;
      *((float *)a1[167] + 989) = rf_float_maximum_two_values(*(float *)(v22 + 3956), v49);
    }
    rf_model_handle_reset_cyclic_adapter((int)a1[32]);
    rf_model_handle_set_cyclic_mix_adapter((int *)a1[32], (int)a1[569], 1.0);
    return (unsigned __int8)rf_vfx_update_instance((int *)a1[32], 0.2, 0, 0, 0, 1);
  }
  return result;
}

