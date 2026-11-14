// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004293C0 rf_entity_choose_body_actions_and_movement_codes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity,outCodeA DWORD*,outCodeB DWORD*), no uniform EAX result. Every output pair writes A THEN B; no NULL/alias guard. Split-screen BYTE ANY
// nonzero immediately writes(3,5), exits without own entity reads/actions/speed writes. Otherwise movement predicate437F60==EXACT AL1 AND humanoid40D150==EXACT AL1 gives(1,1),
// short-circuiting second on first mismatch. Then body action20==EXACT AL1 OR action19==EXACT AL1 gives(9,9) with no new action/timers. Remaining path: eligibility1 only if class
// flags2 DWORD1832 mask4 CLEAR, signed route-count entity1416>0, and AI flags entity2000 mask8 SET. Always copy original entity vector1952 into local vector. If eligible,559280
// normalizes local in place UNCHECKED; only ORDERED returned length<DOUBLE0.10000000149011612 clears eligibility, equality/NaN preserves it. Always initialize local direction output
// zero. Eligible normalized vector dot COMMON third matrix row96 roundsFLOAT32; allow inclusive[-DOUBLE0.5,+DOUBLE0.5] OR UNORDERED, otherwise clear eligibility. Still eligible
// transforms ORIGINAL UNNORMALIZED entity1952 by COMMON matrix rows72 into local direction; normalized copy is only for angular test. High-action attempt requires eligibility,
// slots20 index2964 and19 index2948 both!=-1, then action20/19 queries each AL0 (ANY nonzero rejects, unlike early exact1 tests). Once these pass, STOP firing422A40(raw full
// handle44,current primary676) unconditionally, ignoring all later rejection possibilities. Require BYTE1784 any nonzero, ORDERED distance(retained
// point2004,point1788)>DOUBLE8.199999809265137 (<= OR UNORDERED rejects), and probe BYTE1340 OR1341 any nonzero. Success writes(9,9), requests body action20 for only ordered
// localDirection.X>0, else19 for <= OR UNORDERED, five args(entity,action,FLOAT1,BYTE0,BYTE1). Ignore request result; then entity DWORD1980=1, arm deadlines1948,1232,1236,1860,1944
// in order at relative1200 MILLISECONDS each, request4344D0 thiscall speed1 and exit. Action failure does not suppress timers/stores. Any high-attempt rejection falls back with
// firing-stop effects retained if already reached. If eligibility==1 and slots18 index2932 and17 index2916 both!=-1: request speed0 FIRST, write(3,5); only if active18 AL0 AND
// active17 AL0 request action18 for ordered localDirection.X>0, else17 for <=/UNORDERED, same unit action args; no new timer/1980 write. Otherwise request speed1 FIRST, then
// write(2,4) only if primary676==global911CBC, primary mode1364==EXACT1, and RE-READ split-screen/multiplayer BYTEs both0; else(3,5). Speed helper may override request for
// carried-body state and writes native speed/physics fields; do not substitute direct speed-mode assignment. No independent action-record bound, owner ready/death/authority/finite
// guard, failed-stop rollback or output snapshot: aliased outputs/entity fields can affect later reads; when output pointers alias, B is final stored pair value.
void __cdecl rf_entity_choose_body_actions_and_movement_codes(int a1, _DWORD *a2, _DWORD *a3)
{
  float *v3; // eax
  float copy_result[3]; // [esp+Ch] [ebp-38h] BYREF
  _BYTE v5[15]; // [esp+18h] [ebp-2Ch] BYREF
  bool v6; // [esp+27h] [ebp-1Dh]
  float destination[3]; // [esp+28h] [ebp-1Ch] BYREF
  float v8[3]; // [esp+34h] [ebp-10h] BYREF
  float v9; // [esp+40h] [ebp-4h]

  if ( rf_splitscreen_runtime_active )
  {
    *a2 = 3;
    *a3 = 5;
  }
  else if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(a1) && rf_entity_has_humanoid_flag(a1) )
  {
    *a2 = 1;
    *a3 = 1;
  }
  else if ( rf_entity_body_action_is_active(a1, 0x14u) || rf_entity_body_action_is_active(a1, 0x13u) )
  {
    *a2 = 9;
    *a3 = 9;
  }
  else
  {
    v6 = (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 4) == 0;
    if ( *(int *)(a1 + 1416) <= 0 || (*(_DWORD *)(a1 + 2000) & 8) == 0 )
      v6 = 0;
    rf_vector3_copy_return_destination(v8, (float *)(a1 + 1952));
    if ( v6 && rf_vector3_normalize_return_length(v8) < 0.1000000014901161 )
      v6 = 0;
    v9 = 0.0;
    rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
    if ( v6 )
    {
      v9 = rf_vector_dot(v8, (float *)(a1 + 96));
      if ( v9 <= 0.5 && v9 >= -0.5 )
      {
        v3 = rf_vector3_transform_by_matrix_rows((float *)(a1 + 1952), (float *)v5, (float *)(a1 + 72));
        rf_vector_copy(destination, copy_result, v3);
      }
      else
      {
        v6 = 0;
      }
    }
    if ( !v6
      || *(_DWORD *)(a1 + 2964) == -1
      || *(_DWORD *)(a1 + 2948) == -1
      || rf_entity_body_action_is_active(a1, 0x14u)
      || rf_entity_body_action_is_active(a1, 0x13u)
      || (rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676)), !*(_BYTE *)(a1 + 1784))
      || rf_vector_distance((const float *)(a1 + 2004), (const float *)(a1 + 1788)) <= 8.199999809265137
      || !*(_BYTE *)(a1 + 1340) && !*(_BYTE *)(a1 + 1341) )
    {
      if ( !v6 || *(_DWORD *)(a1 + 2932) == -1 || *(_DWORD *)(a1 + 2916) == -1 )
      {
        sub_4344D0(a1, 1);
        if ( *(_DWORD *)(a1 + 676) != dword_911CBC
          || *(_DWORD *)(a1 + 1364) != 1
          || rf_splitscreen_runtime_active
          || rf_multiplayer_runtime_mode )
        {
          *a2 = 3;
          *a3 = 5;
        }
        else
        {
          *a2 = 2;
          *a3 = 4;
        }
      }
      else
      {
        sub_4344D0(a1, 0);
        *a2 = 3;
        *a3 = 5;
        if ( !rf_entity_body_action_is_active(a1, 0x12u) && !rf_entity_body_action_is_active(a1, 0x11u) )
        {
          if ( destination[0] <= 0.0 )
            rf_entity_request_body_action(a1, 0x11u, 1.0, 0, 1);
          else
            rf_entity_request_body_action(a1, 0x12u, 1.0, 0, 1);
        }
      }
    }
    else
    {
      *a2 = 9;
      *a3 = 9;
      if ( destination[0] <= 0.0 )
        rf_entity_request_body_action(a1, 0x13u, 1.0, 0, 1);
      else
        rf_entity_request_body_action(a1, 0x14u, 1.0, 0, 1);
      *(_DWORD *)(a1 + 1980) = 1;
      rf_replicator_arm_milliseconds((int *)(a1 + 1948), 1200);
      rf_replicator_arm_milliseconds((int *)(a1 + 1232), 1200);
      rf_replicator_arm_milliseconds((int *)(a1 + 1236), 1200);
      rf_replicator_arm_milliseconds((int *)(a1 + 1860), 1200);
      rf_replicator_arm_milliseconds((int *)(a1 + 1944), 1200);
      sub_4344D0(a1, 1);
    }
  }
}

