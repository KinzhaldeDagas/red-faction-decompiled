// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041FDD0 rf_ai_behavior_name_to_code
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(required RFString object pointer), full EAX integer result. Calls5609B0(object,literal) in order: exact case-insensitive
// none->0,evasive->1,stand_ground->2,direct->3; first ANY nonzero returnedAL ends lookup. No match returns0, indistinguishable from none. Input is RFString extent/buffer object, NOT
// raw char pointer. Delegate uses stored extent and whole-buffer CRT_stricmp with no trimming/prefix matching; valid empty RFString fails all four nonempty literals and returns0. No
// own pointer/buffer validation, allocation, state mutation, fallback keyword, logging or range clamp; malformed/null object follows delegate dereferences. Does not parse a numeric
// string into a behavior code.
int __cdecl rf_ai_behavior_name_to_code(int a1)
{
  if ( rf_string_equals_case_insensitive(a1, "none") )
    return 0;
  if ( rf_string_equals_case_insensitive(a1, "evasive") )
    return 1;
  if ( rf_string_equals_case_insensitive(a1, "stand_ground") )
    return 2;
  if ( rf_string_equals_case_insensitive(a1, "direct") )
    return 3;
  return 0;
}

