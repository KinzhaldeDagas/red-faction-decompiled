// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457E60 rf_frontend_release_array6f26ac_and_reverse_motion
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. First517F40 on global6F26AC: fresh helper zeroes count/capacity, deletes nonnull backing and clears pointer, WITHOUT destroying pointed
// elements. After normal return, writes FLOAT6F23E0=-FLOAT661E50 then FLOAT6F23DC=-FLOAT661E60 via FLD/FCHS/FSTP. Does not move current positions or check active/ready flags;
// forwards storage-release EAX despite later x87-only writes. If deletion does not return, velocity writes do not occur; no rollback or object-loop cleanup.
void **rf_frontend_release_array6f26ac_and_reverse_motion()
{
  void **result; // eax

  result = rf_pointer_array_release_storage((void **)dword_6F26AC);
  unk_6F23E0 = -rf_ui_open_transition_speed;
  unk_6F23DC = -flt_661E60;
  return result;
}

