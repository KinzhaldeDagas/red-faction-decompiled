// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495F30 rf_player_destroy_owned_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall Player destructor. Destroys embedded3740-state strings at228,then name RFString8;unwind also destroys name. No receiver free,list unlink,score/net pointee
// destruction,entity delete or scalar reset. Live scalar-deleting destructor and EH snapshot cleanup handle outer storage separately.
void __thiscall rf_player_destroy_owned_members(char *this)
{
  rf_player_state3740_destroy(this + 228);
  rf_string_destroy_buffer(this + 8);
}

