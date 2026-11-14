// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505D30 rf_trigger_set_global_activation_suppression
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): No arguments,void. Only store is DWORD90B508=1; no calls, command-line/argv setup, object iteration or pause-state change. False ___setargv library identification corrected. Verified readers505360 rejects central trigger commit ONLY when this global equals EXACT1; startup5052B0 in that mode runs flag8-link filtering505D40 instead of normal startup commits. Benchmark panel515070 case5 sets suppression after successful level load. Does not disable every lower-level trigger/event path or freeze simulation.
void rf_trigger_set_global_activation_suppression()
{
  unk_90B508 = 1;
}

