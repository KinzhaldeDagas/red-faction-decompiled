// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569300 rf_sound_backend_service_fades_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl no arguments. Calls5C0140 backend fade-service dispatcher then returns its incidental EAX. Dispatcher only services fades when backend ready and mode==1; result is not a normalized success or voice count. Adapter adds no frontend-ready check.
int rf_sound_backend_service_fades_adapter()
{
  return rf_sound_backend_service_fades();
}

