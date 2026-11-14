// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C7A0 rf_record_destroy_strings0_8_and_pair24
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall ECX record, no stack args, plainRET, compiler SEH cleanup frame. Normal path calls EH vector
// destructor6066BD(record+24,stride12,count2,callback4873C0); callback destroys only RFString at each record start. Then destroy RFString buffer at record+8, then record+0, advancing
// unwind states1,0,-1. Includes cleanup thunks622EC0 and622EC8 for strings0/8 plus622ED3 C++ frame-handler/security-cookie dispatcher; all chunks belong to this function and were
// PE-matched. No scalar/other-field reset, array storage/containing allocation free or normalized return in this body; it is neither a52-byte array walk nor a bitmap-handle release
// despite the shared destructor callback name. Record nonNULL is assumed.
void __thiscall rf_record_destroy_strings0_8_and_pair24(char *this)
{
  `eh vector destructor iterator'(this + 24, 0xCu, 2, rf_glare_definition52_destroy_name_member);
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

