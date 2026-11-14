// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B880 rf_rfl_light_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Thiscall152-byte light constructor, returns receiver. Constructs empty RFString4, calls no-op vector12 and matrix24 constructors. Does not initialize id0,
// scalar/profile/shape/color/flag fields60..146, renderer handle148 or elapsed140; allocator47B440 separately initializes last two. Constructor unwind destroys RFString4. No own
// allocation or renderer creation.
int __thiscall rf_rfl_light_construct(int this)
{
  rf_string_construct_empty((_DWORD *)(this + 4));
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_matrix3_construct((char *)(this + 24));
  return this;
}

