// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495FB0 rf_player_state3740_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall wrapper delegates496100(receiver) to destroy all128 embedded RFStrings. No receiver free,raw pointer release,scalar reset or owned-name handling outside this aggregate.
void __thiscall rf_player_state3740_destroy(void *this)
{
  rf_player_string_state3664_destroy((int)this);
}

