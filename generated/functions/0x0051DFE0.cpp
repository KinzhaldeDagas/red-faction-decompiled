// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051DFE0 rf_primary_uv_classify_against_cut_epsilon
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl value,cut returnsEAX class:3 if ORDERED cut<value-doubleepsilon (value above cut),1 if ORDERED cut>value+doubleepsilon (below),otherwise2 inclusive epsilon band. Epsilon PE double0.00009999999747378752; subtraction/addition done inx87 before comparison, not storedF32 bounds. Unordered comparison returns2 via TEST AH41/JNZ; no finite check or absolute-value helper.
int __cdecl rf_primary_uv_classify_against_cut_epsilon(float a1, float a2)
{
  if ( a2 < a1 - 0.00009999999747378752 )
    return 3;
  if ( a2 <= a1 + 0.00009999999747378752 )
    return 2;
  return 1;
}

