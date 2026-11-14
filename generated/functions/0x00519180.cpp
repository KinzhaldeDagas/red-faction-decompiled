// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519180 rf_nav_graph_destroy_nodes_and_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph array,no stack args. Walks each node pointer,releases neighbor backing at node40,then if pointer nonNULL invokes519210 flags1. Node destructor4126C0 releases neighbor40 AGAIN(safe only because release cleared header),and array112. Releases graph backing after all nodes. No NULL guard before first neighbor access,duplicate-node check or per-node reference counting. Returns graph release-helper result;no own deletion of graph header.
void **__thiscall rf_nav_graph_destroy_nodes_and_storage(_DWORD *this)
{
  int i; // eax
  int v2; // eax
  void *v5; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  v6 = 0;
  for ( i = rf_receiver_get_first_dword(this); v6 < i; i = rf_receiver_get_first_dword(this) )
  {
    v2 = sub_552200(this, v6);
    rf_pointer_array_release_storage((void **)(*(_DWORD *)v2 + 40));
    if ( v6 < rf_receiver_get_first_dword(this) )
    {
      v5 = *(void **)sub_552200(this, v6);
      if ( v5 )
        rf_nav_node_scalar_deleting_destructor(v5, 1);
    }
    ++v6;
  }
  return rf_pointer_array_release_storage((void **)this);
}

