// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005155F0 rf_benchmark_update_and_render_frame
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdecl noargs. Calls main level-update manager444D30,then view preparation442950,then442BC0(local_fpgun_player,0),forwarding lastEAX. No timer sampling,benchmark statistic updates,own playerNULLguard,present/swap or rotation update in this body. Dispatcher515070 invokes BEFORE its entity rotation-field write and FPS accumulation. Inherited442950 thiscall receiver is incidental/unused by observed body;this wrapper does not setECX for it.
void rf_benchmark_update_and_render_frame()
{
  sub_444D30();
  rf_render_local_player_auxiliary_views_and_visibility_union();
  rf_player_render_view(rf_local_fpgun_player, 0);
}

