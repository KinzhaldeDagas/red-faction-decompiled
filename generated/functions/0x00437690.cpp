// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437690 rf_object_is_use_vehicle
// UNREALRED VERIFIED [mission-startup-20261020] Trigger NPC policy4 combines this Use vehicle classification predicate with0x4BCF40 player association. It is not merely any NPC or any entity. Vehicle attachment flag0x80 eligibility is a different predicate.
bool __cdecl rf_object_is_use_vehicle(_DWORD *a1)
{
  return a1 && rf_object_get_use_classification(a1) == 1;
}

