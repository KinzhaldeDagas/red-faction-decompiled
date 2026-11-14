// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469EB0 rf_performance_filter_group_press_apply
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Hit-test6F6A28/count6F6AA8;nonnegative hit/nonnull child callback32 getsTWO original(x,y). Selected filterDWORD6F6FC4 anynonzero
// ->playerBYTE3912=1/backend mip-filter setterarg0;zero ->BYTE0/backendarg1. Then apply_preset(3) commits whole UI tuple and repeats filter backend call. Choices are
// Trilinear0,Bilinear1,loaded from unsigned playerBYTE without validation. No own index/player/bounds/changed-choice guard,save or sound. Keyboard calls leaf469F60/F90 directly and
// does not run this apply wrapper.
int __cdecl rf_performance_filter_group_press_apply(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F6A28, dword_6F6AA8);
  if ( result >= 0 && *(_DWORD *)(unk_6F6A28[result] + 32) )
  {
    (*(void (__cdecl **)(int, int))(unk_6F6A28[result] + 32))(physical_x, physical_y);
    if ( unk_6F6FC4 )
    {
      *(_BYTE *)(rf_local_fpgun_player + 3912) = 1;
      rf_renderer_set_mip_filter_backend_dispatch(0);
    }
    else
    {
      *(_BYTE *)(rf_local_fpgun_player + 3912) = 0;
      rf_renderer_set_mip_filter_backend_dispatch(1);
    }
    return rf_performance_options_apply_preset(3);
  }
  return result;
}

