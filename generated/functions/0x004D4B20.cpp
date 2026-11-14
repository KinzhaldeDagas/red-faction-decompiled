// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D4B20 rf_face_is_portal
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Portal predicate reads signed16 at this+0C, where collision caller passes Face+28hex; therefore raw Face+34hex marker>0 is the complete predicate. No independent faceflag20 check. Negative markers and zero are nonportals.
bool __thiscall rf_face_is_portal(__int16 *this)
{
  return *(this + 6) > 0;
}

