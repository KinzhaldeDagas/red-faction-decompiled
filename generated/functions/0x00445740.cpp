// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445740 sub_445740
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Movement-mode registry lookup by native index: index>=16 or unloaded byte at6E6B90[index*32] selects slot0; it does NOT require slot0 to be loaded. Writes selected index to global6E6D90, returns pointer to that32-byte slot. This decoded missing-known-mode fallback differs from445780 unknown-name null. Global selected-index/debug history is separate from per-entity movement ownership.
// UNREALRED VERIFIED [combat-panic-movement-20261111-clarified]: Undefined-record precision:4451D0 clears loaded bytes, and445740 may still return the slot0 pointer with no authored row. A loaded-byte test does not establish the complete descriptor payload. Fresh IDA get_bytes of this registry yielded FF; do not treat a value read alone as proof of initialized runtime data. The implemented physical host adapter explicitly declines an undefined descriptor rather than fabricate movement references or generic run motion.
char *__cdecl sub_445740(unsigned int a1)
{
  if ( a1 >= 0x10 || !unk_6E6B90[32 * a1] )
    a1 = 0;
  unk_6E6D90 = a1;
  return &unk_6E6B90[32 * a1];
}

