// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434150 rf_ai_scripted_route_admit
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Mode10 route admission is entityresolve→rawspeedEntity8C0>0.001→40E030 routebuild. Native success already refreshes secondary1 for mode3/10; caller406130 refreshes1 again, so do not dedupe equal state timestamps. Failure-1 differs from a host missing provider.
// UNREALRED VERIFIED [combat-directed-consumers-20261111] Raw speedEntity8C0 is binary32, compared against DOUBLE literal0.001 at632FF8 (bytesfca9f1d24d62503f). Preserve double promotion: binary32 0.001f is slightly ABOVE this threshold and must pass; replacing comparison with0.001f changes admission at this exact boundary.
int __cdecl rf_ai_scripted_route_admit(int a1, float *a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_entity_resolve_handle(a1);
  if ( !v3 )
    return -1;
  if ( *(float *)(v3 + 2240) <= 0.001 )
    return -1;
  if ( !rf_ai_route_build(*(_DWORD *)(v3 + 44), a2) )
    return -1;
  if ( *(_DWORD *)(v3 + 1312) == 3 || *(_DWORD *)(v3 + 1312) == 10 )
    rf_ai_secondary_state_write(v3 + 672, 1);
  else
    rf_ai_numeric_mode_write((_DWORD *)(v3 + 672), 4, -1, -1);
  return 0;
}

