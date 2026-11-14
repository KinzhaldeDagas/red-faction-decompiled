// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042CB80 rf_entity_create_runtime
// UNREALRED VERIFIED [combat-selector-owner-20260930] Entity+0x147C is initialized to -1 at0x42DBBF and again0x42F4F1. This is the unregistered selector case in0x4014F0. A host must not invent a registered preference row for an ordinary entity merely from its spawn ordinal.
// UNREALRED VERIFIED [mission-visibility-20261020] Entity creation option2 sets common-inactive mask0x4000 in construction flags. Option4 separately sets mask0x20000. The RFL loader v130 boolean drives option2; its v169 trailing boolean drives option4. These must not be conflated with rendered visibility or ready/holstered AI fields.
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Initial entity movement owner:445780(gameplayclass+30 Movemode string) ->Entity+858, sentinel7BEB0C ->+85C, then4344D0(1). Runtime current movement classification must remain distinct from authored default. Initial special nano-shield class mutation changes MaxVel to8 and Movemode tohover before these writes; do not generalize strict ordinary-source admission to that unsupported alternate owner.
// UNREALRED VERIFIED [combat-speech-eye-phase-20261111]: Constructor timing before eye setup:138C=current0,1390=pending-1,1394/1398float0,428970bodyweights at42E591,564F30 with actual global frameDelta and lastDWORD1 at42E5B8,then42F670 at42E63A,420870 at42E649 initializes retained7D4. Do not fabricate a common-position initial reference for a present eye or assume standingcache is untouched bindpose. Host birth-frame clock and faithful pose evaluator are explicit backend dependencies.
// UNREALRED VERIFIED [combat-reaction-20261111]: After4033C0, class primary+88 is granted then selected at Entity+2A4; class secondary+8C is granted then selected at Entity+2A8; class melee+90 is granted without replacing either selection. RFL4811C0 subsequently applies authored overrides. Constructor selections therefore precede authored saved-state restoration and weapon overrides.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Native counter construction order after4033C0 reset: classprimary403AB0(-1), explicitprimarywrite+holdingrefresh, then IF itsAmmoID>=0 set reserve=thatweaponactiveMax. Classsecondary403AB0(-1), explicitsecondarywrite, IF AmmoID>=0 set reserve=thatweaponactiveMax. Melee403AB0(-1) without additional maxfill. Latersecondary max overwrite wins sharedpool even ifsmaller, and caller maxfills stillrun ifgrantalreadyowned. Entity147C playerrecord set-1 beforethesegrants.
// UNREALRED VERIFIED [combat-ai-view-prerequisites-20261111] After AI constructor,42DB2E loads class764 and42DB34 storesEntity840 threshold.42E657 suppliesCOMMON48 matrix toEntity7E0 destination copied at42E667. This proves a construction seed, not a universal runtime ActorForward alias after view-specific writers such as411DD0.
// UNREALRED VERIFIED [combat-steering-signature-20261112]: Constructor orientation operands at42DE43:55AC10 extracts from common48 through three explicit output pointers.42DE67 stores2148=(0,localY,0);42DE87 calls445B80(out,entity,inputAngles) then copies result into2172 at42DEA3;42DEAE zeros2196. Raw RFL row preservation and exact extract/filter semantics are needed before this can supply retained7E0; normalized host Rotator is not original input.
// UNREALRED VERIFIED [combat-original-facing-20261112]: Before object setup, except exact case-insensitive class names fighter and robot fly, constructor MUTATES caller native rows: row1=(0,1,0); if ordered abs(dot(row1,row2))>float0.99, row2.x+=double(float0.1) with float store; row0=row1 cross row2; analogous row0.x perturb after its up-dot test; row2=row0 cross row1; then55B770 repair. This precedes setup matrix copies. Later55AC10 extracts COMMON72,2148=(0,heading,0),445B80 rotates/filter-selects PHB into2172;42E651..667 seeds2016 fromCOMMON72 only after initial model/eye/reference setup. No raw9 identity, quaternion or immediate view-update equivalence is implied. After that late matrix seed, the nonzero COMMON-leading array-count gate42ED99, descriptor438010 true (index1 or5), and a clear level/script exception gate together call4D98A0 at42EE0F before42EE37 entity-list append. The shape sweep may publish a changed COMMON3C through4BC330; the initial RFL point need not be the final first-AI point.
// UNREALRED VERIFIED CORRECTION [combat-original-snapdown-20261112]: Supersedes only the earlier combat-original-facing-20261112 phrase "COMMON-leading array-count gate42ED99": ECX at42ED99 is the ENTITY base, so486DE0 reads its cached ROOM pointer at COMMON+0. The same generic first-DWORD accessor at42ECF3 has ECX=class+CEC and reads an array count; these receivers must not be conflated. Non-NULL cached ROOM, descriptor index1/5 (438010), and clear ASCII-case-insensitive logical-level L11S3.rfl / SOURCE SCRIPT cs_parker exception admit4D98A0. The matrix2016 seed precedes this tail; authored FOV840 overwrite481B13 follows return to4811C0. Early4D7A00 resets shape query word, but42DF49..61 ORs entity428 with0x3000 before snapdown: ordinary query flags are0x3004, not4. Late drag140: class MaxVel80==0 writes100; otherwise acc92*mass152/(MaxVel80*(class724 bit0x40?2:1)), with double denominator and one final float store. Early setup drag10 is not the completed constructor drag.
int __cdecl rf_entity_create_runtime(int a1, char *Source, int a3, float *source, float *destination, char a6, int a7)
{
  float *v8; // eax
  float *v9; // eax
  int first_dword; // eax
  int element_address; // eax
  const char *v12; // eax
  int v13; // eax
  const char *v14; // eax
  int v15; // eax
  _DWORD *instance; // eax
  char *v17; // eax
  char *v18; // eax
  float *v19; // eax
  double v20; // st6
  const char *v21; // eax
  int v22; // eax
  const char *v23; // eax
  int v24; // edx
  const char *v25; // eax
  const char *v26; // eax
  int v27; // eax
  _DWORD *v28; // eax
  _DWORD *v29; // ecx
  _DWORD *v30; // ecx
  _DWORD *v31; // edx
  int v32; // eax
  float *element_address_unchecked; // eax
  float v34; // ecx
  const char *v35; // eax
  int v36; // eax
  void *v37; // ecx
  int v38; // eax
  int sound_by_index; // eax
  int v40; // eax
  _DWORD *v41; // eax
  int **v42; // eax
  char *v43; // eax
  _DWORD *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int *v48; // eax
  int *v49; // eax
  char *v50; // eax
  _DWORD *v51; // eax
  int node_adapter; // eax
  char *v53; // eax
  int name; // eax
  int v55; // eax
  char *v56; // eax
  int v57; // eax
  int v58; // eax
  char *v59; // eax
  int v3m_mode1; // eax
  int **v61; // eax
  int v62; // eax
  _DWORD *v63; // eax
  float v64[2]; // [esp-4h] [ebp-2ECh] BYREF
  float *v65; // [esp+4h] [ebp-2E4h]
  float v66; // [esp+8h] [ebp-2E0h]
  int v67; // [esp+Ch] [ebp-2DCh]
  int v68; // [esp+10h] [ebp-2D8h]
  char *v69; // [esp+20h] [ebp-2C8h]
  std::exception *v70; // [esp+24h] [ebp-2C4h]
  std::exception *v71; // [esp+28h] [ebp-2C0h]
  std::exception *v72; // [esp+2Ch] [ebp-2BCh]
  std::exception *v73; // [esp+30h] [ebp-2B8h]
  void *v74; // [esp+34h] [ebp-2B4h]
  const char *v75; // [esp+38h] [ebp-2B0h]
  const char *v76; // [esp+40h] [ebp-2A8h]
  const char *v77; // [esp+44h] [ebp-2A4h]
  int v78; // [esp+48h] [ebp-2A0h]
  int v79; // [esp+4Ch] [ebp-29Ch]
  unsigned __int16 v80; // [esp+52h] [ebp-296h]
  int v81; // [esp+54h] [ebp-294h]
  int v82; // [esp+58h] [ebp-290h]
  unsigned __int16 v83; // [esp+5Eh] [ebp-28Ah]
  int v84; // [esp+60h] [ebp-288h]
  int v85; // [esp+64h] [ebp-284h]
  unsigned __int16 v86; // [esp+6Ah] [ebp-27Eh]
  const void *v87; // [esp+6Ch] [ebp-27Ch]
  float v88; // [esp+70h] [ebp-278h]
  float v89; // [esp+74h] [ebp-274h]
  char *v90; // [esp+78h] [ebp-270h]
  int v91; // [esp+7Ch] [ebp-26Ch]
  void *v92; // [esp+80h] [ebp-268h]
  char *v93; // [esp+84h] [ebp-264h]
  float v94[3]; // [esp+88h] [ebp-260h] BYREF
  float v95[3]; // [esp+94h] [ebp-254h] BYREF
  float v96[3]; // [esp+A0h] [ebp-248h] BYREF
  _DWORD v97[2]; // [esp+ACh] [ebp-23Ch] BYREF
  void *v98[2]; // [esp+B4h] [ebp-234h] BYREF
  void *v99; // [esp+BCh] [ebp-22Ch]
  void *v100; // [esp+C0h] [ebp-228h]
  int v101; // [esp+C4h] [ebp-224h]
  float v102[3]; // [esp+C8h] [ebp-220h] BYREF
  float v103[3]; // [esp+D4h] [ebp-214h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-208h] BYREF
  void *v105; // [esp+ECh] [ebp-1FCh]
  float v106[3]; // [esp+F0h] [ebp-1F8h] BYREF
  void *v107; // [esp+FCh] [ebp-1ECh]
  void *v108; // [esp+100h] [ebp-1E8h]
  int v109; // [esp+104h] [ebp-1E4h]
  float *v110; // [esp+108h] [ebp-1E0h]
  float v111[3]; // [esp+10Ch] [ebp-1DCh] BYREF
  float v112[4]; // [esp+118h] [ebp-1D0h] BYREF
  float v113[3]; // [esp+128h] [ebp-1C0h] BYREF
  float v114[3]; // [esp+134h] [ebp-1B4h] BYREF
  float copy_result[3]; // [esp+140h] [ebp-1A8h] BYREF
  float v116[3]; // [esp+14Ch] [ebp-19Ch] BYREF
  _DWORD *v117; // [esp+158h] [ebp-190h]
  int index_by_name; // [esp+15Ch] [ebp-18Ch]
  int *runtime; // [esp+160h] [ebp-188h]
  int v120; // [esp+164h] [ebp-184h]
  char v121[12]; // [esp+168h] [ebp-180h] BYREF
  float v122[6]; // [esp+174h] [ebp-174h] BYREF
  char v123; // [esp+18Fh] [ebp-159h]
  int attached_to_model_prop; // [esp+190h] [ebp-158h]
  int v125; // [esp+194h] [ebp-154h]
  float *v126; // [esp+198h] [ebp-150h]
  int v127; // [esp+19Ch] [ebp-14Ch]
  int v128; // [esp+1A0h] [ebp-148h]
  _DWORD v129[3]; // [esp+1A4h] [ebp-144h] BYREF
  _DWORD *v130; // [esp+1B0h] [ebp-138h]
  int v131; // [esp+1B4h] [ebp-134h]
  float v132; // [esp+1B8h] [ebp-130h]
  float v133[3]; // [esp+1BCh] [ebp-12Ch] BYREF
  float v134; // [esp+1C8h] [ebp-120h] BYREF
  float v135; // [esp+1CCh] [ebp-11Ch]
  float v136; // [esp+1D0h] [ebp-118h]
  int j; // [esp+1D4h] [ebp-114h]
  _DWORD v138[2]; // [esp+1D8h] [ebp-110h] BYREF
  int animation_record_by_name; // [esp+1E0h] [ebp-108h]
  float v140[6]; // [esp+1E4h] [ebp-104h] BYREF
  int k; // [esp+1FCh] [ebp-ECh]
  int v142; // [esp+200h] [ebp-E8h]
  int v143; // [esp+204h] [ebp-E4h]
  float v144; // [esp+208h] [ebp-E0h] BYREF
  int entity; // [esp+20Ch] [ebp-DCh]
  int v146; // [esp+210h] [ebp-D8h]
  int v147; // [esp+214h] [ebp-D4h]
  float v148; // [esp+218h] [ebp-D0h] BYREF
  float v149; // [esp+21Ch] [ebp-CCh] BYREF
  float input_vector; // [esp+220h] [ebp-C8h] BYREF
  float v151; // [esp+224h] [ebp-C4h] BYREF
  float v152; // [esp+228h] [ebp-C0h] BYREF
  void *v153[39]; // [esp+22Ch] [ebp-BCh] BYREF
  int i; // [esp+2C8h] [ebp-20h]
  char v155; // [esp+2CFh] [ebp-19h]
  _DWORD *definition_pointer; // [esp+2D0h] [ebp-18h]
  int v157; // [esp+2D4h] [ebp-14h]
  char *v158; // [esp+2D8h] [ebp-10h]
  int v159; // [esp+2E4h] [ebp-4h]

  v155 = a6 & 1;
  if ( a1 < 0 || a1 > dword_681E14 )
    return 0;
  if ( rf_multiplayer_runtime_mode == 1 )
    a6 |= 8u;
  v147 = -1;
  v157 = -1;
  if ( (a6 & 1) != 0 && a7 > -1 )
  {
    v147 = unk_77D764[80 * a7];
    v157 = unk_77D768[80 * a7];
  }
  v142 = (int)&rf_entity_info_definitions[5396 * a1];
  if ( v147 < 0 )
    v90 = nullptr;
  else
    v90 = &rf_entity_info_definitions[5396 * v147];
  v158 = v90;
  v143 = 0;
  if ( *(_DWORD *)(v142 + 148) == 3 )
    v143 = 0x10000;
  if ( v155 )
    v143 |= 8u;
  if ( (a6 & 2) != 0 )
    v143 |= 0x4000u;
  if ( (a6 & 4) != 0 )
    v143 |= 0x20000u;
  if ( rf_rf_string_not_equals_cstring_case_insensitive(v142 + 48, "fighter")
    && rf_rf_string_not_equals_cstring_case_insensitive(v142 + 48, "robot fly") )
  {
    rf_vector3_set_components_thiscall(destination + 3, 0.0, 1.0, 0.0);
    v89 = fabs(rf_vector_dot(destination + 3, destination + 6));
    if ( v89 > 0.9900000095367432 )
      destination[6] = destination[6] + 0.1000000014901161;
    v8 = rf_vector_cross(destination + 3, v116, destination + 6);
    rf_vector_copy(destination, copy_result, v8);
    v88 = fabs(rf_vector_dot(destination + 3, destination));
    if ( v88 > 0.9900000095367432 )
      *destination = *destination + 0.1000000014901161;
    v9 = rf_vector_cross(destination, v114, destination + 3);
    rf_vector_copy(destination + 6, v113, v9);
    rf_matrix3_rebuild_basis_from_forward_in_place((char *)destination);
  }
  rf_object_setup152_construct_members((char *)v153);
  v159 = 0;
  memset(v153, 0, 0x98u);
  if ( v158 )
    v87 = v158 + 8;
  else
    v87 = (const void *)(v142 + 8);
  LODWORD(v112[3]) = v87;
  v153[0] = (void *)rf_string_object_c_str_or_empty(v87);
  v153[1] = *(void **)(v142 + 148);
  v153[5] = *(void **)(v142 + 104);
  *(float *)&v153[33] = -1.0;
  rf_vector_copy((float *)&v153[15], v112, source);
  rf_matrix3_copy((float *)&v153[18], destination);
  *(float *)&v153[3] = 10.0;
  v153[4] = (void *)*(unsigned __int8 *)(v142 + 152);
  if ( v158 )
    v146 = (int)v158;
  else
    v146 = v142;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(v146 + 3308));
    if ( i >= first_dword )
      break;
    rf_vector_prefix_construct_noop(v140);
    element_address = rf_inline_array40_get_element_address((void *)(v146 + 3308), i);
    rf_vector_copy(v140, v111, (const float *)(element_address + 24));
    v140[3] = *(float *)rf_inline_array40_get_element_address((void *)(v146 + 3308), i);
    v140[4] = *(float *)(rf_inline_array40_get_element_address((void *)(v146 + 3308), i) + 16);
    v140[5] = *(float *)(rf_inline_array40_get_element_address((void *)(v146 + 3308), i) + 20);
    v110 = v64;
    rf_record24_copy_construct_six_floats(v64, v140);
    rf_array24_append_record_by_value((int *)&v153[34], v64[0], SLODWORD(v64[1]), (int)v65, SLODWORD(v66), v67, v68);
  }
  v153[37] = (void *)0x80000000;
  if ( (*(_DWORD *)(v142 + 1832) & 2) != 0 )
  {
    v153[37] = (void *)((int)v153[37] | 0x70);
  }
  else if ( (*(_DWORD *)(v142 + 1828) & 0x40000) == 0 )
  {
    v153[37] = (void *)((int)v153[37] | 0x70);
  }
  if ( *(_DWORD *)(v142 + 436) == 4 )
    v153[37] = (void *)((int)v153[37] | 0x1000);
  if ( (*(_DWORD *)(v142 + 1828) & 0x4000) != 0 && v155 == 1 )
    v153[37] = (void *)((int)v153[37] | 0x80);
  if ( (*(_DWORD *)(v142 + 1828) & 0x200) != 0
    || (*(_DWORD *)(v142 + 1828) & 0x1000) != 0
    || (*(_DWORD *)(v142 + 1828) & 0x400000) != 0 )
  {
    v153[37] = (void *)((int)v153[37] | 0x4000);
  }
  else
  {
    v153[37] = (void *)((int)v153[37] | 8);
  }
  if ( rf_multiplayer_runtime_mode && (a6 & 1) != 0 )
    v153[37] = (void *)((int)v153[37] | 0x8000);
  entity = rf_object_create(0, a1, a3, (int)v153, v143, 0);
  if ( entity )
  {
    rf_light_get_ambient_rgb_floats(&v144, &v148, &v149);
    v85 = v86 | 0xC00;
    v84 = (int)(v144 * 255.0);
    *(_BYTE *)(entity + 5236) = v84;
    v82 = v83 | 0xC00;
    v81 = (int)(v148 * 255.0);
    *(_BYTE *)(entity + 5237) = v81;
    v79 = v80 | 0xC00;
    v78 = (int)(v149 * 255.0);
    *(_BYTE *)(entity + 5238) = v78;
    *(_DWORD *)(entity + 5168) = 0;
    for ( i = 0; i < 23; ++i )
    {
      *(_DWORD *)(entity + 16 * i + 2276) = -1;
      *(_DWORD *)(entity + 16 * i + 2288) = -1;
      *(_DWORD *)(entity + 16 * i + 2284) = -1;
    }
    for ( i = 0; i < 45; ++i )
    {
      *(_DWORD *)(entity + 16 * i + 2644) = -1;
      *(_DWORD *)(entity + 16 * i + 2656) = -1;
      *(_DWORD *)(entity + 16 * i + 2652) = -1;
    }
    *(_DWORD *)(entity + 2064) = 0;
    *(_DWORD *)(entity + 2068) = 0;
    *(_DWORD *)(entity + 660) = v142;
    if ( v158 )
      *(_DWORD *)(entity + 668) = v158;
    else
      *(_DWORD *)(entity + 668) = v142;
    *(_DWORD *)(entity + 664) = a1;
    definition_pointer = (_DWORD *)rf_model_handle_get_definition_pointer(*(_DWORD *)(entity + 128));
    for ( i = 0; i < 64; ++i )
    {
      rf_string_construct_empty(v138);
      LOBYTE(v159) = 1;
      *(_DWORD *)(entity + 4 * i + 4452) = 0;
      *(_DWORD *)(entity + 4 * i + 4708) = 0;
      if ( *(int *)(*(_DWORD *)(entity + 660) + 4 * i + 1896) > 0 )
      {
        v108 = operator new(0x170u);
        *(_DWORD *)(entity + 4 * i + 4452) = v108;
        for ( j = 0; j < 23; ++j )
        {
          if ( v158 )
            animation_record_by_name = rf_entity_info_find_animation_record_by_name(v138, v157, i, 8 * j + 6829200, 1);
          else
            animation_record_by_name = rf_entity_info_find_animation_record_by_name(
                                         v138,
                                         *(_DWORD *)(entity + 664),
                                         i,
                                         8 * j + 6829200,
                                         1);
          if ( animation_record_by_name == -1 )
          {
            *(_DWORD *)(16 * j + *(_DWORD *)(entity + 4 * i + 4452)) = -1;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4452) + 16 * j + 4) = -1;
          }
          else
          {
            v68 = 1;
            v67 = 1;
            v12 = rf_string_object_c_str_or_empty(v138);
            v13 = rf_animation_registry_load(definition_pointer, (int)v12, v67, v68);
            *(_DWORD *)(16 * j + *(_DWORD *)(entity + 4 * i + 4452)) = v13;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4452) + 16 * j + 4) = animation_record_by_name;
          }
          *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4452) + 16 * j + 8) = -1;
        }
      }
      if ( *(int *)(*(_DWORD *)(entity + 660) + 4 * i + 2152) > 0 )
      {
        v107 = operator new(0x2D0u);
        *(_DWORD *)(entity + 4 * i + 4708) = v107;
        for ( j = 0; j < 45; ++j )
        {
          if ( v158 )
            animation_record_by_name = rf_entity_info_find_animation_record_by_name(v138, v157, i, 8 * j + 6828840, 0);
          else
            animation_record_by_name = rf_entity_info_find_animation_record_by_name(
                                         v138,
                                         *(_DWORD *)(entity + 664),
                                         i,
                                         8 * j + 6828840,
                                         0);
          if ( animation_record_by_name == -1 )
          {
            *(_DWORD *)(16 * j + *(_DWORD *)(entity + 4 * i + 4708)) = -1;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4708) + 16 * j + 4) = -1;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4708) + 16 * j + 8) = -1;
          }
          else
          {
            v68 = 1;
            *(float *)&v67 = 0.0;
            v14 = rf_string_object_c_str_or_empty(v138);
            v15 = rf_animation_registry_load(definition_pointer, (int)v14, v67, v68);
            *(_DWORD *)(16 * j + *(_DWORD *)(entity + 4 * i + 4708)) = v15;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4708) + 16 * j + 4) = animation_record_by_name;
            *(_DWORD *)(*(_DWORD *)(entity + 4 * i + 4708) + 16 * j + 8) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(entity + 660)
                                                                                                 + 4 * i
                                                                                                 + 2664)
                                                                                     + 52 * animation_record_by_name
                                                                                     + 16);
          }
        }
      }
      LOBYTE(v159) = 0;
      rf_string_destroy_buffer(v138);
    }
    rf_string_assign_from_cstr((_DWORD *)(entity + 24), Source);
    if ( rf_multiplayer_runtime_mode )
      *(float *)(entity + 56) = 0.0;
    else
      *(float *)(entity + 56) = *(float *)(*(_DWORD *)(entity + 660) + 72);
    rf_vector_copy((float *)(entity + 5048), v106, (const float *)(entity + 96));
    *(_DWORD *)(entity + 2128) = 0;
    if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(v142 + 1828)) != 0 )
    {
      v105 = operator new(8u);
      *(_DWORD *)(entity + 2128) = v105;
      **(float **)(entity + 2128) = *(float *)(*(_DWORD *)(entity + 660) + 80);
      instance = rf_vfx_load_instance("NanoShieldConstant.vfx", (int)byte_98967F);
      *(_DWORD *)(*(_DWORD *)(entity + 2128) + 4) = instance;
      rf_model_handle_set_cyclic_mix_adapter(*(int **)(*(_DWORD *)(entity + 2128) + 4), 0, 1.0);
      *(float *)(*(_DWORD *)(entity + 660) + 80) = 8.0;
      *(float *)(entity + 2240) = *(float *)(*(_DWORD *)(entity + 660) + 80);
      rf_string_assign_from_cstr((_DWORD *)(v142 + 48), "hover");
      if ( dword_681E64 == -1 )
      {
        dword_681E64 = sub_507610("Nano Shield Small Hit");
        rf_vclip_preload_bitmap_and_vfx_stub(dword_681E64);
      }
      if ( unk_681E74 == -1 )
      {
        unk_681E74 = sub_507610("Nano Shield Big Hit");
        rf_vclip_preload_bitmap_and_vfx_stub(unk_681E74);
      }
      if ( unk_681E24 == -1 )
      {
        unk_681E24 = sub_507610("Nano Shield Destroy");
        rf_vclip_preload_bitmap_and_vfx_stub(unk_681E24);
      }
    }
    if ( (*(_DWORD *)(v142 + 1832) & 1) == 0 )
      *(_DWORD *)(entity + 124) |= 0x20000u;
    if ( rf_entity_class_has_angular_decay_flags(entity) )
    {
      *(float *)(entity + 136) = flt_661518;
      *(float *)(entity + 144) = 0.1;
      v132 = *(float *)(entity + 152) / 12.0;
      rf_vector3_default_construct_noop(v133);
      rf_vector3_default_construct_noop(&v134);
      rf_model_handle_bounds_aabb_adapter(*(_DWORD *)(entity + 128), (int)v133, (int)&v134);
      rf_vector_subtract_in_place(&v134, v133);
      rf_vector3_zero_return_destination((float *)(entity + 156));
      *(float *)(entity + 156) = (v136 * v136 + v135 * v135) * v132;
      rf_vector3_zero_return_destination((float *)(entity + 168));
      *(float *)(entity + 172) = (v136 * v136 + v134 * v134) * v132;
      rf_vector3_zero_return_destination((float *)(entity + 180));
      *(float *)(entity + 188) = (v134 * v134 + v135 * v135) * v132;
      rf_matrix3_inverse_in_place_if_nonsingular((float *)(entity + 156));
    }
    rf_entity_build_sequential_interface_node_relations(entity);
    sub_430310(entity);
    sub_4033C0(entity + 672, *(_DWORD *)(entity + 44), v155);
    *(float *)(entity + 2112) = *(float *)(v142 + 1892);
    if ( *(float *)(v142 + 68) >= 0.0 )
    {
      *(float *)(entity + 52) = *(float *)(v142 + 68);
    }
    else
    {
      *(float *)(entity + 52) = 100.0;
      *(_DWORD *)(entity + 124) |= 4u;
    }
    rf_replicator_reset((_DWORD *)(entity + 2072));
    *(_DWORD *)(entity + 2080) = -1;
    *(_DWORD *)(entity + 2076) = -1;
    *(_DWORD *)(entity + 5244) = -1;
    if ( *(_DWORD *)(v142 + 136) != -1 )
    {
      rf_entity_inventory_grant_weapon((int *)(entity + 672), *(_DWORD *)(v142 + 136), -1);
      *(_DWORD *)(entity + 676) = *(_DWORD *)(v142 + 136);
      rf_entity_restore_action_tables_and_apply_weapon_overrides(entity, *(_DWORD *)(entity + 676));
      if ( dword_912024[340 * *(_DWORD *)(v142 + 136)] >= 0 )
        *(_DWORD *)(entity + 4 * dword_912024[340 * *(_DWORD *)(v142 + 136)] + 684) = unk_912260[340
                                                                                               * *(_DWORD *)(v142 + 136)];
    }
    if ( *(_DWORD *)(v142 + 140) != -1 )
    {
      rf_entity_inventory_grant_weapon((int *)(entity + 672), *(_DWORD *)(v142 + 140), -1);
      *(_DWORD *)(entity + 680) = *(_DWORD *)(v142 + 140);
      if ( dword_912024[340 * *(_DWORD *)(v142 + 140)] >= 0 )
        *(_DWORD *)(entity + 4 * dword_912024[340 * *(_DWORD *)(v142 + 140)] + 684) = unk_912260[340
                                                                                               * *(_DWORD *)(v142 + 140)];
    }
    if ( *(_DWORD *)(v142 + 144) != -1 )
      rf_entity_inventory_grant_weapon((int *)(entity + 672), *(_DWORD *)(v142 + 144), -1);
    if ( rf_weapon_is_melee(*(_DWORD *)(entity + 676)) )
      *(_DWORD *)(entity + 1980) = 0;
    *(_DWORD *)(entity + 2100) = -1;
    *(float *)(entity + 2248) = 1.0;
    v17 = (char *)rf_string_object_c_str_or_empty((const void *)(v142 + 48));
    v18 = sub_445780(v17);
    *(_DWORD *)(entity + 2136) = v18;
    if ( *(_DWORD *)(*(_DWORD *)(entity + 2136) + 4) == 10 )
      *(_DWORD *)(entity + 424) &= ~0x10u;
    *(_DWORD *)(entity + 2140) = &unk_7BEB0C;
    sub_4344D0(entity, 1);
    rf_vector3_default_construct_noop(&input_vector);
    rf_matrix3_extract_euler_angles_retail((float *)(entity + 72), &input_vector, &v152, &v151);
    rf_vector3_set_components_thiscall((float *)(entity + 2148), 0.0, v151, 0.0);
    v19 = rf_entity_rotate_then_filter_view_offset_axes(out_vector, entity, &input_vector);
    rf_vector_copy((float *)(entity + 2172), v103, v19);
    rf_vector3_zero_return_destination((float *)(entity + 2196));
    *(_BYTE *)(entity + 1824) = (*(_DWORD *)(v142 + 1828) & 0x4000) != 0 && v155 == 1;
    *(float *)(entity + 1828) = 0.0;
    *(float *)(entity + 1832) = 0.0;
    *(float *)(entity + 1800) = 0.0;
    *(float *)(entity + 1804) = 0.0;
    *(float *)(entity + 1808) = 0.0;
    rf_vector3_zero_return_destination((float *)(entity + 1812));
    *(_DWORD *)(entity + 428) |= 0x3000u;
    if ( *(float *)(*(_DWORD *)(entity + 660) + 80) == 0.0 )
    {
      *(float *)(entity + 140) = 100.0;
    }
    else
    {
      if ( (*(_DWORD *)(*(_DWORD *)(entity + 660) + 1828) & 0x40) != 0 )
        v20 = *(float *)(*(_DWORD *)(entity + 660) + 80) * 2.0;
      else
        v20 = *(float *)(*(_DWORD *)(entity + 660) + 80) * 1.0;
      *(float *)(entity + 140) = *(float *)(*(_DWORD *)(entity + 660) + 92) * *(float *)(entity + 152) / v20;
    }
    rf_vector3_zero_return_destination((float *)(entity + 2208));
    *(_DWORD *)(entity + 2220) = 0;
    if ( rf_entity_admits_speech_body_actions(entity) )
    {
      rf_string_construct_empty(v129);
      LOBYTE(v159) = 2;
      v130 = (_DWORD *)rf_model_handle_get_definition_pointer(*(_DWORD *)(entity + 128));
      for ( i = 0; i < 23; ++i )
      {
        if ( v158 )
          v131 = rf_entity_info_find_animation_record_by_name(v129, v157, -1, 8 * i + 6829200, 1);
        else
          v131 = rf_entity_info_find_animation_record_by_name(v129, *(_DWORD *)(entity + 664), -1, 8 * i + 6829200, 1);
        if ( v131 == -1 )
        {
          *(_DWORD *)(entity + 16 * i + 2276) = -1;
          *(_DWORD *)(entity + 16 * i + 2280) = -1;
        }
        else
        {
          v68 = 1;
          v67 = 1;
          v21 = rf_string_object_c_str_or_empty(v129);
          v22 = rf_animation_registry_load(v130, (int)v21, v67, v68);
          *(_DWORD *)(entity + 16 * i + 2276) = v22;
          *(_DWORD *)(entity + 16 * i + 2280) = v131;
          if ( v158 )
          {
            v127 = *(_DWORD *)(*((_DWORD *)v158 + 471) + 52 * v131 + 20);
            for ( k = 0; k < v127; ++k )
            {
              v24 = 52 * v131 + *(_DWORD *)(*(_DWORD *)(entity + 660) + 1884);
              v68 = 52 * v131;
              v68 = *(int *)(v24 + 12 * k + 32);
              v25 = rf_string_object_c_str_or_empty((const void *)(52 * v131 + *((_DWORD *)v158 + 471) + 12 * k + 24));
              rf_animation_trigger_ensure(v130, *(_DWORD *)(entity + 16 * i + 2276), v25, *(float *)&v68);
            }
          }
          else
          {
            v128 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(entity + 660) + 1884) + 52 * v131 + 20);
            for ( k = 0; k < v128; ++k )
            {
              v68 = 52 * v131 + *(_DWORD *)(*(_DWORD *)(entity + 660) + 1884);
              v68 = *(int *)(v68 + 12 * k + 32);
              v23 = rf_string_object_c_str_or_empty((const void *)(52 * v131
                                                                 + *(_DWORD *)(*(_DWORD *)(entity + 660) + 1884)
                                                                 + 12 * k
                                                                 + 24));
              rf_animation_trigger_ensure(v130, *(_DWORD *)(entity + 16 * i + 2276), v23, *(float *)&v68);
            }
          }
        }
      }
      for ( i = 0; i < 45; ++i )
      {
        if ( v158 )
          v131 = rf_entity_info_find_animation_record_by_name(v129, v157, -1, 8 * i + 6828840, 0);
        else
          v131 = rf_entity_info_find_animation_record_by_name(v129, *(_DWORD *)(entity + 664), -1, 8 * i + 6828840, 0);
        if ( v131 == -1 )
        {
          *(_DWORD *)(entity + 16 * i + 2644) = -1;
          *(_DWORD *)(entity + 16 * i + 2648) = -1;
          *(_DWORD *)(entity + 16 * i + 2652) = -1;
        }
        else
        {
          v68 = 1;
          *(float *)&v67 = 0.0;
          v26 = rf_string_object_c_str_or_empty(v129);
          v27 = rf_animation_registry_load(v130, (int)v26, v67, v68);
          *(_DWORD *)(entity + 16 * i + 2644) = v27;
          *(_DWORD *)(entity + 16 * i + 2648) = v131;
          *(_DWORD *)(entity + 16 * i + 2652) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(entity + 660) + 1888)
                                                          + 52 * v131
                                                          + 16);
        }
      }
      for ( i = 0; i < 23; ++i )
      {
        v28 = (_DWORD *)(entity + 16 * i + 2276);
        v29 = (_DWORD *)(entity + 16 * i + 3364);
        *v29 = *v28;
        v29[1] = v28[1];
        v29[2] = v28[2];
        v29[3] = v28[3];
      }
      for ( i = 0; i < 45; ++i )
      {
        v30 = (_DWORD *)(entity + 16 * i + 2644);
        v31 = (_DWORD *)(entity + 16 * i + 3732);
        *v31 = *v30;
        v31[1] = v30[1];
        v31[2] = v30[2];
        v31[3] = v30[3];
      }
      v129[2] = rf_model_handle_get_runtime_pointer(*(int **)(entity + 128));
      *(_DWORD *)(entity + 5004) = 0;
      *(_DWORD *)(entity + 5008) = -1;
      *(float *)(entity + 5012) = 0.0;
      *(float *)(entity + 5016) = 0.0;
      rf_entity_update_body_state_transition(entity);
      v68 = 1;
      *(float *)&v67 = 0.0;
      v66 = 0.0;
      v65 = nullptr;
      rf_vfx_update_instance(*(int **)(entity + 128), rf_frame_delta_seconds, 0, 0, 0, 1);
      LOBYTE(v159) = 0;
      rf_string_destroy_buffer(v129);
    }
    else
    {
      for ( i = 0; i < 23; ++i )
        *(_DWORD *)(entity + 16 * i + 2276) = -1;
      for ( i = 0; i < 45; ++i )
        *(_DWORD *)(entity + 16 * i + 2644) = -1;
    }
    sub_42F670((int *)entity);
    sub_420870(entity);
    rf_matrix3_copy((float *)(entity + 2016), (const float *)(entity + 72));
    for ( i = 0; ; ++i )
    {
      v32 = rf_receiver_get_first_dword((void *)(entity + 388));
      if ( i >= v32 )
        break;
      v68 = rf_inline_array40_get_element_address((void *)(*(_DWORD *)(entity + 668) + 3308), i) + 24;
      *(float *)&v67 = COERCE_FLOAT(v102);
      element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(entity + 388), i);
      rf_vector_copy(element_address_unchecked, (float *)v67, (const float *)v68);
    }
    *(_DWORD *)(entity + 2052) = -1;
    if ( (int)rf_string_length_from_cstr((const char **)(v142 + 260)) > 0 )
    {
      *(float *)&v68 = 1.0;
      *(float *)&v67 = 1.0;
      v66 = v34;
      v66 = *(float *)(v142 + 268);
      v35 = rf_string_object_c_str_or_empty((const void *)(v142 + 260));
      v36 = rf_ambient_sound_resource_register((int)v35, v66, *(float *)&v67, *(float *)&v68);
      v37 = (void *)v142;
      *(_DWORD *)(v142 + 256) = v36;
      if ( *(int *)(v142 + 256) >= 0 )
      {
        v68 = (int)v37;
        v38 = rf_ambient_voice_reserve_frontend_slot(
                *(_DWORD *)(v142 + 256),
                (float *)(entity + 60),
                *(float *)(v142 + 272));
        *(_DWORD *)(entity + 2052) = v38;
      }
    }
    if ( *(int *)(v142 + 316) < 0 )
    {
      *(_DWORD *)(entity + 2060) = -1;
    }
    else
    {
      *(float *)&v68 = 0.0;
      *(float *)&v67 = COERCE_FLOAT(&unk_17F10B0);
      v66 = 1.0;
      v65 = (float *)(entity + 60);
      sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(v142 + 316), 0);
      v40 = rf_gamesound_play_positional_event(sound_by_index, v65, v66, v67, v68);
      *(_DWORD *)(entity + 2060) = v40;
    }
    rf_replicator_arm_milliseconds((int *)(entity + 2096), 0);
    *(_DWORD *)(entity + 2092) = -1;
    *(_DWORD *)(entity + 2108) = -1;
    *(_DWORD *)(entity + 5228) = -1;
    *(_DWORD *)(entity + 2116) = -1;
    *(_DWORD *)(entity + 2056) = -1;
    *(_DWORD *)(entity + 2084) = -1;
    *(_DWORD *)(entity + 2088) = -1;
    *(_DWORD *)(entity + 2104) = -1;
    *(_DWORD *)(entity + 5076) = -1;
    *(_DWORD *)(entity + 5080) = 0;
    rf_replicator_arm_milliseconds((int *)(entity + 4972), 0);
    rf_replicator_reset((_DWORD *)(entity + 4980));
    *(_DWORD *)(entity + 4984) = -1;
    *(float *)(entity + 5044) = 1.0;
    for ( i = 0; i < *(_DWORD *)(v142 + 1652); ++i )
    {
      v77 = (const char *)(v142 + 32 * i + 628);
      v76 = (const char *)(v142 + 32 * i + 629);
      v77 += strlen(v77);
      v75 = (const char *)(++v77 - v76);
      if ( v77 == v76 )
      {
        rf_pointer_array_append_dword((_DWORD *)(entity + 2264), 0);
      }
      else
      {
        v41 = rf_vfx_load_instance((char *)(v142 + 32 * i + 628), (int)byte_98967F);
        rf_pointer_array_append_dword((_DWORD *)(entity + 2264), (int)v41);
        *(float *)&v68 = 1.0;
        *(float *)&v67 = 0.0;
        v42 = (int **)sub_552200((_DWORD *)(entity + 2264), i);
        rf_model_handle_set_cyclic_mix_adapter(*v42, v67, *(float *)&v68);
      }
    }
    if ( rf_rf_string_not_equals_cstring_case_insensitive(v142 + 5068, (char *)&byte_631AB3) )
    {
      *(float *)&v68 = COERCE_FLOAT(byte_98967F);
      v43 = (char *)rf_string_object_c_str_or_empty((const void *)(v142 + 5068));
      v44 = rf_vfx_load_instance(v43, v68);
      *(_DWORD *)(entity + 2124) = v44;
      rf_model_handle_set_cyclic_mix_adapter(*(int **)(entity + 2124), 0, 1.0);
    }
    else
    {
      *(_DWORD *)(entity + 2124) = 0;
    }
    for ( i = 0; ; ++i )
    {
      v45 = rf_receiver_get_first_dword((void *)(v142 + 1804));
      if ( i >= v45 )
        break;
      v126 = (float *)dword_867800[*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1804), i)];
      if ( v126 )
      {
        v68 = 1;
        *(float *)&v67 = 0.0;
        v46 = rf_receiver_get_first_dword((void *)entity);
        v125 = rf_particle_emitter_create(*(_DWORD *)(entity + 44), v126, v46, v67, v68);
        if ( v125 )
        {
          *(_DWORD *)(v125 + 336) = *(_DWORD *)(entity + 616);
          *(_DWORD *)(entity + 616) = v125;
        }
      }
    }
    for ( i = 0; ; ++i )
    {
      v47 = rf_receiver_get_first_dword((void *)(v142 + 1656));
      if ( i >= v47 )
        break;
      if ( *(int *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1692), i) >= 0
        && *(int *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1656), i) >= 0 )
      {
        v48 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1692), i);
        v68 = rf_inline_pointer_array_find_first((_DWORD *)(v142 + 1728), *v48) > -1;
        v67 = *(int *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1692), i);
        v49 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(v142 + 1656), i);
        attached_to_model_prop = rf_glare_create_attached_to_model_prop(*(_DWORD *)(entity + 44), *v49, v67, v68);
        if ( attached_to_model_prop )
          rf_pointer_array_append_dword((_DWORD *)(entity + 5144), attached_to_model_prop);
      }
    }
    rf_replicator_arm_milliseconds((int *)(entity + 4976), 0);
    *(_DWORD *)(entity + 4964) = -1;
    *(_DWORD *)(entity + 4968) = -1;
    *(_DWORD *)(entity + 2120) = 0;
    if ( (int)rf_string_length_from_cstr((const char **)(v142 + 1860)) > 0 )
    {
      *(float *)&v68 = COERCE_FLOAT(byte_98967F);
      v50 = (char *)rf_string_object_c_str_or_empty((const void *)(v142 + 1860));
      v51 = rf_vfx_load_instance(v50, v68);
      *(_DWORD *)(entity + 2120) = v51;
    }
    rf_replicator_arm_milliseconds((int *)(entity + 4988), 0);
    *(_DWORD *)(entity + 4992) = 0;
    *(float *)(entity + 5060) = 0.0;
    *(float *)(entity + 5064) = 0.0;
    v101 = rf_receiver_get_first_dword((void *)(*(_DWORD *)(entity + 668) + 3308));
    v99 = operator new(12 * v101);
    LOBYTE(v159) = 3;
    if ( v99 )
    {
      rf_vector_construct_no_unwind((char *)v99, 0xCu, v101, rf_vector3_default_construct_noop);
      v74 = v99;
    }
    else
    {
      v74 = nullptr;
    }
    v100 = v74;
    LOBYTE(v159) = 0;
    *(_DWORD *)(entity + 5084) = v74;
    rf_entity_update_allocated_sphere_center_positions(entity);
    if ( rf_receiver_get_first_dword((void *)entity) )
    {
      v123 = 0;
      if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L11S3.rfl")
        && rf_string_equals_case_insensitive(entity + 24, "cs_parker") )
      {
        v123 = 1;
      }
      if ( sub_438010(entity) && !v123 )
        rf_object_snap_down_using_physics_shape_sweep(entity);
    }
    *(_DWORD *)(entity + 5100) = 0;
    *(_DWORD *)(entity + 5104) = 0;
    *(_DWORD *)(entity + 656) = unk_682120;
    *(_DWORD *)(entity + 652) = &unk_681E90;
    *(_DWORD *)(unk_682120 + 652) = entity;
    unk_682120 = entity;
    ++unk_681E10;
    *(_DWORD *)(entity + 4996) = -1;
    *(_DWORD *)(entity + 5000) = -1;
    if ( !v155 )
    {
      rf_timestamp_arm_random_inclusive_milliseconds((int *)(entity + 4976), 5000, 30000);
      for ( i = 0; i < 64; ++i )
      {
        if ( unk_912088[340 * i] > 0 )
          *(_DWORD *)(entity + 4 * i + 812) = rand() % (unk_912088[340 * i] - 2) + 2;
      }
    }
    rf_replicator_arm_milliseconds((int *)(entity + 2236), 0);
    node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(entity + 128), "mouth");
    *(_DWORD *)(entity + 5108) = node_adapter;
    if ( *(int *)(entity + 5108) <= -1 )
    {
      *(_DWORD *)(entity + 5112) = 0;
    }
    else
    {
      if ( (*(_DWORD *)(*(_DWORD *)(entity + 660) + 1832) & 0x20) != 0 )
      {
        v68 = 1;
        *(float *)&v67 = 0.0;
        v66 = COERCE_FLOAT(rf_receiver_get_first_dword((void *)entity));
        v73 = (std::exception *)rf_string_construct_from_cstr(v98, "slime drool");
        v72 = v73;
        LOBYTE(v159) = 4;
        v53 = (char *)rf_string_object_c_str_or_empty(v73);
        name = rf_particle_emitter_definition_find_name(v53);
        v55 = rf_particle_emitter_create(*(_DWORD *)(entity + 44), (float *)dword_867800[name], SLODWORD(v66), v67, v68);
        *(_DWORD *)(entity + 5112) = v55;
        LOBYTE(v159) = 0;
        rf_string_destroy_buffer(v98);
      }
      else
      {
        v68 = 1;
        *(float *)&v67 = 0.0;
        v66 = COERCE_FLOAT(rf_receiver_get_first_dword((void *)entity));
        v71 = (std::exception *)rf_string_construct_from_cstr(v97, "player breath");
        v70 = v71;
        LOBYTE(v159) = 5;
        v56 = (char *)rf_string_object_c_str_or_empty(v71);
        v57 = rf_particle_emitter_definition_find_name(v56);
        v58 = rf_particle_emitter_create(*(_DWORD *)(entity + 44), (float *)dword_867800[v57], SLODWORD(v66), v67, v68);
        *(_DWORD *)(entity + 5112) = v58;
        LOBYTE(v159) = 0;
        rf_string_destroy_buffer(v97);
      }
      if ( *(_DWORD *)(entity + 5112) )
      {
        rf_matrix3_construct(v121);
        rf_model_handle_get_node_transform_adapter(
          *(_DWORD *)(entity + 128),
          *(_DWORD *)(entity + 5112) + 8,
          (int)v121,
          *(_DWORD *)(entity + 5108));
        rf_vector_copy((float *)(*(_DWORD *)(entity + 5112) + 20), v96, v122);
      }
    }
    rf_replicator_arm_milliseconds((int *)(entity + 5116), -1000);
    *(_DWORD *)(entity + 5120) = -1;
    *(_DWORD *)(entity + 5124) = -1;
    *(float *)(entity + 5128) = 0.0;
    rf_replicator_reset((_DWORD *)(entity + 5132));
    *(_DWORD *)(entity + 2132) = -1;
    rf_replicator_reset((_DWORD *)(entity + 5068));
    *(_DWORD *)(entity + 5136) = 0;
    if ( (int)rf_string_length_from_cstr((const char **)(v142 + 56)) > 0 )
    {
      *(float *)&v68 = NAN;
      v67 = 1;
      v59 = (char *)rf_string_object_c_str_or_empty((const void *)(v142 + 56));
      v3m_mode1 = rf_model_handle_load_v3m_mode1(v59, v67, (void *)v68);
      *(_DWORD *)(entity + 5136) = v3m_mode1;
    }
    rf_replicator_arm_milliseconds((int *)(entity + 5140), 0);
    *(_DWORD *)(entity + 5156) = 0;
    *(_DWORD *)(entity + 5160) = 0;
    *(_DWORD *)(entity + 5164) = 0;
    rf_vector_copy((float *)(entity + 5172), v95, (const float *)(*(_DWORD *)(entity + 660) + 108));
    rf_vector_copy((float *)(entity + 5184), v94, (const float *)(*(_DWORD *)(entity + 660) + 120));
    if ( (*(_DWORD *)(entity + 424) & 0x20) != 0 && (*(_DWORD *)(entity + 124) & 0x8000) == 0 )
      rf_collision_register_object_against_active_list(entity);
    if ( rf_string_equals_case_insensitive(v142, "auto turret") )
    {
      v120 = sub_431680("auto turret head");
      runtime = (int *)rf_entity_create_runtime(
                         v120,
                         (char *)&byte_631AC3,
                         *(_DWORD *)(entity + 44),
                         entity + 60,
                         (float *)(entity + 72),
                         0,
                         -1);
      runtime[126] = 0;
      runtime[31] |= 0x100u;
      v61 = (int **)sub_552200((_DWORD *)(entity + 2252), 0);
      rf_entity_associate_child_with_last_slot_key(entity, runtime[11], **v61);
    }
    *(_DWORD *)(entity + 5196) = -1;
    *(_DWORD *)(entity + 5200) = -1;
    rf_replicator_arm_milliseconds((int *)(entity + 5208), 0);
    if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(entity + 660) + 1828)) != 0 )
      *(_DWORD *)(entity + 2064) |= 0x40u;
    if ( rf_entity_has_jeep_flag(entity) )
    {
      v62 = rf_model_handle_find_node_adapter(*(_DWORD *)(entity + 128), "jeep_gun");
      *(_DWORD *)(entity + 5204) = v62;
      if ( !unk_681E80 )
      {
        unk_681E80 = rf_model_handle_load_v3m_mode1("jeep_gun.v3d", 1, (void *)0xFFFFFFFF);
        if ( unk_681E80 )
          dword_661514 = rf_model_handle_find_node_adapter(unk_681E80, "muzzle_1");
      }
    }
    for ( i = 0; i < 2; ++i )
      *(_DWORD *)(entity + 4 * i + 5212) = -1;
    if ( rf_string_equals_case_insensitive(v142, "medic1") )
    {
      index_by_name = rf_clutter_class_find_index_by_name("syringe");
      v117 = rf_clutter_runtime_create(
               index_by_name,
               (char *)&byte_631AD3,
               -1,
               (float *)(entity + 60),
               (float *)(entity + 72),
               0);
      if ( v117 )
        *(_DWORD *)(entity + 5216) = v117[11];
    }
    *(_DWORD *)(entity + 5244) = -1;
    *(_DWORD *)(entity + 5240) = -1;
    *(float *)(entity + 5220) = 0.0;
    *(_DWORD *)(entity + 5232) = 0;
    *(_DWORD *)(entity + 5248) = a7;
    *(_DWORD *)(entity + 5252) = -1;
    *(_DWORD *)(entity + 5260) = 0;
    if ( rf_multiplayer_runtime_mode && (a6 & 8) != 0 )
    {
      v92 = operator new(0x900u);
      LOBYTE(v159) = 6;
      if ( v92 )
        v69 = rf_motion_sample_buffer_construct((char *)v92);
      else
        v69 = nullptr;
      v93 = v69;
      LOBYTE(v159) = 0;
      *(_DWORD *)(entity + 632) = v69;
      rf_motion_sample_buffer_reset(*(_DWORD *)(entity + 632));
      v63 = rf_vfx_load_instance("respawn.vfx", (int)byte_98967F);
      *(_DWORD *)(entity + 5260) = v63;
      rf_vfx_start_instance(*(int **)(entity + 5260), 0, 1.0, 1);
    }
    rf_replicator_reset((_DWORD *)(entity + 5264));
    v91 = entity;
    v159 = -1;
    rf_object_setup152_destroy_array_backing(v153);
    return v91;
  }
  else
  {
    v109 = 0;
    v159 = -1;
    rf_object_setup152_destroy_array_backing(v153);
    return v109;
  }
}

