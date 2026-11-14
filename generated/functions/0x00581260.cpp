// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581260 rf_renderer_push_instance_transform_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Cdecl two transform arguments. Reads renderer selector187CC9C;only selector102 forwards both unchanged to rf_renderer_push_instance_transform. Other selectors make no transform call. Returns selector on bypass or callee incidental result;not a universal boolean success. Wrapper adds no pointer/stack-depth validation or light-space synchronization.
int __cdecl rf_renderer_push_instance_transform_dispatch(int a1, int a2)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_push_instance_transform(a1, a2);
  return result;
}

