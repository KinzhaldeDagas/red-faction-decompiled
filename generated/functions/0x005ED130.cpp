// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED130 rf_renderer_append_world_face_packet_wrapper
// UNREALRED VERIFIED [face-batch-20261028]: Directly delegates seven arguments to0x5EAA80. No extra validation,state mutation or packet allocation policy.
int *__cdecl rf_renderer_append_world_face_packet_wrapper(int *a1, void *Src, int a3, int a4, int a5, int a6, int a7)
{
  return rf_renderer_append_world_face_packet(a1, Src, a3, a4, a5, a6, a7);
}

