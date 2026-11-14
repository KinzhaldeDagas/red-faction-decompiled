// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004580D0 rf_shared_noop_destructor_4580d0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): No-op body with no memory access, free, register-dependent work or calls; EAX untouched, declared void/no args. Used as local read-context and scene-base destruction across RF, including VSFX cleanup; ECX values supplied by callers are ignored. Does not release scene-owned pools or receiver. Existing library flag and generic Microsoft repeatable comment retained.
void rf_shared_noop_destructor_4580d0()
{
  ;
}

