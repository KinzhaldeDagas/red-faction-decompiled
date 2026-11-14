// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561EF0 rf_model_handle_get_node_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX tagged handle:tag2 returns definition8 DWORD72;tag1 returns instance4 DWORD72;tag3 delegates scene definition8 flattened object count; other tags-1. No pointer/state validation, allocation or cached count update.
int __thiscall rf_model_handle_get_node_count(_DWORD *this)
{
  switch ( *this )
  {
    case 2:
      return *(_DWORD *)(*(this + 2) + 72);
    case 1:
      return *(_DWORD *)(*(this + 1) + 72);
    case 3:
      return rf_scene_definition_get_flat_object_count((_DWORD *)*(this + 2));
  }
  return -1;
}

