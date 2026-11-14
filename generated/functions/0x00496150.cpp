// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496150 rf_player_string_record28_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall28-byte record destructor callback. Destroys RFString12 only; no receiver free,scalar clearing orDWORD8 pointee release. Used by128-record inline-array constructor unwind
// and destructor iterator.
void __thiscall rf_player_string_record28_destroy(char *this)
{
  rf_string_destroy_buffer(this + 12);
}

