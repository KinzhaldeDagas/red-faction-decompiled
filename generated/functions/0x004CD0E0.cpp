// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD0E0 rf_particle_render_billboard_callback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Game-specific cdecl one-argument callback forwarding particle pointer unchanged to rf_particle_render_billboard at 0x4CA8D0. Native wrapper pushes exactly one argument,
// caller-cleans 4 bytes, and preserves callee EAX through return. Referenced as callback by rf_particle_submit_global_lists_for_room at 0x4CD046 and 0x4CD0A3. Prior
// unknown_libname_12 / Microsoft runtime identification and FUNC_LIB classification are false; this wrapper belongs to RF particle rendering. No duplicate rendering logic or
// ownership mutation here.
char __cdecl rf_particle_render_billboard_callback(int a1)
{
  return rf_particle_render_billboard(a1);
}

