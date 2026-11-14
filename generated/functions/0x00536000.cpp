// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536000 rf_geomod_face_ray_query_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall nominal query constructor, returns receiverEAX, no stack args. Calls413010 on receiver (which invokes4F2700 no-op vector defaults at0 and12), then4F2700 on receiver+24. All three vector defaults are verified no-ops: this constructor initializes NO query bytes, including hit pointer, distance, flags or padding. Call535B40 supplies actual query state before use. Shared413010 name reflects another caller role, not an allocation or a44-byte initialization in this body.
char *__thiscall rf_geomod_face_ray_query_init(char *this)
{
  rf_force_sample44_construct_vectors_noop(this);
  rf_vector3_default_construct_noop(this + 24);
  return this;
}

