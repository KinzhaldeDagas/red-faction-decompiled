// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CF010 rf_console_set_underwater_particle_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Recovered standalone original function [0x4CF010,0x4CF040), cdecl noargs, no currently recorded incoming xrefs. If console argument count DWORD 0x1809818 is nonzero, invokes
// argument reader/validator with type mask8 and argument index0. Then uses shared signed DWORD result 0x180981C: when <=1024, stores it verbatim into active underwater-particle count
// 0x662DFC. No lower bound; negative values are accepted and suppress the signed i<count render loop. Values >1024 leave count unchanged. Does not initialize newly enabled records,
// clamp an existing count, print, or return a stable success value.
void __cdecl rf_console_set_underwater_particle_count()
{
  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(8, 0);
    if ( dword_180981C <= 1024 )
      dword_662DFC = dword_180981C;
  }
}

