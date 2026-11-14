// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048BF80 rf_moving_solid_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Thiscall constructor, returns receiver after common_object_construct_members only. Does not initialize geometry pointer660 or link fields652/656, create geometry or register list
// membership. Object allocator invokes it for moving solids; static initializer62C278 also passes moving-solid sentinel704940.
char *__thiscall rf_moving_solid_construct_members(char *this)
{
  rf_common_object_construct_members(this);
  return this;
}

