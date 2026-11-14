// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2650 rf_d3d8_shutdown_backend_if_initialized
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args,void. If ready DWORD1DAEDCC==0 does nothing. Otherwise resets full viewport,clears color,calls5C2720,then destroys texture-cache array. For each nonNULL pointer1DAEDB0,1DAEDB4,device1DAEDC4,D3D object1DAEDC0,calls vtable+8 Release and clears pointer,then clears ready flag1DAEDCC. Order exactly as listed;release results ignored. Does not clear generic renderer selector/screen/gamma fields or font registry (generic571960 releases fonts afterward). No rollback/error handling and no additional unknown resource semantics assigned to first two pointers.
void rf_d3d8_shutdown_backend_if_initialized()
{
  if ( unk_1DAEDCC )
  {
    rf_renderer_reset_viewport_full_screen();
    rf_renderer_clear_color_backend_dispatch();
    rf_d3d8_end_scene_shutdown_adapter();
    rf_d3d8_texture_cache_destroy_array();
    if ( dword_1DAEDB0 )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 8))(dword_1DAEDB0);
      dword_1DAEDB0 = nullptr;
    }
    if ( dword_1DAEDB4 )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 8))(dword_1DAEDB4);
      dword_1DAEDB4 = nullptr;
    }
    if ( dword_1DAEDC4 )
    {
      (*(void (__thiscall **)(int, int))(*(_DWORD *)dword_1DAEDC4 + 8))(dword_1DAEDC4, dword_1DAEDC4);
      dword_1DAEDC4 = 0;
    }
    if ( dword_1DAEDC0 )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDC0 + 8))(dword_1DAEDC0);
      dword_1DAEDC0 = nullptr;
    }
    unk_1DAEDCC = 0;
  }
}

