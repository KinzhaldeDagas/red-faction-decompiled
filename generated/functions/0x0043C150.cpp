// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C150 rf_entity_definition_field436_is_one
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl index, canonical AL0/1. Signed index<0 or index>=75 returns0; accepted0..74 uses5396-byte definition
// stride, returns1 only when DWORD at6836FC+5396*index (definition base683548+436) is EXACT1. Other positive/nonzero values return0. Uses fixed capacity75, not live definition
// count681E14; no string/runtime entity or current level state read and no mutation.
bool __cdecl rf_entity_definition_field436_is_one(unsigned int a1)
{
  return a1 <= 0x4A && unk_6836FC[1349 * a1] == 1;
}

