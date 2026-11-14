// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487630 rf_mover_create_from_group
// UNREALRED VERIFIED [mission-mover-layout-20261013] Creates ONE common type8 object per nonempty key list; authored common UID +0x20 is FIRST key UID, independent of selected initial key. Current index +0x2F8 starts at authored initial index for nonrotating movers; target +0x2FC starts -1. Mode at +0x2E8. Six group bools map to runtime +0x318 masks [2,4,(direction clear 0x2000 plus 0x100),0x400,0x800,0x1000]. Rotating flag is bool index1. Initial transform comes from key zero before nonrotating initial-key position installation. Actual link remapping, motion/collision and persistence require separate ownership; merely parsing editor placements does not instantiate moving solids.
// UNREALRED VERIFIED [mission-mover-world-20261013] Runtime ordering: appends each newly created controller at the TAIL of the mover list (sentinel0x704610, first0x70489C, last0x7048A0; common next+0x28C/prev+0x290). Loader creation order therefore determines contributor traversal order. Constructor target index+0x2FC=-1; it does not automatically activate the mover. Selected initial key only installs the initial nonrotating position.
int __cdecl rf_mover_create_from_group(int a1)
{
  int v2; // eax
  int v3; // eax
  int first_dword; // eax
  int *v5; // eax
  int v6; // eax
  int *v7; // eax
  int v8; // eax
  int *v9; // eax
  const char *v10; // eax
  int v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // ecx
  unsigned int v14; // eax
  int **v15; // eax
  int v16; // eax
  _DWORD **v17; // eax
  int v18; // eax
  float distance; // [esp+0h] [ebp-F0h]
  float volume; // [esp+4h] [ebp-ECh]
  int v21; // [esp+10h] [ebp-E0h]
  float v22[3]; // [esp+14h] [ebp-DCh] BYREF
  float v23[3]; // [esp+20h] [ebp-D0h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-C0h] BYREF
  float v25; // [esp+3Ch] [ebp-B4h]
  int v26; // [esp+40h] [ebp-B0h]
  void *v27[39]; // [esp+44h] [ebp-ACh] BYREF
  int i; // [esp+E0h] [ebp-10h]
  int v29; // [esp+ECh] [ebp-4h]

  if ( rf_receiver_get_first_dword((void *)(a1 + 4)) <= 0 )
    return 0;
  rf_object_setup152_construct_members((char *)v27);
  v29 = 0;
  memset(v27, 0, 0x98u);
  v27[0] = nullptr;
  v27[1] = nullptr;
  *(float *)&v27[5] = 1.0;
  *(float *)&v27[33] = -1.0;
  v2 = sub_552200((_DWORD *)(a1 + 4), 0);
  rf_vector_copy((float *)&v27[15], copy_result, (const float *)(*(_DWORD *)v2 + 4));
  v3 = sub_552200((_DWORD *)(a1 + 4), 0);
  rf_matrix3_copy((float *)&v27[18], (const float *)(*(_DWORD *)v3 + 16));
  v27[37] = nullptr;
  v26 = rf_object_create(8, -1, -1, (int)v27, 1, 0);
  if ( v26 )
  {
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a1 + 4));
      if ( i >= first_dword )
        break;
      v5 = (int *)sub_552200((_DWORD *)(a1 + 4), i);
      rf_pointer_array_append_dword((_DWORD *)(v26 + 668), *v5);
    }
    for ( i = 0; ; ++i )
    {
      v6 = rf_receiver_get_first_dword((void *)(a1 + 16));
      if ( i >= v6 )
        break;
      v7 = (int *)sub_552200((_DWORD *)(a1 + 16), i);
      rf_pointer_array_append_dword((_DWORD *)(v26 + 680), *v7);
    }
    for ( i = 0; ; ++i )
    {
      v8 = rf_receiver_get_first_dword((void *)(a1 + 28));
      if ( i >= v8 )
        break;
      v9 = (int *)sub_552200((_DWORD *)(a1 + 28), i);
      rf_pointer_array_append_dword((_DWORD *)(v26 + 692), *v9);
    }
    *(_DWORD *)(v26 + 744) = *(_DWORD *)(a1 + 48);
    *(_DWORD *)(v26 + 780) = -1;
    *(_DWORD *)(v26 + 792) = 0x80000000;
    if ( *(_BYTE *)(a1 + 42) == 1 )
    {
      *(_DWORD *)(v26 + 792) &= ~0x2000u;
      *(_DWORD *)(v26 + 792) |= 0x100u;
    }
    else
    {
      *(_DWORD *)(v26 + 792) |= 0x2000u;
    }
    for ( i = 0; i < 4; ++i )
    {
      if ( (int)rf_string_length_from_cstr((const char **)(a1 + 8 * i + 56)) <= 0 )
      {
        *(_DWORD *)(v26 + 4 * i + 728) = -1;
      }
      else
      {
        v25 = 5.0;
        if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L14S2.rfl") )
          v25 = v25 + v25;
        volume = *(float *)(a1 + 4 * i + 88);
        distance = v25;
        v10 = rf_string_object_c_str_or_empty((const void *)(a1 + 8 * i + 56));
        v11 = rf_sound_resource_load(v10, distance, volume, 1.0);
        *(_DWORD *)(v26 + 4 * i + 728) = v11;
        if ( *(_DWORD *)(v26 + 4 * i + 728) != -1 )
          rf_gamesound_resolve_and_load(*(_DWORD *)(v26 + 4 * i + 728));
      }
      *(_DWORD *)(v26 + 4 * i + 796) = -1;
    }
    if ( *(_BYTE *)(a1 + 40) == 1 )
      *(_DWORD *)(v26 + 792) |= 2u;
    if ( *(_BYTE *)(a1 + 41) == 1 )
    {
      *(_DWORD *)(v26 + 792) |= 4u;
      if ( *(float *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 4), 0) + 64) != 0.0
        || *(float *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 4), 0) + 68) != 0.0 )
      {
        *(_DWORD *)(v26 + 792) |= 0x40u;
      }
    }
    if ( *(_BYTE *)(a1 + 43) )
      v12 = *(_DWORD *)(v26 + 792) | 0x400;
    else
      v12 = *(_DWORD *)(v26 + 792) & 0xFFFFFBFF;
    *(_DWORD *)(v26 + 792) = v12;
    if ( *(_BYTE *)(a1 + 44) )
      v13 = *(_DWORD *)(v26 + 792) | 0x800;
    else
      v13 = *(_DWORD *)(v26 + 792) & 0xFFFFF7FF;
    *(_DWORD *)(v26 + 792) = v13;
    if ( *(_BYTE *)(a1 + 45) )
      v14 = *(_DWORD *)(v26 + 792) | 0x1000;
    else
      v14 = *(_DWORD *)(v26 + 792) & 0xFFFFEFFF;
    *(_DWORD *)(v26 + 792) = v14;
    *(_DWORD *)(v26 + 760) = 0;
    *(_DWORD *)(v26 + 764) = -1;
    *(float *)(v26 + 768) = 0.0;
    *(float *)(v26 + 776) = 0.0;
    *(float *)(v26 + 772) = 0.0;
    rf_replicator_arm_milliseconds((int *)(v26 + 784), 0);
    if ( rf_receiver_get_first_dword((void *)(v26 + 668)) <= 0 )
    {
      *(_DWORD *)(v26 + 748) = 0;
    }
    else
    {
      v15 = (int **)sub_552200((_DWORD *)(v26 + 668), 0);
      v16 = sub_479EC0(**v15);
      *(_DWORD *)(v26 + 748) = v16;
    }
    *(_DWORD *)(v26 + 788) = -1;
    v17 = (_DWORD **)sub_552200((_DWORD *)(v26 + 668), 0);
    *(_DWORD *)(v26 + 32) = **v17;
    *(float *)(v26 + 752) = 0.0;
    *(float *)(v26 + 756) = 0.0;
    if ( !rf_mover_is_rotating(v26) )
    {
      v18 = sub_552200((_DWORD *)(v26 + 668), *(_DWORD *)(a1 + 52));
      rf_vector_copy((float *)(v26 + 228), v23, (const float *)(*(_DWORD *)v18 + 4));
      rf_vector_copy((float *)(v26 + 240), v22, (const float *)(v26 + 228));
      rf_vector3_zero_return_destination((float *)(v26 + 324));
      rf_object_publish_position_and_bounds(v26, (float *)(v26 + 228));
      *(float *)(v26 + 756) = 0.0;
      *(float *)(v26 + 772) = 0.0;
      *(_DWORD *)(v26 + 760) = *(_DWORD *)(a1 + 52);
    }
    *(_BYTE *)(v26 + 660) = dword_704608[0];
    ++dword_704608[0];
    rf_replicator_arm_milliseconds((int *)(v26 + 664), -1);
    *(_DWORD *)(v26 + 656) = unk_7048A0;
    *(_DWORD *)(v26 + 652) = &unk_704610;
    *(_DWORD *)(unk_7048A0 + 652) = v26;
    unk_7048A0 = v26;
    v21 = v26;
    v29 = -1;
    rf_object_setup152_destroy_array_backing(v27);
    return v21;
  }
  else
  {
    v29 = -1;
    rf_object_setup152_destroy_array_backing(v27);
    return 0;
  }
}

