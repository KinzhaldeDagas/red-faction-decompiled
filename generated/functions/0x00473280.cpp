// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473280 rf_item_instance_spawn
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: Selected-drop item creation checks valid item definition and authority, loads exact definition model throughcommonObjectCreate; failedmodel/commonallocation returnsnull. Caller source handle becomes common+30 owner/parent, distinct from hostLevel lifetime ownership. Newitem+2BC flags start0 (plus class/passedflags);439220 laterORs8 afterreturn, thenqueries ownmodelbound and adjustsposition. Native synchronouscreate doesnotdispatch Unreal-style BeginPlay overlap callbacks; host deferred contact publication is an explicit engine phase adapter.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Instance creation copies supplied signed quantity arg3 directly into item+2A4(+676); no -1/default count resolution occurs here. Definition model filename/type feed common object creation before publication. Class no_pickup bit1 becomes instance+2BC bit1. Exact first class-name comparisons flag_red/base_red/flag_blue/base_blue produce CTF bits20/80/40/100, flags additionally200. These instance domains are not inferred from bound ammo or generic pickup presentation.
int __cdecl rf_item_instance_spawn(
        int a1,
        char *Source,
        int a3,
        int a4,
        float *source,
        float *a6,
        int a7,
        char a8,
        char a9)
{
  int v10; // [esp+4h] [ebp-BCh]
  float copy_result[3]; // [esp+Ch] [ebp-B4h] BYREF
  int v12; // [esp+18h] [ebp-A8h]
  void *v13[38]; // [esp+1Ch] [ebp-A4h] BYREF
  int v14; // [esp+BCh] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && !a9 )
    return 0;
  if ( a1 < 0 || a1 >= unk_6F9124 )
    return 0;
  rf_object_setup152_construct_members((char *)v13);
  v14 = 0;
  memset(v13, 0, sizeof(v13));
  v13[0] = (void *)rf_string_object_c_str_or_empty((char *)&unk_6F9138 + 80 * a1);
  v13[1] = (void *)unk_6F9154[20 * a1];
  *(float *)&v13[5] = 1.0;
  *(float *)&v13[33] = 0.25;
  rf_vector_copy((float *)&v13[15], copy_result, source);
  rf_matrix3_copy((float *)&v13[18], a6);
  *(float *)&v13[3] = 2.0;
  v13[37] = (void *)1137;
  v12 = rf_object_create(1, -1, a4, (int)v13, 0, 0);
  if ( v12 )
  {
    *(_DWORD *)(v12 + 660) = (char *)&unk_6F9130 + 80 * a1;
    *(_DWORD *)(v12 + 664) = a1;
    rf_string_assign_from_cstr((_DWORD *)(v12 + 668), Source);
    *(_DWORD *)(v12 + 676) = a3;
    *(_DWORD *)(v12 + 684) = a7;
    *(_DWORD *)(v12 + 680) = 0;
    rf_timestamp4_invalidate((_DWORD *)(v12 + 688));
    *(float *)(v12 + 696) = *(float *)&dword_6FC428;
    *(_DWORD *)(v12 + 700) = 0;
    *(float *)(v12 + 704) = 0.0;
    rf_physics_state_deactivate(v12 + 136);
    if ( a8 == 1 )
      *(_DWORD *)(v12 + 700) |= 0x10u;
    if ( (*(_DWORD *)(*(_DWORD *)(v12 + 660) + 68) & 1) != 0 )
      *(_DWORD *)(v12 + 700) |= 1u;
    if ( rf_string_equals_case_insensitive(*(_DWORD *)(v12 + 660), "flag_red") )
    {
      *(_DWORD *)(v12 + 700) |= 0x20u;
      *(_DWORD *)(v12 + 700) |= 0x200u;
      rf_ctf_register_flag_home(v12);
    }
    else if ( rf_string_equals_case_insensitive(*(_DWORD *)(v12 + 660), "base_red") )
    {
      *(_DWORD *)(v12 + 700) |= 0x80u;
    }
    else if ( rf_string_equals_case_insensitive(*(_DWORD *)(v12 + 660), "flag_blue") )
    {
      *(_DWORD *)(v12 + 700) |= 0x40u;
      *(_DWORD *)(v12 + 700) |= 0x200u;
      rf_ctf_register_flag_home(v12);
    }
    else if ( rf_string_equals_case_insensitive(*(_DWORD *)(v12 + 660), "base_blue") )
    {
      *(_DWORD *)(v12 + 700) |= 0x100u;
    }
    *(_DWORD *)(v12 + 508) = 2;
    if ( (*(_DWORD *)(v12 + 424) & 0x20) != 0 && (*(_DWORD *)(v12 + 124) & 0x8000) == 0 )
      rf_collision_register_object_against_active_list(v12);
    *(_DWORD *)(v12 + 656) = unk_6FB1C8;
    *(_DWORD *)(v12 + 652) = &unk_6FAF38;
    *(_DWORD *)(unk_6FB1C8 + 652) = v12;
    unk_6FB1C8 = v12;
    v10 = v12;
    v14 = -1;
    rf_object_setup152_destroy_array_backing(v13);
    return v10;
  }
  else
  {
    v14 = -1;
    rf_object_setup152_destroy_array_backing(v13);
    return 0;
  }
}

