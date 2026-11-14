// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495E60 rf_player_construct_owned_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall4612-byte Player constructor; native EAX receiver though saved void prototype retained. Constructs empty RFString8,no-op vector28;invalid timestamp DWORDs60/184/188/192=-1.
// Constructs embedded3740 state228,260 state3968,60 pose4244,no-opRGBA4304. Prefix construction builds128 record strings;260-state ctor sets eight timestamp fields,other
// vector/matrix/color constructors are no-op. Does not zero whole player,initialize next/prev,score pointer44,net4608 or latent zoom4428. Unwind destroys constructed nested strings
// and name only. Used for live Player and scoreboard snapshot storage.
void __thiscall rf_player_construct_owned_members(char *this)
{
  rf_string_construct_empty((_DWORD *)this + 2);
  rf_vector3_default_construct_noop(this + 28);
  rf_timestamp4_construct_invalid((int *)this + 15);
  rf_timestamp4_construct_invalid((int *)this + 46);
  rf_timestamp4_construct_invalid((int *)this + 47);
  rf_timestamp4_construct_invalid((int *)this + 48);
  rf_player_state3740_construct(this + 228);
  rf_player_state260_construct(this + 3968);
  rf_player_pose60_construct_noop(this + 4244);
  rf_rgba8_default_construct_noop(this + 4304);
}

