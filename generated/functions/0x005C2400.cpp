// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2400 rf_d3d8_create_and_bind_main_geometry_buffers
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Creates main vertex buffer240000 bytes, usage568(0x238), FVF708(0x2C4), and index buffer20000 bytes, same usage, format101. Pool is2 only for vendor4098/device20804, otherwise0. Negative HRESULT raises fatal gr_direct3d.cpp:689 or697. Sets vertex lock flags1DAEE04=0x2000 and index flags1DAEE08=0x2000 for that adapter else0x1000. Binds vertex stream0 with stride40, index buffer with base0, and fixed-function vertex shader/FVF708. Device state calls are stack-pushed COM calls despite thiscall artifacts. Does not release prior buffers here.
int rf_d3d8_create_and_bind_main_geometry_buffers()
{
  bool v1; // [esp+3h] [ebp-9h]

  v1 = rf_d3d8_adapter_vendor_id == 4098 && rf_d3d8_adapter_device_id == 20804;
  if ( (*(int (__thiscall **)(int, int, int, int, int, int, _DWORD **))(*(_DWORD *)dword_1DAEDC4 + 92))(
         dword_1DAEDC4,
         dword_1DAEDC4,
         240000,
         568,
         708,
         v1 ? 2 : 0,
         &dword_1DAEDB0) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      689,
      "Unable to create main vertex buffer for D3d!");
  if ( (*(int (__stdcall **)(int, int, int, int, int, _DWORD **))(*(_DWORD *)dword_1DAEDC4 + 96))(
         dword_1DAEDC4,
         20000,
         568,
         101,
         v1 ? 2 : 0,
         &dword_1DAEDB4) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp",
      697,
      "Unable to create main index buffer for D3d!");
  unk_1DAEE04 = 0x2000;
  if ( v1 )
    unk_1DAEE08 = 0x2000;
  else
    unk_1DAEE08 = 4096;
  (*(void (__stdcall **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)dword_1DAEDC4 + 332))(
    dword_1DAEDC4,
    0,
    dword_1DAEDB0,
    40);
  (*(void (__stdcall **)(int, _DWORD *, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 340))(dword_1DAEDC4, dword_1DAEDB4, 0);
  return (*(int (__stdcall **)(int, int))(*(_DWORD *)dword_1DAEDC4 + 304))(dword_1DAEDC4, 708);
}

