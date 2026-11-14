// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511E80 rf_projectile_trace_contact_continue
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclprojectile,contactStart3f*,outDoneBYTE*,outRicochetBYTE*,traceResult*,caller pops20,returnsEAXhandledbool. Infopointer=projectile660;requireINFOflagsDWORD612bit80000000 (rawtest,not a recordID). Ifclear,setRicochet0,Done1,return0withoutclearingremainingdistance752/result. Ifset,initbothoutBYTES0. Unlessinfoflags2DWORD616 pierces_allmask0x1set,physicaltypeDWORD464==2 calls511FF0andstoresALricochet;othertypeclearsremainingdistance752=0. Ifnotricochet ANDORDEREDremaining>0,computevelocity324length,dividevelocitybylength WITHOUTzeroguard;store remaining inresultFLOAT24,call4CFA50(start,unitVelocity,result) forF32consumed/advance distance,then normalize resultnormal12
// withoutfiniteguard. Continue ONLYifORDEREDremaining>consumed:subtractconsumed,updateprojectilepublished/physicspositionsfromresultXYZvia4BC330. Else(<= ORUNORDERED)cleardistance0,NO positionupdate;pseudocode <=/else misses unorderedclear. FinallyDone=NOT(ORDEREDremaining>0),regardlessricochetflag;return1wheneverinitialbit31set. Successfulricochetalone doesnotforceDone0. No ammo/damageaccounting,ownerNULLguard,normalvalidation orrollback;resultfieldsuntouchedonpathswhichskiptracehelper.
int __cdecl rf_projectile_trace_contact_continue(int a1, float *a2, _BYTE *a3, char *a4, float *a5)
{
  float geometry_contact; // [esp+4h] [ebp-14h]
  int v7[3]; // [esp+8h] [ebp-10h] BYREF
  float v8; // [esp+14h] [ebp-4h]

  if ( *(int *)(*(_DWORD *)(a1 + 660) + 612) < 0 )
  {
    *a4 = 0;
    *a3 = 0;
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 1) == 0 )
    {
      if ( *(_DWORD *)(a1 + 464) == 2 )
        *a4 = rf_projectile_try_ricochet_preserve_speed(a1);
      else
        *(float *)(a1 + 752) = 0.0;
    }
    if ( !*a4 && *(float *)(a1 + 752) > 0.0 )
    {
      v8 = rf_vector3_length((float *)(a1 + 324));
      a5[6] = *(float *)(a1 + 752);
      rf_vector_divide((float *)(a1 + 324), (float *)v7, v8);
      geometry_contact = rf_projectile_advance_to_next_geometry_contact(a2, (float *)v7, a5);
      rf_vector_normalize_reciprocal_sqrt(a5 + 3);
      if ( *(float *)(a1 + 752) <= (double)geometry_contact )
      {
        *(float *)(a1 + 752) = 0.0;
      }
      else
      {
        *(float *)(a1 + 752) = *(float *)(a1 + 752) - geometry_contact;
        rf_object_publish_position_and_bounds(a1, a5);
      }
    }
    *a3 = 1;
    if ( *(float *)(a1 + 752) > 0.0 )
      *a3 = 0;
    return 1;
  }
  else
  {
    *a4 = 0;
    *a3 = 1;
    return 0;
  }
}

