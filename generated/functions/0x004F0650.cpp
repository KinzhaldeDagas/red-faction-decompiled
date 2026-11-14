// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0650 rf_mount_user_maps_and_active_mod_vpps
// UNREALRED VERIFIED [source-ownership-20260930] The enabled, nonempty mod argument is used to register mods\<argument> and enumerate its VPP files after the user-map groups. No alternate mod argument is selected in this function. Rejecting malformed host directory-name configuration in UnrealRed is an explicit host policy, not a recovered RF path-validation rule.
char rf_mount_user_maps_and_active_mod_vpps()
{
  const char **v0; // eax
  char v2; // [esp+Bh] [ebp-115h]
  _WORD *v3; // [esp+Ch] [ebp-114h]
  char *v5; // [esp+14h] [ebp-10Ch]
  unsigned int v6; // [esp+28h] [ebp-F8h]
  _BYTE *v8; // [esp+38h] [ebp-E8h]
  void *v9; // [esp+44h] [ebp-DCh] BYREF
  char v10[132]; // [esp+48h] [ebp-D8h] BYREF
  int v11; // [esp+CCh] [ebp-54h]
  int v12; // [esp+D0h] [ebp-50h]
  int v13; // [esp+D4h] [ebp-4Ch]
  const char *v14[14]; // [esp+D8h] [ebp-48h] BYREF
  char *i; // [esp+114h] [ebp-Ch]
  char *v16; // [esp+118h] [ebp-8h]
  const char *v17; // [esp+11Ch] [ebp-4h]

  v17 = "*.vpp";
  v13 = (int)"user_maps\\single\\";
  v12 = (int)"user_maps\\multi\\";
  rf_vpackfile_set_loading_user_maps(1);
  rf_enumerate_files_sorted(v14, unk_88E43C, "*.vpp", 5, nullptr);
  for ( i = (char *)v14[0]; i != (char *)v14; i = *(char **)i )
    rf_vpackfile_add(i + 8, (const char *)v13);
  for ( i = (char *)v14[0]; i != (char *)v14; i = v16 )
  {
    v16 = *(char **)i;
    i[8] = 0;
    **((_DWORD **)i + 1) = *(_DWORD *)i;
    *(_DWORD *)(*(_DWORD *)i + 4) = *((_DWORD *)i + 1);
    *(_DWORD *)i = 0;
    *((_DWORD *)i + 1) = 0;
    HIBYTE(v9) = HIBYTE(i);
    operator delete(i);
  }
  rf_enumerate_files_sorted(v14, unk_88E440, v17, 5, nullptr);
  for ( i = (char *)v14[0]; i != (char *)v14; i = *(char **)i )
    rf_vpackfile_add(i + 8, (const char *)v12);
  for ( i = (char *)v14[0]; i != (char *)v14; i = v16 )
  {
    v16 = *(char **)i;
    i[8] = 0;
    **((_DWORD **)i + 1) = *(_DWORD *)i;
    *(_DWORD *)(*(_DWORD *)i + 4) = *((_DWORD *)i + 1);
    *(_DWORD *)i = 0;
    *((_DWORD *)i + 1) = 0;
    operator delete(i);
  }
  rf_vpackfile_set_loading_user_maps(0);
  LOBYTE(v0) = rf_command_line_bool_option_is_enabled(unk_88E478);
  if ( (unsigned __int8)v0 == 1 )
  {
    v8 = (_BYTE *)unk_88E488;
    do
      LOBYTE(v0) = *v8;
    while ( *v8++ );
    if ( v8 != (_BYTE *)(unk_88E488 + 1) )
    {
      strcpy(v10, "mods\\");
      v6 = unk_88E488 + strlen(unk_88E488) + 1;
      v5 = (char *)&v9 + 3;
      while ( *++v5 )
        ;
      qmemcpy(v5, unk_88E488, v6 - unk_88E488);
      v11 = rf_register_runtime_loose_search_root(v10, ".vpp");
      v3 = (_WORD *)((char *)&v9 + 3);
      do
      {
        v2 = *((_BYTE *)v3 + 1);
        v3 = (_WORD *)((char *)v3 + 1);
      }
      while ( v2 );
      *v3 = 92;
      rf_enumerate_files_sorted(v14, v11, v17, 5, nullptr);
      for ( i = (char *)v14[0]; i != (char *)v14; i = *(char **)i )
        rf_vpackfile_add(i + 8, v10);
      for ( i = (char *)v14[0]; ; i = v16 )
      {
        v0 = v14;
        if ( i == (char *)v14 )
          break;
        v16 = *(char **)i;
        i[8] = 0;
        **((_DWORD **)i + 1) = *(_DWORD *)i;
        *(_DWORD *)(*(_DWORD *)i + 4) = *((_DWORD *)i + 1);
        *(_DWORD *)i = 0;
        *((_DWORD *)i + 1) = 0;
        operator delete(i);
      }
    }
  }
  return (char)v0;
}

