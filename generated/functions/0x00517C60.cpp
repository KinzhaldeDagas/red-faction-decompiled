// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517C60 sub_517C60
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Recomputes room byte +2 as all-faces-invisible: clears it, scans the ordered room face list at +40, and returns immediately on any face without metadata flag 0x2000 (0x517E20). If no such face exists, including an empty list, sets byte +2 to 1. Does not modify ordinary/detail or referenced-room arrays. The extra world argument is unused.
char __thiscall sub_517C60(_BYTE *this, int a2)
{
  char result; // al
  int i; // [esp+4h] [ebp-4h]

  *(this + 2) = 0;
  for ( i = rf_receiver_get_first_dword(this + 40); i; i = rf_face_next_room_link(i) )
  {
    result = rf_face_is_invisible((_DWORD *)(i + 40));
    if ( !result )
      return result;
  }
  *(this + 2) = 1;
  return (char)this;
}

