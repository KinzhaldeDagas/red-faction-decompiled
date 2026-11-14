// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2A40 rf_player_record_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Thiscall receiver with one caller-supplied flags DWORD, RET4. Always call495F30(receiver), whose body destroys embedded member+228 and RFString+8. If LOW flags mask1 set, operator delete(receiver), then return original receiver bits EAX even if freed. No NULL guard or additional lifecycle cleanup in wrapper. Both native callers in player creation failure/removal pass1; not an allocation or array destructor.
char *__thiscall rf_player_record_scalar_deleting_destructor(char *this, char a2)
{
  rf_player_destroy_owned_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

