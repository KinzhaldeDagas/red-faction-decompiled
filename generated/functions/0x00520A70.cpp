// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520A70 rf_world_visit_room_through_portal_apertures
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Cdecl world,room,optionalScreenRect4,depth,flags,viewPoint. Six stack args caller-pop24; nominal char return is AL residue, not success. Reject authored-sky BYTE1 nonzero then roomBYTE0 nonzero before any state writes. Otherwise set globalBYTEA4207C=1, use physical full-screen[0,0,width,height] if rectangleNULL. If roomBYTE353==0 append to global array940A48 at countA42074++, copy rect to364..376. Else union stored rect with incoming and move FIRST matching pointer to final array slot count-1 by shifting left, leaving count unchanged; if not found still overwrites final slot, and count0 would write preceding array word. No bounds or capacity checks. Increment statsA42054 on EVERY admitted
// visit, set roomBYTE353=1 and352=1, depthDWORD356=inputdepth. flags mask0x1 stops portal traversal after recording; roomBYTE64 nonzero also stops unless room==globalA42080. Iterate portal-pointer array room48. Other room=end1 if end0==current elseend0 (no membership validation). Skip when SIGNED other.depth356<current.depth356. For portalBYTE36==0 set36=1 BEFORE broadphase; if viewpoint inside inclusive portalAABB8/20 expanded1.0 use full physical screen bounds40..52 and cachedRejectBYTE37=0. Else frustum rejection sets37=1; otherwise projectAABB toscreen and set37=!projectionSuccess. Cache reused across visits with no per-call reset. If not rejected, intersect INCOMING rect (not accumulated room union) with portal rect using max minima/min maxima. Width/height comparisons accept strictly positive OR UNORDERED (AH41/JNP thenJP); orderedzero/negative rejects. Recurse with depth+1,same
// flags/viewpoint,then unconditionally assign OTHER room.depth356=255 even if recursive entry rejected sky/byte0. No explicit recursion limit or visited-room early-out; repeat visits reorder list and enlarge union. World arg is only forwarded recursively in this body.
// [UnrealRed physical spheres 2026-11-12; executable-store scan] Portal-aperture room traversal sets room byte352(+160h) to1. Cachedroom admission in410170 is coupled to this renderer visibility owner, not AI state. Host room loading/missionUnHide alone does not establish native byte352.
char __cdecl rf_world_visit_room_through_portal_apertures(int a1, int a2, float *a3, int a4, int a5, float *a6)
{
  int first_dword; // eax
  bool v7; // al
  int v9; // [esp+1Ch] [ebp-34h]
  float v10; // [esp+20h] [ebp-30h] BYREF
  float v11; // [esp+24h] [ebp-2Ch]
  float v12; // [esp+28h] [ebp-28h]
  float v13; // [esp+2Ch] [ebp-24h]
  int v14; // [esp+30h] [ebp-20h]
  int i; // [esp+34h] [ebp-1Ch]
  int j; // [esp+38h] [ebp-18h]
  int k; // [esp+3Ch] [ebp-14h]
  float v18[4]; // [esp+40h] [ebp-10h] BYREF

  LOBYTE(first_dword) = rf_room_is_authored_sky((_BYTE *)a2);
  if ( !(_BYTE)first_dword )
  {
    LOBYTE(first_dword) = unknown_libname_11((void *)a2);
    if ( !(_BYTE)first_dword )
    {
      unk_A4207C = 1;
      if ( !a3 )
      {
        v18[0] = 0.0;
        v18[1] = 0.0;
        v18[2] = (float)rf_renderer_get_physical_screen_width();
        v18[3] = (float)rf_renderer_get_physical_screen_height();
        a3 = v18;
      }
      if ( *(_BYTE *)(a2 + 353) )
      {
        *(float *)(a2 + 364) = rf_float_minimum_two_values(*a3, *(float *)(a2 + 364));
        *(float *)(a2 + 372) = rf_float_maximum_two_values(a3[2], *(float *)(a2 + 372));
        *(float *)(a2 + 368) = rf_float_minimum_two_values(a3[1], *(float *)(a2 + 368));
        *(float *)(a2 + 376) = rf_float_maximum_two_values(a3[3], *(float *)(a2 + 376));
        for ( i = 0; i < dword_A42074 && dword_940A48[i] != a2; ++i )
          ;
        while ( i < dword_A42074 - 1 )
        {
          dword_940A48[i] = unk_940A4C[i];
          ++i;
        }
        dword_940A44[dword_A42074] = a2;
      }
      else
      {
        for ( j = 0; j < dword_A42074; ++j )
          ;
        dword_940A48[dword_A42074++] = a2;
        *(float *)(a2 + 364) = *a3;
        *(float *)(a2 + 368) = a3[1];
        *(float *)(a2 + 372) = a3[2];
        *(float *)(a2 + 376) = a3[3];
      }
      ++*(_DWORD *)&byte_98967F[756181];
      *(_BYTE *)(a2 + 353) = 1;
      *(_BYTE *)(a2 + 352) = 1;
      *(_DWORD *)(a2 + 356) = a4;
      LOBYTE(first_dword) = a5 & 1;
      if ( (a5 & 1) == 0 )
      {
        if ( !*(_BYTE *)(a2 + 64) || (LOBYTE(first_dword) = a2, a2 == unk_A42080) )
        {
          for ( k = 0; ; ++k )
          {
            first_dword = rf_receiver_get_first_dword((void *)(a2 + 48));
            if ( k >= first_dword )
              break;
            v14 = *(_DWORD *)sub_552200((_DWORD *)(a2 + 48), k);
            if ( *(_DWORD *)v14 == a2 )
              v9 = *(_DWORD *)(v14 + 4);
            else
              v9 = *(_DWORD *)v14;
            if ( *(_DWORD *)(v9 + 356) >= *(_DWORD *)(a2 + 356) )
            {
              if ( !*(_BYTE *)(v14 + 36) )
              {
                *(_BYTE *)(v14 + 36) = 1;
                if ( rf_point_within_expanded_aabb(a6, 1.0, (float *)(v14 + 8), (float *)(v14 + 20)) )
                {
                  *(float *)(v14 + 40) = 0.0;
                  *(float *)(v14 + 44) = 0.0;
                  *(float *)(v14 + 48) = (float)rf_renderer_get_physical_screen_width();
                  *(float *)(v14 + 52) = (float)rf_renderer_get_physical_screen_height();
                  *(_BYTE *)(v14 + 37) = 0;
                }
                else if ( rf_frustum_reject_aabb((float *)(v14 + 8), (float *)(v14 + 20)) )
                {
                  *(_BYTE *)(v14 + 37) = 1;
                }
                else
                {
                  v7 = rf_renderer_world_aabb_screen_bounds(
                         (float *)(v14 + 8),
                         (float *)(v14 + 20),
                         (float *)(v14 + 40),
                         (float *)(v14 + 44),
                         (float *)(v14 + 48),
                         (float *)(v14 + 52));
                  *(_BYTE *)(v14 + 37) = !v7;
                }
              }
              if ( !*(_BYTE *)(v14 + 37) )
              {
                v10 = rf_float_maximum_two_values(*a3, *(float *)(v14 + 40));
                v12 = rf_float_minimum_two_values(a3[2], *(float *)(v14 + 48));
                v11 = rf_float_maximum_two_values(a3[1], *(float *)(v14 + 44));
                v13 = rf_float_minimum_two_values(a3[3], *(float *)(v14 + 52));
                if ( v12 > (double)v10 && v13 > (double)v11 )
                {
                  rf_world_visit_room_through_portal_apertures(a1, v9, &v10, a4 + 1, a5, (int)a6);
                  *(_DWORD *)(v9 + 356) = 255;
                }
              }
            }
          }
        }
      }
    }
  }
  return first_dword;
}

