// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603810 rf_jpeg_downsample_fullsize
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:fullsize_downsample matched): Copies max_v rows of image_width bytes to output, then pads the OUTPUT right edge to 8*width_in_blocks. Selected when component sampling equals the maximum in both axes. Does not modify input padding.
_BYTE *__cdecl rf_jpeg_downsample_fullsize(int a1, int a2, int a3, int a4)
{
  rf_jpeg_jcopy_sample_rows(a3, 0, a4, 0, *(_DWORD *)(a1 + 232), *(_DWORD *)(a1 + 28));
  return rf_jpeg_downsample_expand_right_edge(a4, *(_DWORD *)(a1 + 232), *(_DWORD *)(a1 + 28), 8 * *(_DWORD *)(a2 + 28));
}

