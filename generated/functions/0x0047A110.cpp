// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A110 rf_room_is_authored_sky
// UNREALRED VERIFIED [sky-face-render-contract] Returns the authored room byte at Room+0x01 without reinterpretation. The world sky selector uses this exact predicate and takes the first matching room.
char __thiscall rf_room_is_authored_sky(_BYTE *this)
{
  return *(this + 1);
}

