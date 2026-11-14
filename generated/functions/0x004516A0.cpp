// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004516A0 rf_binding_context_append_named_triplet_record
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,Cstring,raw metadataDWORD,LOWWORD code0,LOWWORD code1,LOWWORD code2), fullEAX old
// count or-1. Snapshot signed context DWORD3596; ONLY count>=128 rejects without writes. Negative count is admitted and raw28*count can address before records.
// Entry=context+12+28*oldCount. In order write WORDs at entry0/2/4 from low16 arguments, DWORD metadata at8, assign Cstring into existing RFString at12 via55FFA0, then RE-READ
// original argument lowWORDs and write duplicate triplet at20/22/24. Finally RE-READ current context3596, increment/store wrapped32, return captured oldCount. No
// duplicate/name/NULL/nonnegative/constructor check, record memset, count rollback or string-success test; padding bytes6..7 and26..27 retain old contents. String assignment is not
// construction/ownership transfer of input Cstring. No unsupported active/default meaning is assigned to the two equal triplets; source aliasing and helper mutations preserve the
// literal store/read order.
int __cdecl rf_binding_context_append_named_triplet_record(
        int a1,
        char *Source,
        int a3,
        __int16 a4,
        __int16 a5,
        __int16 a6)
{
  int v7; // [esp+0h] [ebp-8h]
  int v8; // [esp+4h] [ebp-4h]

  v7 = *(_DWORD *)(a1 + 3596);
  if ( v7 >= 128 )
    return -1;
  v8 = a1 + 28 * v7 + 12;
  *(_WORD *)v8 = a4;
  *(_WORD *)(v8 + 2) = a5;
  *(_WORD *)(v8 + 4) = a6;
  *(_DWORD *)(v8 + 8) = a3;
  rf_string_assign_from_cstr((_DWORD *)(a1 + 28 * v7 + 24), Source);
  *(_WORD *)(v8 + 20) = a4;
  *(_WORD *)(v8 + 22) = a5;
  *(_WORD *)(v8 + 24) = a6;
  ++*(_DWORD *)(a1 + 3596);
  return v7;
}

