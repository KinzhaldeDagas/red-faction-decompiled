// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004873C0 rf_glare_definition52_destroy_name_member
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall record, no stack args. Only destroys RFString buffer at record+0, no bitmap handle release, scalar/color reset, containing allocation free or count update. Used as destructor callback for64 records of52-byte stride in static glare-definition storage. Distinct from shutdown name-empty assignment0x419A30.
void __thiscall rf_glare_definition52_destroy_name_member(void *this)
{
  rf_string_destroy_buffer(this);
}

