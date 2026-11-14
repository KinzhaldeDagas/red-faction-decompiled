// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535A30 rf_face_prepend_decal_polygon_link
// UNREALRED VERIFIED [decal-face-links-20261028]: Sets polygon+1328 to current face head+76 then stores polygon as new head. Returns face. Does not set polygon face-owner+1312, update decal list/count, set face flags or prevent duplicate/cyclic insertion; caller handles those fields.
_DWORD *__thiscall rf_face_prepend_decal_polygon_link(_DWORD *this, int a2)
{
  *(_DWORD *)(a2 + 1328) = *(this + 19);
  *(this + 19) = a2;
  return this;
}

