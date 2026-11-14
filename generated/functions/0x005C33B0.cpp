// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C33B0 rf_d3d8_detect_capabilities_and_formats
// UNREALRED VERIFIED [ground-detail-compatibility-20260903]: Detects D3D8 formats and capabilities. Multitexture is enabled only with at least two texture-blend stages and two simultaneous textures; a Voodoo2 name forces it off. This capability feeds the later adapter whitelist and projected-world-light dual-stage gate.
int rf_d3d8_detect_capabilities_and_formats()
{
  int result; // eax
  char *v2; // [esp+Ch] [ebp-20030h]
  char *v4; // [esp+14h] [ebp-20028h]
  char *v6; // [esp+1Ch] [ebp-20020h]
  int v7; // [esp+28h] [ebp-20014h] BYREF
  CHAR Text[131076]; // [esp+2Ch] [ebp-20010h] BYREF
  bool v9; // [esp+20037h] [ebp-5h]
  int i; // [esp+20038h] [ebp-4h]

  if ( unk_187CCA0 == 200 )
  {
LABEL_6:
    byte_664A00 = 1;
    goto LABEL_7;
  }
  if ( unk_187CCA0 != 201 )
  {
    if ( unk_187CCA0 != 202 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
        1086,
        "Invalid window_mode passed to gr_direct3d_init\n");
    goto LABEL_6;
  }
  byte_664A00 = 0;
LABEL_7:
  if ( byte_664A00 )
  {
    GetClientRect(unk_1DAEDF8, &MEMORY[0x1DAED74]);
    GetClientRect(unk_1DAEDF8, &unk_1DAE8E4);
    ClientToScreen(unk_1DAEDF8, (LPPOINT)&MEMORY[0x1DAED74]);
    ClientToScreen(unk_1DAEDF8, (LPPOINT)&unk_1DAED7C);
  }
  unk_1DAE900 = -1;
  unk_1DAED84 = -1;
  unk_1DAE8F4 = -1;
  for ( i = 0; i < 5; ++i )
  {
    if ( rf_d3d8_check_texture_format(dword_664A28[i]) )
    {
      unk_1DAE900 = dword_664A28[i];
      break;
    }
  }
  for ( i = 2; i < 5; ++i )
  {
    if ( rf_d3d8_check_texture_format(dword_664A28[i]) )
    {
      unk_1DAE8F4 = dword_664A28[i];
      break;
    }
  }
  for ( i = 3; i < 5; ++i )
  {
    if ( rf_d3d8_check_texture_format(dword_664A28[i]) )
    {
      unk_1DAED84 = dword_664A28[i];
      break;
    }
  }
  if ( unk_1DAE900 == -1 || unk_1DAED84 == -1 || unk_1DAE8F4 == -1 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1135,
      "Video card does not support suitable texture formats for Red Faction!");
  v9 = 0;
  if ( rf_cstring_find_first_substring_case_insensitive(MEMORY[0x1DAE948], "3dfx") && !rf_d3d8_adapter_vendor_id )
    v9 = rf_d3d8_adapter_device_id == 0;
  if ( rf_cstring_find_first_substring_case_insensitive(unk_1DAEB48, "Voodoo2") )
  {
    unk_1DAEDAB = 1;
    rf_d3d8_multitexture_available = 0;
  }
  else if ( unk_1DAE8A4 < 2u || unk_1DAE8A8 < 2u )
  {
    if ( unk_1DAE8A4 == 3 && unk_1DAE8A8 == 1 )
      unk_1DAEDAB = 1;
    rf_d3d8_multitexture_available = 0;
  }
  else
  {
    rf_d3d8_multitexture_available = 1;
  }
  unk_1DAEDF5 = (unk_1DAE8A0 & 0x10) != 0;
  dword_1DAEDE8 = unk_1DAE86C;
  unk_1DAEDE0 = dword_1DAE868;
  unk_1DAEDEC = 0;
  unk_1DAEDF0 = 0;
  unk_1DAEDDC = 16;
  unk_1DAEDE4 = 16;
  if ( dword_1DAE868 < 16 )
    unk_1DAEDE0 = 256;
  if ( dword_1DAEDE8 < 16 )
    dword_1DAEDE8 = 256;
  unk_1DAEDEC = (unk_1DAE84C & 0x20) != 0;
  unk_1DAEDF0 = (unk_1DAE84C & 2) != 0;
  unk_187CCCC = unk_1DAEDE0;
  unk_187CCD0 = dword_1DAEDE8;
  v7 = 0;
  strcpy(Text, "Your video card is missing the following features required by Red Faction:\r\n\r\n");
  if ( (unk_1DAE8A0 & 8) == 0 )
  {
    v6 = (char *)&v7 + 3;
    while ( *++v6 )
      ;
    strcpy(v6, "Texture blending mode = Modulate\r\n");
    ++v7;
  }
  if ( (unk_1DAE83C & 0x810) == 0 )
  {
    v4 = (char *)&v7 + 3;
    while ( *++v4 )
      ;
    strcpy(v4, "Source blending mode = SRCALPHA or BOTHSRCALPHA\r\n");
    ++v7;
  }
  if ( (unk_1DAE840 & 0x1020) == 0 )
  {
    v2 = (char *)&v7 + 3;
    while ( *++v2 )
      ;
    strcpy(v2, "Destination blending mode = INVSRCALPHA or BOTHINVSRCALPHA\r\n");
    ++v7;
  }
  if ( v7 )
  {
    rf_d3d8_shutdown_backend_if_initialized();
    MessageBoxA(nullptr, Text, "Missing Video Card Features", 0x12000u);
    exit(1);
  }
  dword_664A14 = -1;
  if ( (unk_1DAE834 & 0x80) != 0 )
    dword_664A14 = 2;
  if ( !rf_fixed_pool_heap_spill_enabled[0]
    && !unk_1DAEDAB
    && !byte_664A00
    && (unsigned int)(*(int (__cdecl **)(int))(*(_DWORD *)dword_1DAEDC4 + 16))(dword_1DAEDC4) < 0x500000 )
  {
    rf_d3d8_shutdown_backend_if_initialized();
    MessageBoxA(
      nullptr,
      "At least 8 MB of available video memory is required to run Red Faction!",
      "Missing Features",
      0x12000u);
    exit(1);
  }
  if ( dword_187CCB0 != 16 || rf_d3d8_adapter_vendor_id == 4098 )
    (*(void (__cdecl **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 26, 0);
  else
    (*(void (__cdecl **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 26, 1);
  if ( rf_d3d8_adapter_vendor_id == 4634
    || unk_1DAEDAB
    || v9
    || rf_command_line_bool_option_is_enabled(rf_option_voodoo)
    || rf_command_line_bool_option_is_enabled(rf_option_voodoo3) )
  {
    if ( rf_d3d8_adapter_device_id == 5
      || unk_1DAEDAB
      || v9
      || rf_command_line_bool_option_is_enabled(rf_option_voodoo3) )
    {
      unk_1DAEDA8 = 1;
      rf_d3d8_voodoo3_compatibility_mode = 1;
    }
    unk_1DAEDA9 = 1;
    flt_6649F8 = 0.001;
  }
  if ( unk_1DAE884 > 0.0
    || unk_1DAE888 > 0.0
    || unk_1DAE890 <= (double)dword_187CC98
    || unk_1DAE88C <= (double)dword_187CC94
    || unk_1DAE888 >= (double)unk_1DAE890
    || unk_1DAE884 >= (double)unk_1DAE88C )
  {
    unk_1DAEDA8 = 1;
  }
  (*(void (__cdecl **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 22, 1);
  if ( unk_1DAEDAB )
  {
    (*(void (__cdecl **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 0);
    (*(void (__cdecl **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 0);
  }
  else
  {
    (*(void (__cdecl **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
    (*(void (__cdecl **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 2);
  }
  (*(void (__cdecl **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 16, 2);
  (*(void (__cdecl **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
  (*(void (__cdecl **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 9, 2);
  (*(void (__cdecl **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 29, 0);
  (*(void (__cdecl **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 139, -11250604);
  (*(void (__cdecl **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 136, 0);
  (*(void (__cdecl **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 18, 1);
  if ( unk_1DAEDAB )
  {
    (*(void (__cdecl **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 18, 1);
    (*(void (__cdecl **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 18, 1);
  }
  result = rf_d3d8_set_identity_world_view_and_projection(dword_1DAEDC4);
  unk_1DAEDCC = 1;
  return result;
}

