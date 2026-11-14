// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455E40 rf_frontend_release_array6f21ac_and_reverse_motion
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. First517F40 on global6F21AC: fresh helper zeroes count/capacity, deletes nonnull backing and clears pointer, WITHOUT destroying pointed
// elements. After normal return, writes FLOAT6F1F94=-FLOAT661E50 then FLOAT6F1F90=-FLOAT661E60 via FLD/FCHS/FSTP. Does not move current positions or check active/ready flags;
// forwards storage-release EAX despite later x87-only writes. If deletion does not return, velocity writes do not occur; no rollback or object-loop cleanup.
void **rf_frontend_release_array6f21ac_and_reverse_motion()
{
  void **result; // eax

  result = rf_pointer_array_release_storage((void **)dword_6F21AC);
  unk_6F1F94 = -rf_ui_open_transition_speed;
  unk_6F1F90 = -flt_661E60;
  return result;
}

