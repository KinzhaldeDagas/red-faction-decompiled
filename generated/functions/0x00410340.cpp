// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410340 rf_ai_collect_path_record_candidate_points
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(entity full HANDLE,signed requestedLimit); no uniform AL/EAX success result. FIRST zeros shared candidate count6663F8, then
// ENTITY-resolves handle. Missing entity returns with count0, leaving point array/queue/record markers unchanged. If entity primary record pointer+1692 isNULL, calls40FD80(entity
// position+60,FLOAT+1984,FLOAT+1988,LOWBYTE1,&entity+1692,&entity+1692,LOWBYTE0): BOTH output pointers intentionally alias the SAME +1692 DWORD, and+1696 is not passed. Helper AL is
// ignored, so populated fallback output admits even when delegatedAL0; sequential edge outputs leave second record in aliased slot. Still-null+1692 exits with count0. Otherwise scans
// worldSolid+768 pointer array in signed index order, re-reading count DWORD+0 each iteration; for each record writes BYTE+52 EXACT1 iff pointer equals entity+1692 OR+1696, else0. No
// world/record/array pointer guards or preservation of prior markers.  requestedLimit==0: generates one random point from primary into6665D8, sets count1; nonnull secondary generates
// second at6665E4 and sets count2, even if equal to primary. Scans primary record+40 neighbor pointer array in signed order/count re-read: at each valid iteration, candidate
// count>=100 immediately exits whole function BEFORE inspecting marker. Nonzero neighbor BYTE+52 skips; zero marks1, generates point at6665D8+12*count, increments count. Then nonnull
// secondary neighbor array receives same loop/cap/test/generation but DOES NOT mark appended neighbors, so repeated unmarked neighbors can append duplicates. Existing primary marks
// and initial seed markers still suppress those records. Mode0 never resets/uses queue666438/count6665D0.  requestedLimit!=0: signed limit>100 is clamped locally to100; negative
// limits stay negative. Seeds shared record queue666438[0]=primary and queue count6665D0=1; nonnull secondary seeds[1] and count2 without distinctness check. Signed expanding loop
// i0..queueCount-1 calls410750(queue[i]) only while queueCount<limit; helper may append a whole neighbor prefix up to102, so queue can exceed requested limit before next outer check.
// Sets candidate count6663F8=min_signed(limit,queueCount), then generates points for signed i0..<candidateCount from queued record pointers. Negative limit therefore publishes
// negative candidate count and generates none, after record-marker reset/queue seeding. Positive limit outputs at most100 points; queue cap102 is distinct. All point generation is
// unchecked, consumes RNG and writes progressively. After optional initial40FD80 fit query, collection loops perform no additional collision/visibility/eligibility test. No result
// rollback, clearing unused point/queue slots or independent owner/death/authority gate.
char __cdecl rf_ai_collect_path_record_candidate_points(int a1, int a2)
{
  int first_dword; // eax
  int *v3; // eax
  int v4; // eax
  float **v5; // eax
  int v7; // [esp+18h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-Ch]
  int v9; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]
  int m; // [esp+24h] [ebp-4h]
  int n; // [esp+24h] [ebp-4h]
  int j; // [esp+24h] [ebp-4h]
  int k; // [esp+24h] [ebp-4h]

  dword_6663F8 = 0;
  first_dword = rf_entity_resolve_handle(a1);
  v9 = first_dword;
  if ( first_dword )
  {
    if ( !*(_DWORD *)(first_dword + 1692) )
      LOBYTE(first_dword) = sub_40FD80(
                              (float *)(first_dword + 60),
                              *(float *)(first_dword + 1984),
                              *(float *)(first_dword + 1988),
                              1,
                              (int *)(first_dword + 1692),
                              (int *)(first_dword + 1692),
                              0);
    if ( *(_DWORD *)(v9 + 1692) )
    {
      for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 768)); ++i )
      {
        v3 = (int *)sub_552200((_DWORD *)(rf_world_solid + 768), i);
        v8 = *v3;
        *(_BYTE *)(v8 + 52) = *v3 == *(_DWORD *)(v9 + 1692) || v8 == *(_DWORD *)(v9 + 1696);
      }
      if ( a2 )
      {
        if ( a2 > 100 )
          a2 = 100;
        dword_666438[0] = *(_DWORD *)(v9 + 1692);
        unk_6665D0 = 1;
        if ( *(_DWORD *)(v9 + 1696) )
        {
          unk_66643C = *(_DWORD *)(v9 + 1696);
          unk_6665D0 = 2;
        }
        for ( j = 0; j < unk_6665D0 && unk_6665D0 < a2; ++j )
          rf_path_record_enqueue_unmarked_neighbors(dword_666438[j]);
        dword_6663F8 = rf_int_min_signed(a2, unk_6665D0);
        for ( k = 0; ; ++k )
        {
          LOBYTE(first_dword) = k;
          if ( k >= dword_6663F8 )
            break;
          rf_path_record_sample_offset_point((float *)dword_666438[k], &flt_6665D8[3 * k]);
        }
      }
      else
      {
        rf_path_record_sample_offset_point(*(float **)(v9 + 1692), flt_6665D8);
        dword_6663F8 = 1;
        if ( *(_DWORD *)(v9 + 1696) )
        {
          rf_path_record_sample_offset_point(*(float **)(v9 + 1696), flt_6665E4);
          dword_6663F8 = 2;
        }
        for ( m = 0; ; ++m )
        {
          first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(v9 + 1692) + 40));
          if ( m >= first_dword )
            break;
          if ( dword_6663F8 >= 100 )
            return first_dword;
          v4 = sub_552200((_DWORD *)(*(_DWORD *)(v9 + 1692) + 40), m);
          v7 = *(_DWORD *)v4;
          if ( !*(_BYTE *)(*(_DWORD *)v4 + 52) )
          {
            *(_BYTE *)(v7 + 52) = 1;
            rf_path_record_sample_offset_point((float *)v7, &flt_6665D8[3 * dword_6663F8]);
            ++dword_6663F8;
          }
        }
        LOBYTE(first_dword) = v9;
        if ( *(_DWORD *)(v9 + 1696) )
        {
          for ( n = 0; ; ++n )
          {
            first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(v9 + 1696) + 40));
            if ( n >= first_dword || dword_6663F8 >= 100 )
              break;
            v5 = (float **)sub_552200((_DWORD *)(*(_DWORD *)(v9 + 1696) + 40), n);
            if ( !*((_BYTE *)*v5 + 52) )
            {
              rf_path_record_sample_offset_point(*v5, &flt_6665D8[3 * dword_6663F8]);
              ++dword_6663F8;
            }
          }
        }
      }
    }
  }
  return first_dword;
}

