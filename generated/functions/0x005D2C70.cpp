// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2C70 rf_d3d8_bind_textures_and_apply_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, all packed-state selector branches, original-PE device-call immediates and option/cache paths): Cdecl packedWord,stage0Handle,stage1Handle. Nonnegative stage0 handle binds via texture helper0 with immediate-state handling flag1;negative stage0 triggers begin_immediate_buffers(4,3) ONLY when both bytes1E014E5 and1E014E6 are0. Nonnegative stage1 handle binds stage1 with flag1;negative stage1 leaves prior binding intact (no unbind). Then invokes packed-state dispatcher;texture mode0 can separately unbind both stages. No material lookup,automatic missing-second-texture clear,ready guard or rollback. Returns dispatcher incidental AL,not reliable bind/apply status.
char __cdecl rf_d3d8_bind_textures_and_apply_state(int a1, int a2, int a3)
{
  if ( a2 <= -1 )
  {
    if ( !unk_1E014E5 && !unk_1E014E6 )
      rf_renderer_begin_immediate_buffers(4, 3);
  }
  else
  {
    rf_renderer_bind_texture_handle(0, a2, 0, (int)&unk_1E014DC, (int)&unk_1E014D0, 1);
  }
  if ( a3 > -1 )
    rf_renderer_bind_texture_handle(1, a3, 0, (int)&unk_1E014D4, (int)&unk_1E014CC, 1);
  return rf_renderer_apply_packed_render_state(a1);
}

