// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581290 rf_renderer_pop_instance_transform_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): No-argument wrapper:renderer selector187CC9C==102 calls rf_renderer_pop_instance_transform and forwards result,else returns selector unchanged. No pop for other backends,underflow check or automatic light resynchronization. Paired by recovered face renderer when both optional transform arguments supplied.
int rf_renderer_pop_instance_transform_dispatch()
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_pop_instance_transform();
  return result;
}

