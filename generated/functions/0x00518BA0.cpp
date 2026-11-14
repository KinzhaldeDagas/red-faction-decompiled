// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518BA0 rf_nav_route_append_node_first_four
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Cdecl request,node. If signed output count52<4,writes node to buffer56+4*count and postincrements count. Returns request pointer bits in EAX in both branches. No count>=0 or buffer check;negative count writes before buffer. Does not grow storage,shift/truncate existing entries or report dropped nodes.
int __cdecl rf_nav_route_append_node_first_four(int a1, int a2)
{
  int result; // eax

  result = a1;
  if ( *(int *)(a1 + 52) < 4 )
  {
    *(_DWORD *)(*(_DWORD *)(a1 + 56) + 4 * (*(_DWORD *)(a1 + 52))++) = a2;
    return a1;
  }
  return result;
}

