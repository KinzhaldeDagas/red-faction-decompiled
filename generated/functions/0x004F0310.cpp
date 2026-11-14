// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0310 rf_register_runtime_loose_search_root
// UNREALRED VERIFIED [loose-root-registration] Registers a runtime-supplied loose search root and extension mask with alternate-media flag zero.
int __cdecl rf_register_runtime_loose_search_root(char *a1, char *a2)
{
  return rf_vfile_register_loose_search_root(a1, a2, 0);
}

