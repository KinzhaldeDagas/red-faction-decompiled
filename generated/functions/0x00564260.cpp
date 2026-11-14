// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564260 rf_model_descriptor_get_kind
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Return first dword of model descriptor. No validation or type conversion; model queue stores it separately but its shown rebuild consumer dispatches by owner runtime type.
int __cdecl rf_model_descriptor_get_kind(int a1)
{
  return *(_DWORD *)a1;
}

