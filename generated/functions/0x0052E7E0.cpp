// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052E7E0 rf_geomod_boolean_stage_7_finish
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace. ONLYglobalBYTE663CA4==EXACT1 iteratesactiveface list112. For everySIGNEDlightmapWORD54<0 write-1; ifroomowner68nonnull callfaceLightmapGenerate(workspace,face,2.0). Existingnonnegativeindexesunchanged;negative roomlessfacesremain-1. Otherglobalbytevalues skipALLwork. No stage=-1 or scratch-owner marking here; advancewrapper doescompletion aftercall. EAXbytevalueorface-nextloopresidue (normally0),notstatus.
int __cdecl rf_geomod_boolean_stage_7_finish(char *a1)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = (unsigned __int8)byte_663CA4;
  if ( byte_663CA4 == 1 )
  {
    result = rf_receiver_get_first_dword(a1 + 112);
    for ( i = result; i; i = result )
    {
      if ( *(__int16 *)(i + 54) < 0 )
      {
        *(_WORD *)(i + 54) = -1;
        if ( *(_DWORD *)(i + 68) )
          rf_geomod_face_lightmap_generate(a1, i, 2.0);
      }
      result = rf_solid_face_next_link(i);
    }
  }
  return result;
}

