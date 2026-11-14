// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEE80 rf_particle_emitter_extent_prepare_disabled_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl no-argument native NO-OP: original instruction 0x4CEE86 unconditionally jumps to epilogue 0x4CEEE1, before every global read, vector constructor, list traversal and helper
// call. Thus normal entry has no gameplay/rendering writes or calls, regardless of byte 0x662DF4. The unreachable body would walk active emitters via +328, admit signed parent/index
// +4>=0, and call source-frame helper 0x4CD460 with position output emitter+164 and a local direction output. Do not resurrect that dead origin preparation merely because it remains
// disassembled in the binary. Caller sub_444D30 invokes this entry at 0x444F27.
void rf_particle_emitter_extent_prepare_disabled_noop()
{
  ;
}

