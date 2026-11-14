// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CF80 rf_geomod_boolean_stage_3_classify
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspaceSolid,mode. Select spatial52CFB0 iffglobal rf_geomod_spatial_classifier_enabled nonzero,else linear52D170; forward arguments,returncalleeEAX unchanged. No independent faceclassification, cleanup or stageadvance.
int __cdecl rf_geomod_boolean_stage_3_classify(float **a1, int a2)
{
  if ( rf_geomod_spatial_classifier_enabled )
    return rf_geomod_fragments_classify_spatial(a1, a2);
  else
    return rf_geomod_fragments_classify_linear((float *)a1, a2);
}

