// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580330 rf_renderer_four_branch_ribbon_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards two DWORDs and byte flag to verified four-branch textured-or-line ribbon renderer;otherwise returns backend integer cast to pointer. Existing pointer result is not ownership of a newly allocated object or reliable status.
int *__cdecl rf_renderer_four_branch_ribbon_backend_wrapper(int a1, int a2, char a3)
{
  int *result; // eax

  result = (int *)dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_four_branch_textured_or_line_ribbon(a1, a2, a3);
  return result;
}

