// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EF20 rf_geomod_face_flag_08000000_is_set
// UNREALRED VERIFIED [geomod-classification-20261028] Exact accessor for metadata mask 0x08000000. Used as a flood barrier at 0x532FC0. The name describes the bit predicate only; it does not conflate this mask with Boolean operand bit 0x800000.
bool __thiscall rf_geomod_face_flag_08000000_is_set(_DWORD *this)
{
  return (*this & 0x8000000) != 0;
}

