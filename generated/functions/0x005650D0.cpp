// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005650D0 rf_model_descriptor_filename_pointer
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Return input descriptor address+0xC directly, used as filename C-string by model rebuild queue. No null check, allocation, copy, file resolution or resource load.
int __cdecl rf_model_descriptor_filename_pointer(int a1)
{
  return a1 + 12;
}

