// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411910 rf_camera_slot_copy_position_and_vectorE4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required slot pointer,required source float[3]). First assigns source into camera(*slot)+228, then re-reads slot camera
// pointer AND source and assigns source into camera+60. Both assignments40CDF0 use ECX persistent destination, first stack pointer to a distinct LOCAL float[3] copy-result, second
// stack source pointer, RET8. No source snapshot across assignments, alias/overlap protection, room/cache refresh, orientation update or guards. Final EAX is pointer to the second
// LOCAL copy-result (EBP-24), whose lifetime ends on return; it is NOT camera+60, source, or a success code.
float *__cdecl rf_camera_slot_copy_position_and_vectorE4(int a1, float *source)
{
  float v3[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  rf_vector_copy((float *)(*(_DWORD *)a1 + 228), copy_result, source);
  return rf_vector_copy((float *)(*(_DWORD *)a1 + 60), v3, source);
}

