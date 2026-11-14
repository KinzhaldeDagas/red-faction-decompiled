// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498570 rf_ctf_aux_timer77D734_arm_now
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Recovered original no-argument function [498570,498581). Unconditionally calls rf_replicator_arm_milliseconds on77D734 with signed offset0. Timer is distinct from deferred sound
// timer77D730 and shared pickup/capture cooldown77D72C. No own mode, authority or initialization guard. No static incoming xrefs currently; timer77D734 references observed only here
// and its constructor/reset initialization, so no stronger periodic/send purpose is established. Native RET is caller-cleaned; no stable semantic return value.
void __cdecl rf_ctf_aux_timer77D734_arm_now()
{
  rf_replicator_arm_milliseconds(&unk_77D734, 0);
}

