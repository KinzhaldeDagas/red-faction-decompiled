// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580120 rf_renderer_submit_room_faces_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards room/context DWORD,vector pointer,and orientation DWORD plus the low byte of a FOURTH DWORD argument to the room-face submitter;otherwise returns backend value without submission. No input validation here;nominal integer not uniformly meaningful status.
// UNREALRED VERIFIED (2026-11-11; native ABI correction): 0x580134 reads [EBP+14h] with MOVZX, pushes it before three other DWORDs, and pops16 bytes after 0x580145. Caller 0x418743 also pushes/pops four DWORDs. Corrected wrapper prototype includes alpha. Backend 0x5D75A0 reads only first three arguments, so alpha is forwarded but ultimately unused; its existing three-argument prototype is retained.
int __cdecl rf_renderer_submit_room_faces_backend_wrapper(
        int solid,
        float *position,
        int orientation,
        unsigned __int8 alpha)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_submit_room_faces(solid, position, orientation);
  return result;
}

