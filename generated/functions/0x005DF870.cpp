// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF870 rf_renderer_depth_from_reciprocal_wrapper
// UNREALRED VERIFIED [face-batch-20261028]: Actual result is x87 FLOAT despite current void decompiler prototype. Ignores first stack argument,forwards second float to0x5A41B0 and leaves return inST0. Face callers immediately FSTP this value into screen vertex depth+8. No z-dependent formula beyond scaling supplied reciprocal value; types left unchanged.
void __cdecl rf_renderer_depth_from_reciprocal_wrapper(int a1, float a2)
{
  rf_renderer_scale_reciprocal_depth(a2);
}

