// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564F90 rf_vfx_start_instance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,action,floatValue,byteFlag) forwards562B10. Scene ignores action and float magnitude except zero/nonzero, clears draining and sets loop bit from byteFlag low1 on nonzero branch. Not a generic playback-rate assignment.
void __cdecl rf_vfx_start_instance(int *a1, int a2, float a3, char a4)
{
  rf_model_handle_start_action_or_scene(a1, a2, a3, a4);
}

