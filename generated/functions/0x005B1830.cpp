// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1830 rf_plane_select_aabb_support_corners
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl(normalXYZ,outMinSupportIndex,outMaxSupportIndex),12-byte caller cleanup; normal plane distance component unused. Uses each normal component ordered>0 vsotherwise(<=0 OR unordered NaN); exact zero including signed0 follows otherwise. For finite normals first output is minimum dot-product AABB corner index,second maximum. Sign choices(N=otherwise,P=positive),outMin/outMax:NNN4/2,NNP0/6,NPN5/3,NPP1/7,PNN7/1,PNP3/5,PPN6/0,PPP2/4. Writes SECOND output before FIRST; shared output pointer therefore retains minimum index. No normalization,bounds reads,allocation or pointer check. Raw TEST AH,41h branches classify NaN with nonpositive side; NaN plane need not have meaningful
// mathematical support.
void __cdecl rf_plane_select_aabb_support_corners(float *a1, _DWORD *a2, _DWORD *a3)
{
  if ( *a1 <= 0.0 )
  {
    if ( a1[1] <= 0.0 )
    {
      if ( a1[2] <= 0.0 )
      {
        *a3 = 2;
        *a2 = 4;
      }
      else
      {
        *a3 = 6;
        *a2 = 0;
      }
    }
    else if ( a1[2] <= 0.0 )
    {
      *a3 = 3;
      *a2 = 5;
    }
    else
    {
      *a3 = 7;
      *a2 = 1;
    }
  }
  else if ( a1[1] <= 0.0 )
  {
    if ( a1[2] <= 0.0 )
    {
      *a3 = 1;
      *a2 = 7;
    }
    else
    {
      *a3 = 5;
      *a2 = 3;
    }
  }
  else if ( a1[2] <= 0.0 )
  {
    *a3 = 0;
    *a2 = 6;
  }
  else
  {
    *a3 = 4;
    *a2 = 2;
  }
}

