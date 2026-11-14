// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436440 rf_entity_latest_activity_timestamp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One required entity pointer. Calls literal maximum helper40D600(first=FLOAT+1972,second=FLOAT+1968), stores result float32. Then
// maximum(first=that rounded result,second=FLOAT+1976), stores float32 and reloadsST0. Each max chooses SECOND on unordered as well as ordered>=, so not symmetric NaN-propagating
// maximum; evaluation order and two stores matter. No own current-clock read, elapsed subtraction, field update or finite guard. Existing callers compare global seconds clock minus
// this returned timestamp; broader common meaning of the three activity channels remains unassigned.
double __cdecl rf_entity_latest_activity_timestamp(float *a1)
{
  float v2; // [esp+8h] [ebp-4h]

  v2 = rf_float_maximum_two_values(a1[493], a1[492]);
  return (float)rf_float_maximum_two_values(v2, a1[494]);
}

