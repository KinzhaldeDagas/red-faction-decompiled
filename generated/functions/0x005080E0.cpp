// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005080E0 rf_rail_trail_allocate_from_pool
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Cdecl object UID,position pointer,direction pointer,speed float. Takes free head91170C; exhausted =>NULL and no allocation/eviction. Writes UID+68,age+64=0,basis+24 from55BF00 normalized-direction orientation, fixed base center+12=position-RAW supplied direction*0.5, apex+0=position,speed+60. Basis forward+48 is normalized by helper; base offset uses input magnitude unchanged. Removes node from free ring (updates/clears head), clears links, appends before active head911708 or becomes self-linked first active node. No UID resolution, vector finite/NULL guard, update/render or lifetime selection here. EAX is NEW node only for initially empty active ring; existing-active
// case returns preexisting active head, not necessarily allocated node.
float *__cdecl rf_rail_trail_allocate_from_pool(int a1, float *lhs, float *vector, float a4)
{
  float *result; // eax
  float *v5; // eax
  float *v6; // eax
  float v7[3]; // [esp+4h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-28h] BYREF
  float out_vector[3]; // [esp+1Ch] [ebp-1Ch] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-10h] BYREF
  float *destination; // [esp+34h] [ebp-4h]

  result = (float *)unk_91170C;
  destination = (float *)unk_91170C;
  if ( unk_91170C )
  {
    *((_DWORD *)destination + 17) = a1;
    destination[16] = 0.0;
    rf_orientation_matrix_from_normalized_direction(destination + 6, vector);
    v5 = rf_vector_multiply_scalar(vector, scaled_result, 0.5);
    v6 = rf_vector_subtract(lhs, out_vector, v5);
    rf_vector_copy(destination + 3, copy_result, v6);
    rf_vector_copy(destination, v7, lhs);
    destination[15] = a4;
    if ( (float *)unk_91170C == destination )
    {
      if ( *((float **)destination + 18) == destination )
      {
        destination[18] = 0.0;
        destination[19] = 0.0;
        unk_91170C = 0;
        goto LABEL_7;
      }
      unk_91170C = *((_DWORD *)destination + 18);
    }
    *(float *)(*((_DWORD *)destination + 19) + 72) = destination[18];
    *(float *)(*((_DWORD *)destination + 18) + 76) = destination[19];
    destination[18] = 0.0;
    destination[19] = 0.0;
LABEL_7:
    if ( unk_911708 )
    {
      destination[19] = *(float *)(unk_911708 + 76);
      *((_DWORD *)destination + 18) = unk_911708;
      *(_DWORD *)(*(_DWORD *)(unk_911708 + 76) + 72) = destination;
      result = (float *)unk_911708;
      *(_DWORD *)(unk_911708 + 76) = destination;
    }
    else
    {
      *((_DWORD *)destination + 18) = destination;
      *((_DWORD *)destination + 19) = destination;
      unk_911708 = destination;
      return destination;
    }
  }
  return result;
}

