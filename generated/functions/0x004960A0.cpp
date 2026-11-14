// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004960A0 rf_player_pose60_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall embedded60-byte pose,returns receiver. Calls no-op vector0 andmatrix12 constructors; no own payload stores and no initialization of trailing DWORD48/FLOAT52/56. Not an
// identity/zero pose initializer.
char *__thiscall rf_player_pose60_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_matrix3_construct(this + 12);
  return this;
}

