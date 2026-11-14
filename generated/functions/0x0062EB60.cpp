// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EB60 rf_glare_definition_array64_destroy_members_atexit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): No-argument atexit adapter. Calls EH vector destructor iterator with BASE680DD8,STRIDE52,COUNT64,callback0x4873C0. Destroys name RFString in ALL64 constructed definition slots, independent of live definition count0x680AE0; no outer static-array free or bitmap release. Separate from0x419A30 live-name clearing. Native iterator governs reverse destruction/unwind order.
void rf_glare_definition_array64_destroy_members_atexit()
{
  `eh vector destructor iterator'(byte_680DD8, 0x34u, 64, rf_glare_definition52_destroy_name_member);
}

