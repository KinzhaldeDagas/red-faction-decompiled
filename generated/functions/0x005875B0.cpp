// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005875B0 rf_character_instance_start_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Thiscall receiver,resolved animation index,mix float,hold low BYTE,RET12. Accepts signed index<base7504 count3928 but DOES NOT require index>=0; rejects classification BYTE[base+4620+index] only when EXACTLY1,not any nonzero. Mix gate raw5875F1 TEST AH,41h/JP accepts ordered>0 AND unordered NaN; zero/negative reject despite pseudocode showing >0 alone. Finds/adds exact animation record587260; return<=-1 stops without rollback(helper may already have appended failed record). On success clears global hold7500,writes mix and authored start tick to record,sets freeze designation7420 ONLY when hold BYTE==1; hold0/other values retain older designation. If animation-alone
// owner7424==-1,assigns this record and zeros float7448 ONLY,leaving7452 and delta vectors unchanged. Does not clamp mix<=1,reset phase/events/update counter,clear previous owner or validate clip/raw pointer. Advance/reset treat ANY nonzero classification as state,unlike this exact1 test.
void __thiscall rf_character_instance_start_action(int this, int a2, float a3, char a4)
{
  int v5; // [esp+4h] [ebp-4h]

  if ( a2 < *(_DWORD *)(*(_DWORD *)(this + 7504) + 3928)
    && *(_BYTE *)(*(_DWORD *)(this + 7504) + a2 + 4620) != 1
    && a3 > 0.0 )
  {
    v5 = rf_character_instance_find_or_add_action_record((float *)this, a2);
    if ( v5 > -1 )
    {
      *(_BYTE *)(this + 7500) = 0;
      *(float *)(this + 12 * v5 + 4828) = a3;
      *(_DWORD *)(this + 12 * v5 + 4824) = rf_rfa_get_start_tick(*(void **)(*(_DWORD *)(this + 7504) + 4 * a2 + 3932));
      if ( a4 == 1 )
        *(_DWORD *)(this + 7420) = v5;
      if ( *(_DWORD *)(this + 7424) == -1 )
      {
        *(_DWORD *)(this + 7424) = v5;
        *(float *)(this + 7448) = 0.0;
      }
    }
  }
}

