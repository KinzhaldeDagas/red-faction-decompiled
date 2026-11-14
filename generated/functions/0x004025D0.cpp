// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004025D0 rf_ai_refresh_target_collision_and_corridor_probes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(required AI block,required target COMMON-object pointer). Only deadline+660 elapsed EXACT AL1
// executes; bypass preserves all probe bytes/timestamps/timers. Interval=rand()%200+200 (normally200..399ms), query mask0x27. Primary selected weapon DWORD+4!=-1 permits
// UNCHECKED1360-byte weapon-record lookup; flags DWORD+616 mask8 clears query bits0x6 (0x27->0x21) and signed-truncates interval/2 (normally100..199ms). No other lower/upper index
// check. Rearms+660 BEFORE queries. Copies target COMMON position+60 to local. Radius=float32(max_literal(first=target FLOAT+120,second=owner FLOAT+120)+DOUBLE0.10000000149011612);
// max chooses OWNER operand when unordered. First seven-arg segment query(owner retained point+2004,target COMMON-point local,radius,mask,owner pointer,target pointer,NULL); ONLY
// AL==EXACT1 writes BYTE+668=0, all other AL writes1. Constructs alternate point without initialization, calls object retained-entity-point/common-position helper(target,out)
// ignoring its return, then second seven-arg query with same origin/radius/mask and alternate point; same exact1 inversion writesBYTE+669. Both queries always run regardless of first
// result. No-write muzzle-vector and matrix constructors then muzzle-transform(owner,selected weapon,tempPosition,tempMatrix), ignoring result even weapon-1/failure. Calls
// corridor-veto410170 with FIVE explicit stack slots(owner full handle+44,target full handle+44,muzzlePoint,target COMMON-point,alternatePoint) and cleans20bytes; complete callee
// native consumes FIRST FOUR only, so corridor segment is muzzle->COMMON target point and ignores alternate endpoint. Stores returnedAL VERBATIM atBYTE+670. No own
// output-zero/fallback if muzzle delegate leaves temporaries unchanged. If either BYTE+668/+669==EXACT1, copies global FLOAT seconds clock6FC428 into block+664. Then SECONDARY state
// DWORD+692==3 arms deadline+560 with0ms (clock-relative arm, not disarm). Other secondary states compute COMMON-position Euclidean distance, storefloat32 before maximum
// attack-range4098B0 call; ordered distance<returnedST0 arms+560 with500ms, equality/NaN does not arm. Both visibility bytes0 leave prior+664 and+560 untouched; corridor byte does
// not gate these writes. No direct target/weapon selection change, independent owner/target type/dead/runtime/authority gate or defined return status.
void __cdecl rf_ai_refresh_target_collision_and_corridor_probes(int *a1, int a2)
{
  float v2; // [esp+14h] [ebp-5Ch]
  _BYTE v3[12]; // [esp+1Ch] [ebp-54h] BYREF
  int v4[3]; // [esp+28h] [ebp-48h] BYREF
  int v5; // [esp+34h] [ebp-3Ch]
  float v6; // [esp+38h] [ebp-38h]
  int v7[3]; // [esp+3Ch] [ebp-34h] BYREF
  char v8[36]; // [esp+48h] [ebp-28h] BYREF
  int v9; // [esp+6Ch] [ebp-4h]

  if ( rf_replicator_has_elapsed(a1 + 165) )
  {
    v5 = rand() % 200 + 200;
    v9 = 39;
    if ( a1[1] != -1 && (*((_DWORD *)&rf_weapon_records + 340 * a1[1] + 154) & 8) != 0 )
    {
      v9 &= 0x39u;
      v5 /= 2;
    }
    rf_replicator_arm_milliseconds(a1 + 165, v5);
    rf_vector3_copy_return_destination((float *)v4, (float *)(a2 + 60));
    v6 = rf_float_maximum_two_values(*(float *)(a2 + 120), *(float *)(*a1 + 120)) + 0.1000000014901161;
    *((_BYTE *)a1 + 668) = rf_segment_objects_or_world_hit_filtered_by_radius(*a1 + 2004, (int)v4, v6, v9, *a1, a2, 0) != 1;
    rf_vector3_default_construct_noop(v7);
    rf_object_copy_entity_vector7D4_or_position(a2, (float *)v7);
    *((_BYTE *)a1 + 669) = rf_segment_objects_or_world_hit_filtered_by_radius(*a1 + 2004, (int)v7, v6, v9, *a1, a2, 0) != 1;
    rf_vector3_default_construct_noop(v3);
    rf_matrix3_construct(v8);
    rf_entity_compute_weapon_muzzle_transform((_DWORD *)*a1, a1[1], (int)v3, (int)v8);
    *((_BYTE *)a1 + 670) = rf_ai_segment_intersects_same_friendliness_entity(
                             *(_DWORD *)(*a1 + 44),
                             *(_DWORD *)(a2 + 44),
                             (int)v3,
                             (int)v4);
    if ( *((_BYTE *)a1 + 668) == 1 || *((_BYTE *)a1 + 669) == 1 )
    {
      a1[166] = dword_6FC428;
      if ( a1[173] == 3 )
      {
        rf_replicator_arm_milliseconds(a1 + 140, 0);
      }
      else
      {
        v2 = rf_vector_distance((const float *)(a2 + 60), (const float *)(*a1 + 60));
        if ( v2 < rf_ai_resolve_maximum_attack_range(a1) )
          rf_replicator_arm_milliseconds(a1 + 140, 500);
      }
    }
  }
}

