// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052D3D0 rf_geomod_boolean_stage_4_transfer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace,optionalOutputSolid,transferMode,optionalOutArea. BothoutputsNULL ->noaction. OutputSolidnonnull ->clearDWORD28 mappings onALLsourcevertices120;area-only leavesmappingunchanged. OutAreanonNULL initializeF32zero. Iterateactivefaces112 selectingactionTable[40*operand+5*transferMode+class]. Action2: ifoutputSolid copyface withflag0/mappingreuse, then projectgeneratedUV iff copiedoperand1. Action3 samecopy thenreversecopiedwinding andprojectgeneratedUV ifoperand1. For EITHERaction add ORIGINALface area toF32sum ifoutArea,includingwhennooutputsolid; no signflip forreverse. Actions0/1ignore. No removal/transfer ofsourcefaceownership: copyingonly,stage5 appliespolicy
// later. Copyfailurereturn unchecked before accessingcopyflags;no outputbounds/tree/lightmapfinalize or rollback.
void __cdecl rf_geomod_boolean_stage_4_transfer(int a1, _DWORD *a2, int a3, float *a4)
{
  _DWORD *v4; // esi
  int v5; // [esp+4h] [ebp-18h]
  int v6; // [esp+8h] [ebp-14h]
  int v7; // [esp+Ch] [ebp-10h]
  int i; // [esp+14h] [ebp-8h]
  _DWORD *j; // [esp+18h] [ebp-4h]

  if ( a2 || a4 )
  {
    if ( a2 )
    {
      for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 120)); ++i )
        *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 120), i) + 28) = 0;
    }
    if ( a4 )
      *a4 = 0.0;
    for ( j = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); j; j = (_DWORD *)rf_solid_face_next_link((int)j) )
    {
      v4 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get(j + 10) + 5 * a3];
      v5 = v4[rf_geomod_face_boolean_class_get(j + 10)];
      if ( v5 == 2 )
      {
        if ( a2 )
        {
          v7 = rf_geomod_face_copy_to_output(j, a2, a1, 0);
          if ( rf_geomod_face_operand_get((_DWORD *)(v7 + 40)) )
            rf_geomod_generated_uv_project(v7);
        }
        if ( a4 )
          *a4 = rf_geomod_face_area(j) + *a4;
      }
      else if ( v5 == 3 )
      {
        if ( a2 )
        {
          v6 = rf_geomod_face_copy_to_output(j, a2, a1, 0);
          rf_geomod_face_reverse_winding(v6);
          if ( rf_geomod_face_operand_get((_DWORD *)(v6 + 40)) )
            rf_geomod_generated_uv_project(v6);
        }
        if ( a4 )
          *a4 = rf_geomod_face_area(j) + *a4;
      }
    }
  }
}

