// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA820 rf_glass_shard200_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall constructor for a 200-byte glass shard; returns the receiver. Invokes no-op vector constructors at +8,+64,+76, the matrix row constructor at +20, no-op RGBA constructor at
// +56, and four no-op 20-byte corner constructors at +116. The two timestamp constructors write -1 to DWORD +108 and +112. This does not initialize list links, radius +92, bounce
// budget +96, attachment +100, room +104, corner payload/UVs, or flags +196; those belong to later initialization/allocation paths.
char *__thiscall rf_glass_shard200_construct(char *this)
{
  rf_vector3_default_construct_noop(this + 8);
  rf_matrix3_construct(this + 20);
  rf_rgba8_default_construct_noop(this + 56);
  rf_vector3_default_construct_noop(this + 64);
  rf_vector3_default_construct_noop(this + 76);
  rf_timestamp4_construct_invalid((int *)this + 27);
  rf_timestamp4_construct_invalid((int *)this + 28);
  rf_vector_construct_no_unwind(this + 116, 0x14u, 4, rf_vector_prefix_construct_noop);
  return this;
}

