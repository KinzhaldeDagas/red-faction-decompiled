// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556460 rf_generated_uv_set_mode
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Stores arbitrary DWORD into projection mode663E50 and returns it. No range checks; projector recognizes modes1 through4 and other values make no changes.
int __stdcall rf_generated_uv_set_mode(int a1)
{
  dword_663E50 = a1;
  return a1;
}

