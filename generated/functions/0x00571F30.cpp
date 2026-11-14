// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571F30 rf_renderer_set_pending_texture_handles
// UNREALRED VERIFIED [reflection-binding-20260903]: Stores pending primary and secondary texture handles in globals 0x0187CCE8/0x0187CCEC. Immediate polygon drawing later consumes the primary handle for D3D stage 0; this function performs no backend bind itself.
int __cdecl rf_renderer_set_pending_texture_handles(int a1, int a2)
{
  unk_187CCE8 = a1;
  unk_187CCEC = a2;
  return a1;
}

