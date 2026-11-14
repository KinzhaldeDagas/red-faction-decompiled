// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587B60 rf_character_instance_get_node_transform
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Thin thiscall wrapper forwarding output buffer and node index to585C50, returning supplied output pointer. Underlying helper handles primary bones, auxiliary bindings and geometry nodes, including identity fallback. Wrapper adds no validation or independent transform logic.
void *__thiscall rf_character_instance_get_node_transform(void *this, void *a2, int a3)
{
  rf_character_instance_resolve_node_transform((int)this, a2, a3);
  return a2;
}

