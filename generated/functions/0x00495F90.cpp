// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495F90 rf_player_state3740_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall wrapper around4960D0(receiver),returns receiver. Constructs only128 embedded28-byte record strings in prefix; does not initialize 21 trailing byte flags,raw blocks,scalars
// or padding of3740-byte aggregate.
void *__thiscall rf_player_state3740_construct(void *this)
{
  rf_player_string_state3664_construct((int)this);
  return this;
}

