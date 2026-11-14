// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2F30 rf_d3d8_initialize_backend
// VERIFIED: Direct3D backend initialization resets depth-mode global 0x0187CD1C to 0, the internal value mapped to D3DZB_TRUE (ordinary Z buffering).
// UNREALRED VERIFIED [ground-detail-compatibility-20260903]: Initializes D3D8 backend state and sets the dual-stage ground-detail compatibility byte for exactly five adapter predicates: 1002:5144; vendor 10DE with device >=0100; vendor 121A with the legacy restriction clear and multitexture available; 102B:2527; or 104A:0010.
int __cdecl rf_d3d8_initialize_backend(HWND a1, int a2, int a3, int a4)
{
  int result; // eax
  BYTE Data[4]; // [esp+0h] [ebp-20h] BYREF
  FARPROC Direct3DCreate8; // [esp+4h] [ebp-1Ch]
  int v7; // [esp+8h] [ebp-18h]
  _BYTE v8[12]; // [esp+Ch] [ebp-14h] BYREF
  int v9; // [esp+18h] [ebp-8h]
  HMODULE hModule; // [esp+1Ch] [ebp-4h]

  dword_187CD1C = 0;
  unk_1DAEDF8 = a1;
  unk_1DAEE10 = 0;
  if ( a3 >= 0 )
    unk_1DAEE0C = a3;
  if ( dword_187CCB0 != 16 && dword_187CCB0 != 32 )
  {
    dword_187CCB0 = 16;
    unk_187CCB4 = 2;
  }
  hModule = LoadLibraryA("d3d8.dll");
  if ( !hModule )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1783,
      "DirectX 8 not found!");
  Direct3DCreate8 = GetProcAddress(hModule, "Direct3DCreate8");
  if ( !Direct3DCreate8 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1791,
      "Cannot find d3d entry point!");
  dword_1DAEDC0 = (_DWORD *)((int (__stdcall *)(int))Direct3DCreate8)(120);
  if ( !dword_1DAEDC0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1798,
      "Unable to initialize DirectX 8.0!");
  if ( (*(int (__thiscall **)(_DWORD *, _DWORD *, _DWORD, _BYTE *))(*dword_1DAEDC0 + 32))(
         dword_1DAEDC0,
         dword_1DAEDC0,
         unk_1DAEE0C,
         v8) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1806,
      "Unable to initialize DirectX 8.0!");
  if ( (*(int (__stdcall **)(_DWORD *, _DWORD, int, CHAR *))(*dword_1DAEDC0 + 20))(
         dword_1DAEDC0,
         unk_1DAEE0C,
         2,
         MEMORY[0x1DAE948]) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1812,
      "Internal error.");
  (*(void (__stdcall **)(_DWORD *, _DWORD, int, void *))(*dword_1DAEDC0 + 52))(
    dword_1DAEDC0,
    unk_1DAEE0C,
    1,
    &unk_1DAE810);
  memset(&dword_1DAE914, 0, 0x34u);
  if ( unk_187CCA0 == 201 )
  {
    *(_DWORD *)Data = 0;
    rf_registry_read_dword_or_default(nullptr, "Vsync", Data, 0);
    unk_1DAE944 = *(_DWORD *)Data != 0 ? 1 : 0x80000000;
    unk_1DAE930 = 0;
    unk_1DAE928 = 2;
    dword_1DAE914 = dword_187CC94;
    unk_1DAE918 = dword_187CC98;
    if ( a4 < 0 )
    {
      if ( dword_187CCB0 == 16 )
        unk_1DAE91C = 23;
      else
        unk_1DAE91C = 21;
    }
    else
    {
      unk_1DAE91C = a4;
    }
  }
  else
  {
    unk_1DAE930 = 1;
    unk_1DAE928 = 3;
    unk_1DAE91C = v9;
    dword_1DAE914 = dword_187CC94;
    unk_1DAE918 = dword_187CC98;
  }
  unk_1DAE8F8 = unk_1DAE91C;
  unk_1DAE934 = 1;
  unk_1DAE92C = a1;
  unk_1DAE93C = 1;
  unk_1DAE8FC = unk_1DAE91C;
  if ( rf_d3d8_adapter_vendor_id == 4098 && rf_d3d8_adapter_device_id == 20804
    || rf_d3d8_adapter_vendor_id == 4318 && rf_d3d8_adapter_device_id >= 0x100u
    || rf_d3d8_adapter_vendor_id == 4634 && !rf_d3d8_voodoo3_compatibility_mode && rf_d3d8_multitexture_available
    || rf_d3d8_adapter_vendor_id == 4139 && rf_d3d8_adapter_device_id == 9511
    || rf_d3d8_adapter_vendor_id == 4170 && rf_d3d8_adapter_device_id == 16 )
  {
    rf_d3d8_ground_detail_dual_stage_compatible = 1;
  }
  if ( rf_d3d8_adapter_vendor_id == 4318 )
  {
    if ( dword_187CCB0 == 16 )
      unk_1DAE938 = 80;
    else
      unk_1DAE938 = 75;
  }
  else if ( rf_d3d8_adapter_vendor_id == 4139 )
  {
    unk_1DAE938 = 71;
  }
  else
  {
    unk_1DAE938 = 80;
  }
  v7 = (*(int (__stdcall **)(_DWORD *, _DWORD, int, HWND, int, _DWORD *, int *))(*dword_1DAEDC0 + 60))(
         dword_1DAEDC0,
         unk_1DAEE0C,
         1,
         a1,
         32,
         &dword_1DAE914,
         &dword_1DAEDC4);
  if ( v7 < 0 )
  {
    if ( v7 == -2005532292 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
        1889,
        "Unable to initialize DirectX 8.0 -- Out of video memory!\r\n"
        "(Sometimes this can be fixed by lowering your desktop resolution.)");
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      1891,
      "Unable to initialize DirectX 8.0 -- Device creation failed!\r\n");
  }
  rf_d3d8_detect_capabilities_and_formats();
  rf_d3d8_write_device_diagnostic_file();
  rf_d3d8_create_and_bind_main_geometry_buffers();
  rf_d3d8_texture_cache_initialize_array();
  rf_d3d8_begin_scene_reset_batch_counts();
  dword_664A04 = rf_bitmap_load_with_optional_mipmap_generation("glograd.tga", (void *)0xFFFFFFFF, 1);
  dword_664A08 = rf_bitmap_load_with_optional_mipmap_generation("metal_detailmap01.tga", (void *)0xFFFFFFFF, 1);
  dword_664A0C = rf_bitmap_load_with_optional_mipmap_generation("ground_detailmap01.tga", (void *)0xFFFFFFFF, 1);
  result = rf_bitmap_load_with_optional_mipmap_generation("gray16x16.tga", (void *)0xFFFFFFFF, 1);
  dword_664A10 = result;
  unk_1DAEE10 = 1;
  return result;
}

