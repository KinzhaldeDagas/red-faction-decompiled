// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050B080 rf_room_try_break_first_glass_face
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Cdecl room/list owner,position pointer,direction pointer,selector low byte. Reads first face from owner+40 via486DE0; if nonzero calls4C70E0(face,position,direction,zero-extended selector BYTE) and returns its AL. NULL head returns zero from getter. Despite an apparent face-next loop body at50B094, entry skips to head test and first call UNCONDITIONALLY jumps to return50B0C9; the next-face path is unreachable from normal entry. Does not try later faces when first face cannot break, or iterate after success. No owner/point/direction NULL guard.
char __cdecl rf_room_try_break_first_glass_face(int a1, float *a2, float *a3, char a4)
{
  _DWORD *first_dword; // eax

  first_dword = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 40));
  if ( first_dword )
    LOBYTE(first_dword) = rf_glass_face_break_directional(first_dword, a2, a3, a4);
  return (char)first_dword;
}

