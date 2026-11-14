// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004033C0 sub_4033C0
// UNREALRED VERIFIED [ai-authored-startup-20261028] AI initialization sets current numeric mode +0x280 and current secondary state +0x2B4 to 0; saved mode +0x284 is 2 and saved secondary +0x2B8 is 0. Saved authored waypoint-list index +0x4A8 starts at -1. Verified writes 0x4035C6/0x4035D3 and 0x403715; these current and saved fields are distinct.
// UNREALRED VERIFIED [combat-panic-20261104]: Lateral route floatAI+440=table661218[global6663D8%3], thenincrement; literal sequence(-.5,0,.5). Movement radiusAI+520 uses class+74C ifnonzero elsemax(modelAABBdx,dz)/2; heightAI+524=modelAABBdy. Copied to embedded route start/end nodes. Separate common collisionradius+78 or UE capsulefallback is not this producer. PanicdeadlineAI+254 is not armed/reset here; embedded constructor provides-1.
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: AI dimensions initialized here from564EC0 model AABB: radius uses class+74C when nonzero, else half max(raw X extent,raw Z extent); height raw Y extent. Character tag2 follows562880/5628A0 to566B70 reference mesh. Preserve raw source float bounds; rendered vertices/component scaling/collision capsule are different owners.
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Embedded AI construction writes block+4BC=-1. With the proven Entity AI base+2A0 this is Entity+75C, the carried-body handle tested by437B40 and4344D0. This is a native initialized uncarried state, not evidence of a carry interaction implementation.
// UNREALRED VERIFIED [combat-reaction-20261111]: AI construction initializes selected primary AI+4 and selected secondary AI+8 independently to -1. These are retained selected weapon identifiers, not counts, ammo predicates, or inventory ownership bytes.
// UNREALRED VERIFIED [combat-reaction-primary-none-20261111]: Weapon storage boundaries: constructor loops64 entries to clear AI+18C (Entity+42C) presence bytes and followingAI+1CC (Entity+46C) bytes.4811C0 primary-none outerordinal write may cross that fixed64-entry boundary; actualweaponcount is not the storage bound. Selectedprimary+4 and secondary+8 are independent of both arrays.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Distinct fixed namespaces reset only after native entity resolve succeeds: selectedprimaryAI+4=-1,secondaryAI+8=-1; reserve32 signedDWORDsAI+0C; loaded64 signedDWORDsAI+8C; owned64bytesAI+18C and separate64bytesAI+1CC. AI baseEntity+2A0, so reserveEntity2AC/loaded32C/presence42C. Counters survive403C20 ownership removal; neither name-keyed records nor shared magazine-by-ammo can replace these owners.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Birth timer stores: AI+23C Arm0 then separate AI+230 Arm0 (Entity+4DC versus Entity+4D0). Alarm FDA40 rearms only Entity+4D0. Constructor current/saved mode zero/two fields do not prove defaults for mode timestamp+288 or args+28C/+290; do not fabricate initialized timing before a represented writer.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Complete constructor trace additionally proves AI+2DC Arm0 at40366F (Entity+57C), used406130500ms probe; this is separate from AI230/23C clocks. Constructor tail loads6FC428 and truncates intoAI288; no constant-zero timestamp assumption.28C/290 args and2BC secondary time defaults remain unproved. Initial mode timestamp must capture the pre-normal-load-reset seconds source, or be explicitly unavailable in host constructor.
// UNREALRED VERIFIED [combat-route-operands-20261111] AI embedded base is Entity+2A0 (412740 call412A80 and caller4033C0 owner). Therefore AI+530 and Entity+7D0 are exactly the SAME dword, not separate Goto/strafe flag owners. Keep one retained field across Goto410ED0, constructor flags and40F320 bit8 toggles.
// UNREALRED VERIFIED [combat-ai-birth-phase-20261111] Final ctor store403A68 writesAI288 from trunc(current6FC428). For authored entities this executes inside4811C0->42CB80 during47C6C0 section loading BEFORE normal47D4CE reset. A later host admitted-birth clock sample is not the historical native constructor operand. Constructor writes cannot be replayed after a later40A1B0/40A230 runtime writer tuple; preserve actual initialization/event ordering and unknown operands explicitly.
// UNREALRED VERIFIED [original-target-constructor-operands-20261112]: Only after native entity fullhandle resolve succeeds: at4035A7/4035B2/4035BD AI510/514/518 FLOAT0 initialize Entity7B0/7B4/7B8 activity channels. CurrentAI280(Entity520) and currentAI2B4(Entity554) are0; SAVEDAI284 is2 and savedAI2B8 is0, not aliases of current fields. AI530/Entity7D0 wholeDWORD clears0 at4039E0, then exact case-insensitive class auto turret head OR100000 or auto turret OR20000000. These ctor values precede42EE37 entity-list append and subsequent RFL4811C0 flag/mode writes. Live activity/flag mutation writers are separate from the construction proof.
int __cdecl sub_4033C0(int a1, int a2, char a3)
{
  int result; // eax
  int v4; // eax
  float *v5; // eax
  double v6; // st7
  float copy_result[3]; // [esp+Ch] [ebp-3Ch] BYREF
  float v8[3]; // [esp+18h] [ebp-30h] BYREF
  float v9; // [esp+24h] [ebp-24h]
  float v10; // [esp+28h] [ebp-20h]
  float v11[3]; // [esp+2Ch] [ebp-1Ch] BYREF
  float v12[3]; // [esp+38h] [ebp-10h] BYREF
  int i; // [esp+44h] [ebp-4h]

  result = rf_entity_resolve_handle(a2);
  *(_DWORD *)a1 = result;
  if ( *(_DWORD *)a1 )
  {
    *(_DWORD *)(a1 + 4) = -1;
    *(_DWORD *)(a1 + 8) = -1;
    rf_replicator_arm_milliseconds((int *)(a1 + 536), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 540), 0);
    for ( i = 0; i < 2; ++i )
      rf_replicator_reset((_DWORD *)(a1 + 4 * i + 544));
    *(_BYTE *)(a1 + 552) = 0;
    rf_replicator_arm_milliseconds((int *)(a1 + 736), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 660), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 592), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 628), 0);
    rf_replicator_reset((_DWORD *)(a1 + 632));
    rf_replicator_arm_milliseconds((int *)(a1 + 1188), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 572), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 560), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 1272), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 1276), 0);
    *(_DWORD *)(a1 + 740) = -1;
    rf_replicator_reset((_DWORD *)(a1 + 556));
    *(_DWORD *)(a1 + 620) = 0;
    *(_DWORD *)(a1 + 624) = 0;
    *(_DWORD *)(a1 + 724) = -1;
    *(_DWORD *)(a1 + 728) = -1;
    *(_BYTE *)(a1 + 668) = 0;
    *(_BYTE *)(a1 + 669) = 0;
    rf_replicator_arm_milliseconds((int *)(a1 + 1164), 0);
    *(_DWORD *)(a1 + 704) = -1;
    rf_timestamp4_invalidate((_DWORD *)(a1 + 604));
    *(_DWORD *)(a1 + 608) = 0;
    rf_timestamp4_invalidate((_DWORD *)(a1 + 612));
    *(_DWORD *)(a1 + 616) = 0;
    *(float *)(a1 + 1296) = 0.0;
    *(float *)(a1 + 1300) = 0.0;
    *(float *)(a1 + 1304) = 0.0;
    *(_DWORD *)(a1 + 640) = 0;
    *(_DWORD *)(a1 + 692) = 0;
    *(_DWORD *)(a1 + 644) = 2;
    *(_DWORD *)(a1 + 696) = 0;
    for ( i = 0; i < 64; ++i )
    {
      *(_BYTE *)(i + a1 + 396) = 0;
      *(_BYTE *)(i + a1 + 460) = 0;
      *(_DWORD *)(a1 + 4 * i + 140) = 0;
    }
    for ( i = 0; i < 32; ++i )
      *(_DWORD *)(a1 + 4 * i + 12) = 0;
    rf_replicator_arm_milliseconds((int *)(a1 + 732), 0);
    sub_40BA80((int *)a1, -1);
    sub_40DC00(a1 + 744);
    *(_DWORD *)(a1 + 1020) = 0;
    *(_DWORD *)(a1 + 1024) = 0;
    *(_DWORD *)(a1 + 1048) = *(_DWORD *)(*(_DWORD *)a1 + 44);
    *(float *)(a1 + 1088) = flt_661218[dword_6663D8 % 3];
    ++dword_6663D8;
    *(_DWORD *)(a1 + 636) = 1;
    *(_DWORD *)(a1 + 1184) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 660) + 1824);
    *(_DWORD *)(a1 + 1192) = -1;
    *(_DWORD *)(a1 + 1196) = 0;
    rf_pointer_array_release_storage((void **)(a1 + 524));
    rf_vector3_zero_return_destination((float *)(a1 + 1280));
    *(_DWORD *)(a1 + 684) = 0;
    *(_DWORD *)(a1 + 688) = 0;
    rf_replicator_arm_milliseconds((int *)(a1 + 680), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 1208), 0);
    *(_DWORD *)(a1 + 1212) = -1;
    *(_DWORD *)(a1 + 1200) = -1;
    *(float *)(a1 + 1216) = 200.0;
    rf_replicator_reset((_DWORD *)(a1 + 1220));
    if ( a3 == 1 )
      *(_DWORD *)(a1 + 1308) = 0;
    else
      *(_DWORD *)(a1 + 1308) = rand() % 2;
    *(_DWORD *)(a1 + 1224) = -1;
    *(_DWORD *)(a1 + 1224) = -1;
    rf_replicator_arm_milliseconds((int *)(a1 + 1232), 0);
    rf_replicator_arm_milliseconds((int *)(a1 + 1236), 0);
    v4 = rand();
    rf_replicator_arm_milliseconds((int *)(a1 + 1240), v4 % 30000 + 60000);
    rf_replicator_reset((_DWORD *)(a1 + 1244));
    rf_replicator_arm_milliseconds((int *)(a1 + 1252), 0);
    rf_replicator_reset((_DWORD *)(a1 + 1256));
    v5 = rf_vector3_set_components_return_destination(v8, 0.0, 0.0, 0.0);
    rf_vector_copy((float *)(a1 + 1260), copy_result, v5);
    rf_vector3_default_construct_noop(v12);
    rf_vector3_default_construct_noop(v11);
    rf_model_handle_bounds_aabb_adapter(*(_DWORD *)(*(_DWORD *)a1 + 128), (int)v12, (int)v11);
    *(float *)(a1 + 1316) = v11[1] - v12[1];
    if ( *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 660) + 1868) == 0.0 )
    {
      v10 = v11[0] - v12[0];
      v9 = v11[2] - v12[2];
      if ( v9 >= (double)v10 )
        v6 = v9 * 0.5;
      else
        v6 = v10 * 0.5;
      *(float *)(a1 + 1312) = v6;
    }
    else
    {
      *(float *)(a1 + 1312) = *(float *)(*(_DWORD *)(*(_DWORD *)a1 + 660) + 1868);
    }
    *(_BYTE *)(a1 + 1320) = 0;
    *(float *)(a1 + 1324) = 15.0;
    *(float *)(a1 + 800) = *(float *)(a1 + 1312);
    *(float *)(a1 + 804) = *(float *)(a1 + 1316);
    *(float *)(a1 + 808) = 0.0;
    *(float *)(a1 + 924) = *(float *)(a1 + 1312);
    *(float *)(a1 + 928) = *(float *)(a1 + 1316);
    *(float *)(a1 + 932) = 0.0;
    *(_BYTE *)(a1 + 949) = 0;
    *(_DWORD *)(a1 + 1328) = 0;
    if ( rf_string_equals_case_insensitive(*(_DWORD *)(*(_DWORD *)a1 + 660), "auto turret head") )
      *(_DWORD *)(a1 + 1328) |= 0x100000u;
    if ( rf_string_equals_case_insensitive(*(_DWORD *)(*(_DWORD *)a1 + 660), "auto turret") )
      *(_DWORD *)(a1 + 1328) |= 0x20000000u;
    result = (int)*(float *)&dword_6FC428;
    *(_DWORD *)(a1 + 648) = result;
  }
  return result;
}

