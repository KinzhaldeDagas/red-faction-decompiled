// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D6BA0 rf_renderer_draw_face_debug_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, unowned renderer entry recovery, camera-plane beam geometry and original PE bytes): Recovered93-byte cdecl fourDWORD forwarding dispatcher. If either globalA4208C orA42090 nonzero,calls rf_renderer_draw_face_debug_colors_and_edges with four arguments unchanged. Otherwise if A420A0 orA4209C nonzero,calls rf_renderer_draw_face_debug_texture_channel unchanged. Thus color/edge path has precedence when both groups active;all flags clear performs no draw. EAX is forwarded callee result or untouched value on no-draw path,not reliable success. No pointers/counts/state validation;does not choose normal face rendering.
int __cdecl rf_renderer_draw_face_debug_dispatch(int a1, int a2, int a3, int a4)
{
  int result; // eax

  if ( dword_A4208C || dword_A42090 )
    return (int)rf_renderer_draw_face_debug_colors_and_edges(a1, a2, a3, a4);
  if ( dword_A420A0 || dword_A4209C )
    return (int)rf_renderer_draw_face_debug_texture_channel(a1, a2, a3, a4);
  return result;
}

