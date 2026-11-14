// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446EA0 rf_foley_free_variant_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. For a signed local index starting0, re-reads LIVE DWORD6EDC30 on every condition and calls CRT free on raw
// DWORD[6E6E58+44*index], then increments with native32-bit arithmetic. A nonpositive count performs no frees. No capacity, pointer or duplicate-allocation check, and no
// pointer/count/row clearing after release; a repeated call while those fields remain unchanged can release the same allocations again. This releases only variant arrays, not the
// static44-byte row storage. Return is void; free's EAX is not promoted to a status.
void __cdecl rf_foley_free_variant_arrays()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_6EDC30; ++i )
    free((void *)dword_6E6E58[11 * i]);
}

