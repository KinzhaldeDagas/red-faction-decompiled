// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DDD30 rf_renderer_draw_solid_face_wire_outlines
// UNREALRED VERIFIED [renderer-lighting-20261028]: Obtains solidface listhead from solid+112 and walks rf_solid_face_next_link. Calls0x5DD870 for everyface,without facevisibility/portal filtering. Returns finalnull listpointer. Uses currentrenderercolor; no change to stateconfiguration here.
int __cdecl rf_renderer_draw_solid_face_wire_outlines(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(a1 + 112));
  for ( i = result; i; i = result )
  {
    rf_renderer_draw_face_wire_outline(a1, i);
    result = rf_solid_face_next_link(i);
  }
  return result;
}

