// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00428950 sub_428950
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Thin wrapper calls428970 body-state transition only. It does not prove speech action cleanup or AI dispatch. Speech action41/42 requests and common active-action lifetime belong to the existing action owner; do not add guessed tracked-action removal here.
void __cdecl sub_428950(int a1)
{
  rf_entity_update_body_state_transition(a1);
}

