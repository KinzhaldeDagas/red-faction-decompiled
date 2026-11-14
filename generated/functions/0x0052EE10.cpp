// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EE10 rf_geomod_set_finish_lightmap_generation_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl lowBYTEvalue,storetorawglobal663CA4 andreturnALunchanged. No boolean normalization,invalidationor immediate lightmapwork. Stage7generatesONLYwhenstoredbyte==1;2or255donotenablethatpath.
char __cdecl rf_geomod_set_finish_lightmap_generation_byte(char a1)
{
  byte_663CA4 = a1;
  return a1;
}

