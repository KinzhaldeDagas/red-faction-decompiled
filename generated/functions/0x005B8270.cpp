// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8270 rf_model_mesh144_construct_null_geometry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): 144-byte mesh array initializer used by character and static-resource loaders: sets only geometry/LOD pointer at offset140 to NULL. Names, material count132 and material pointer136 remain untouched. Raw code returns ECX as incidental EAX despite existing void declaration; no stack arguments.
void __thiscall rf_model_mesh144_construct_null_geometry(_DWORD *this)
{
  *(this + 35) = 0;
}

