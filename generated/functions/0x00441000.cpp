// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441000 rf_record56_table_clear_names_and_indices
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No-argument void initializer over global56-byte records at6E6730. Signed i starts0 and re-reads global
// count6E6728 on EVERY bound test; count<=0 skips all writes, no capacity/overflow guard. For each record call55FFA0 thiscall RFString assignment with PE empty Cstring633330, then
// set exactly twelve DWORDs at record+8,+12,...,+52 to-1 in increasing order. Does not zero56-byte block, invoke record destructor, allocate table, reset global count, or assume
// RFString assignment clears/reallocates in every prior string state. Earlier assignments/stores survive later fault; no bounds/ownership/validity/authority gate.
void __cdecl rf_record56_table_clear_names_and_indices()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_6E6728; ++i )
  {
    rf_string_assign_from_cstr(&byte_6E6730[56 * i], (char *)&byte_633330);
    unk_6E6738[14 * i] = -1;
    unk_6E673C[14 * i] = -1;
    unk_6E6740[14 * i] = -1;
    unk_6E6744[14 * i] = -1;
    unk_6E6748[14 * i] = -1;
    unk_6E674C[14 * i] = -1;
    unk_6E6750[14 * i] = -1;
    unk_6E6754[14 * i] = -1;
    unk_6E6758[14 * i] = -1;
    unk_6E675C[14 * i] = -1;
    unk_6E6760[14 * i] = -1;
    dword_6E6764[14 * i] = -1;
  }
}

