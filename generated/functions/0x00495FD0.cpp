// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495FD0 rf_player_state260_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall260-byte state,returns receiver. Initializes timestamp DWORDs4/8/16/36/40/44/184/252=-1. Calls no-opRGBA50,vector68/152/200,matrix80/116/212 constructors. No writes to
// other scalar,byte,vector,matrix orpadding fields; in particular matrix constructors do not imply identity. No allocation or link registration.
char *__thiscall rf_player_state260_construct(char *this)
{
  rf_timestamp4_construct_invalid((int *)this + 1);
  rf_timestamp4_construct_invalid((int *)this + 2);
  rf_timestamp4_construct_invalid((int *)this + 4);
  rf_timestamp4_construct_invalid((int *)this + 9);
  rf_timestamp4_construct_invalid((int *)this + 10);
  rf_timestamp4_construct_invalid((int *)this + 11);
  rf_rgba8_default_construct_noop(this + 50);
  rf_vector3_default_construct_noop(this + 68);
  rf_matrix3_construct(this + 80);
  rf_matrix3_construct(this + 116);
  rf_vector3_default_construct_noop(this + 152);
  rf_timestamp4_construct_invalid((int *)this + 46);
  rf_vector3_default_construct_noop(this + 200);
  rf_matrix3_construct(this + 212);
  rf_timestamp4_construct_invalid((int *)this + 63);
  return this;
}

