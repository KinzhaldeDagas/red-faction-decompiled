// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA7C0 rf_face_metadata_portal_index_signed16
// UNREALRED VERIFIED [combat-particle-contact-20261104]: Reads signed16 at receiver+12 (metadata+12; glass caller supplies face+40, so overall face+52); values<2 have no portal (-1), otherwise portal array index=value-2. This serialized/runtime portal value is distinct from room ID.
int __thiscall rf_face_metadata_portal_index_signed16(__int16 *this)
{
  if ( *(this + 6) < 2 )
    return -1;
  else
    return *(this + 6) - 2;
}

