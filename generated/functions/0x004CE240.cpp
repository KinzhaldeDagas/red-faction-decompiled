// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE240 rf_particle_detached_list_reset_empty
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl no-argument reset: writes detached sentinel 0x867C60 to its next +0 and prev +4 and returns EAX=0. Native XOR EAX,EAX/JNZ forms an unreachable loop back edge. Does not
// walk/recycle existing nodes, clear their emitter pointers, repair orphan links, or adjust pool active counts. Direct caller is sub_4CAF00 at 0x4CAF06.
int rf_particle_detached_list_reset_empty()
{
  dword_867C60 = (int)&dword_867C60;
  unk_867C64 = &dword_867C60;
  return 0;
}

