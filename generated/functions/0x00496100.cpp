// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496100 rf_player_string_state3664_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall prefix destructor. EH vector destructor iterator(receiver12,stride28,count128,496150),thus all128 record RFStrings destroyed independent of active entries. No receiver
// free or clearing of other fields. Does not use an allocation cookie for this inline array.
void __thiscall rf_player_string_state3664_destroy(char *this)
{
  `eh vector destructor iterator'(this + 12, 0x1Cu, 128, (void (__thiscall *)(void *))rf_player_string_record28_destroy);
}

