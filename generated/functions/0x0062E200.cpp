// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062E200 rf_renderer_context_static_construct_colors_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): Standalone cdecl noargs wrapper. Loads ECX=global renderer context187CC90,calls573D90,then returns. Callee only invokes two no-op color-member constructors;this wrapper therefore writes no context bytes and does not perform renderer/backend initialization. EAX incidentally contains receiver returned by callee;no separate success value. Adjacent startup code is a different function and not part of this boundary.
void __cdecl rf_renderer_context_static_construct_colors_noop()
{
  rf_renderer_context_construct_noop_color_members(&dword_187CC90);
}

