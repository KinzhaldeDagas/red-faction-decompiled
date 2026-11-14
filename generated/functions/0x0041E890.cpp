// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E890 rf_corpse_restore_animation_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl(rows,signedCount),532-byte row stride with NO32-row,13-sphere or filename-NUL bound checks. PASS1 walks existing corpses except common flags0x800, scans rows for FIRST stable ID(row0 vs common32): match invokes ONLY common60 restore; miss merely marks deferred deletion. PASS2 each row searches ALL current corpses, including skipped/protected/marked ones; any matching stable ID SKIPS corpse-specific restoration and creation, so existing creation/fade/flags/action/model/sphere fields are retained except common60 effects. Duplicate rows can match an object created by an earlier row. Missing row builds PARTIALLY initialized152-byte setup (no memset): model/solid0,mass
// row60,decoded u16 position,quaternion matrix,radius row64,flags0x33,material3,linear velocity0,scalar12=0, copies row sphere count raw24-byte records via by-value append; constructor only initialized array header. Creates type7 parent-1; failure destroys local setup and continues with no overall rollback. Success common60 restores then applies corpse fields660/664/668,deadline684 from remaining440,688,692/696/700/704/708,class672,shadow field736=0. Loads special filename468 in mode1 or712=0. Main filename500 containing CASE-SENSITIVE substring LITERAL v3d ANYWHERE uses mode1 loader; all other nonempty names load character instance. Character branch resets cyclic; if death action696==-1 scans descriptor action count-1 downward for first zero byte at descriptor4620+k, then starts selected action EVEN if still-1, advances duration then0.3 and refreshes geometry. Empty main filename sets
// model128=0. Calls lighting sample helper47C400 into NO-WRITE color local, copies its DWORD to728; no independent alpha initialization here. Tail-links652/656 and increments total count; no five-corpse eviction budget, timer emitter recreation, whole-object defaulting or explicit item716/voice724 initialization. Local setup destroyed. Nominal EAX is incidental traversal value, not count/status; caller must not infer full restoration of existing corpses.
int __cdecl rf_corpse_restore_animation_state(int a1, int a2)
{
  int result; // eax
  int v3m_mode1; // eax
  int v4; // eax
  _DWORD *character_instance; // eax
  float v6[2]; // [esp-4h] [ebp-100h] BYREF
  int v7; // [esp+4h] [ebp-F8h]
  int v8; // [esp+8h] [ebp-F4h]
  int v9; // [esp+Ch] [ebp-F0h]
  int v10; // [esp+10h] [ebp-ECh]
  float *v11; // [esp+18h] [ebp-E4h]
  int runtime_pointer; // [esp+1Ch] [ebp-E0h]
  int v13; // [esp+20h] [ebp-DCh]
  float v14; // [esp+24h] [ebp-D8h]
  char v15; // [esp+2Bh] [ebp-D1h]
  float v16[4]; // [esp+2Ch] [ebp-D0h] BYREF
  int v17; // [esp+3Ch] [ebp-C0h] BYREF
  void *v18[15]; // [esp+40h] [ebp-BCh] BYREF
  float world_position[3]; // [esp+7Ch] [ebp-80h] BYREF
  float v20[9]; // [esp+88h] [ebp-74h] BYREF
  float v21[7]; // [esp+ACh] [ebp-50h] BYREF
  int v22[5]; // [esp+C8h] [ebp-34h] BYREF
  int v23; // [esp+DCh] [ebp-20h]
  char v24; // [esp+E2h] [ebp-1Ah]
  char v25; // [esp+E3h] [ebp-19h]
  int k; // [esp+E4h] [ebp-18h]
  int j; // [esp+E8h] [ebp-14h]
  int i; // [esp+ECh] [ebp-10h]
  int v29; // [esp+F8h] [ebp-4h]

  result = rf_corpse_list_head;
  for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
    {
      v25 = 0;
      for ( j = 0; j < a2; ++j )
      {
        if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 532 * j) )
        {
          v25 = 1;
          break;
        }
      }
      if ( v25 )
        rf_object_snapshot_restore_common60(i, a1 + 532 * j);
      else
        result = rf_object_mark_for_deferred_delete(i);
    }
  }
  for ( j = 0; j < a2; ++j )
  {
    v24 = 0;
    result = rf_corpse_list_head;
    for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
    {
      result = 532 * j;
      if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 532 * j) )
      {
        v24 = 1;
        break;
      }
    }
    if ( !v24 )
    {
      rf_object_setup152_construct_members((char *)v18);
      v29 = 0;
      rf_float4_construct_zero_zero_zero_one(v16);
      rf_snapshot_unpack_quaternion_s16(v16, (__int16 *)(a1 + 532 * j + 26));
      v18[0] = nullptr;
      v18[2] = nullptr;
      v18[5] = *(void **)(a1 + 532 * j + 60);
      rf_geomod_saved_position_decode_u16(
        (const float *)rf_world_solid,
        (const unsigned __int16 *)(a1 + 532 * j + 12),
        world_position);
      rf_quaternion_to_matrix3_rows(v16, v20);
      v21[6] = *(float *)(a1 + 532 * j + 64);
      v22[3] = 51;
      v18[4] = (void *)3;
      rf_vector3_zero_return_destination(v21);
      *(float *)&v18[3] = 0.0;
      for ( k = 0; k < *(_DWORD *)(a1 + 532 * j + 68); ++k )
      {
        v11 = v6;
        rf_record24_copy_construct_six_floats(v6, (float *)(a1 + 532 * j + 24 * k + 72));
        rf_array24_append_record_by_value(v22, v6[0], SLODWORD(v6[1]), v7, v8, v9, v10);
      }
      v23 = rf_object_create(7, -1, -1, (int)v18, 0, 0);
      if ( v23 )
      {
        rf_object_snapshot_restore_common60(v23, a1 + 532 * j);
        *(float *)(v23 + 660) = *(float *)(a1 + 532 * j + 388);
        *(float *)(v23 + 664) = *(float *)(a1 + 532 * j + 392);
        *(_DWORD *)(v23 + 668) = *(_DWORD *)(a1 + 532 * j + 436);
        rf_snapshot_unpack_replicator_remaining((int *)(v23 + 684), (int *)(a1 + 532 * j + 440));
        *(float *)(v23 + 688) = *(float *)(a1 + 532 * j + 444);
        *(_DWORD *)(v23 + 692) = *(_DWORD *)(a1 + 532 * j + 448);
        *(_DWORD *)(v23 + 696) = *(_DWORD *)(a1 + 532 * j + 452);
        *(_DWORD *)(v23 + 700) = *(_DWORD *)(a1 + 532 * j + 456);
        *(_DWORD *)(v23 + 704) = *(_DWORD *)(a1 + 532 * j + 460);
        *(_DWORD *)(v23 + 708) = *(_DWORD *)(a1 + 532 * j + 464);
        *(_DWORD *)(v23 + 672) = *(_DWORD *)(a1 + 532 * j + 384);
        *(_DWORD *)(v23 + 736) = 0;
        if ( *(_BYTE *)(a1 + 532 * j + 468) )
        {
          v3m_mode1 = rf_model_handle_load_v3m_mode1((char *)(a1 + 532 * j + 468), 1, (void *)0xFFFFFFFF);
          *(_DWORD *)(v23 + 712) = v3m_mode1;
        }
        else
        {
          *(_DWORD *)(v23 + 712) = 0;
        }
        if ( *(_BYTE *)(a1 + 532 * j + 500) )
        {
          v15 = 0;
          if ( rf_cstring_find_first_substring((char *)(a1 + 532 * j + 500), (char *)off_631960) )
          {
            v4 = rf_model_handle_load_v3m_mode1((char *)(a1 + 532 * j + 500), 1, (void *)0xFFFFFFFF);
            *(_DWORD *)(v23 + 128) = v4;
            v15 = 1;
          }
          else
          {
            character_instance = rf_model_handle_load_character_instance((char *)(a1 + 532 * j + 500), 0, 0);
            *(_DWORD *)(v23 + 128) = character_instance;
          }
          if ( !v15 )
          {
            rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(v23 + 128));
            if ( *(_DWORD *)(v23 + 696) == -1 )
            {
              runtime_pointer = rf_model_handle_get_runtime_pointer(*(int **)(v23 + 128));
              v13 = *(_DWORD *)(runtime_pointer + 7504);
              for ( k = *(_DWORD *)(v13 + 3928) - 1; k >= 0; --k )
              {
                if ( !*(_BYTE *)(k + v13 + 4620) )
                {
                  *(_DWORD *)(v23 + 696) = k;
                  break;
                }
              }
            }
            rf_vfx_start_instance(*(int **)(v23 + 128), *(_DWORD *)(v23 + 696), 1.0, 1);
            v14 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(v23 + 128), *(_DWORD *)(v23 + 696));
            v10 = 1;
            v9 = 0;
            v8 = 0;
            v7 = 0;
            rf_vfx_update_instance(*(int **)(v23 + 128), v14, 0, 0, 0, 1);
            rf_vfx_update_instance(*(int **)(v23 + 128), 0.30000001, 0, 0, 0, 1);
            rf_corpse_refresh_vmesh_geometry(v23);
          }
        }
        else
        {
          *(_DWORD *)(v23 + 128) = 0;
        }
        rf_rgba8_default_construct_noop(&v17);
        rf_object_sample_ground_light_color(&v17, v23);
        *(_DWORD *)(v23 + 728) = v17;
        *(_DWORD *)(v23 + 656) = unk_681D88;
        *(_DWORD *)(v23 + 652) = &unk_681AF8;
        *(_DWORD *)(unk_681D88 + 652) = v23;
        unk_681D88 = v23;
        ++unk_681AF0;
        v29 = -1;
        rf_object_setup152_destroy_array_backing(v18);
      }
      else
      {
        v29 = -1;
        rf_object_setup152_destroy_array_backing(v18);
      }
    }
  }
  return result;
}

