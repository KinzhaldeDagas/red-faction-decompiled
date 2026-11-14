// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005182C0 rf_nav_node_admits_request_dimensions
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Cdecl node,request. If request BYTE32==1 and node DWORD64!=0,returnsfalse. Then requires request radius24<=node clearance28 and request height28<=node clearance32. Raw TEST AH,41h/JNZ accepts unordered as well as ordered<= in BOTH comparisons;NaN is not rejected. No geometry query or mutation. Node flag64 is separate from working flags52..54. Earlier combat eligibility note retained in518210.
bool __cdecl rf_nav_node_admits_request_dimensions(int a1, int a2)
{
  if ( *(_BYTE *)(a2 + 32) == 1 && *(_DWORD *)(a1 + 64) )
    return 0;
  if ( *(float *)(a2 + 24) <= (double)*(float *)(a1 + 28) )
    return *(float *)(a2 + 28) <= (double)*(float *)(a1 + 32);
  return 0;
}

