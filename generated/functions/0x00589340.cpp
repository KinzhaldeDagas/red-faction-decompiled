// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589340 rf_character_load_vcm_and_build_aux_bindings
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Thiscall base character record (6744 bytes). Sets model-resource count+6588=0; loop bound is ONE, so only first148-byte descriptor at+6592 is loaded. Copies base name without last extension, appends .vcm, and calls5888B0 (which actually substitutes .v3c). The alternate _letter.vcm branch cannot run under this loop bound. Filename scan starts at Buffer-1 then advances into Buffer; odd &Str+3 pseudocode is a stack-layout artifact. No successful resource returnsfalse. Otherwise builds56-byte auxiliary bindings at+4796: first100-byte records use quaternion+68 and translation+84; following44-byte collision-sphere records use identity rotation plus translation+28. Stores source pointer and affine matrix, count+4792=sum of both counts, sets flags+68
// bit4, returns1. No check that combined count fits32 binding slots or counts are nonnegative.
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Character auxiliary bindings place 100-byte auxiliary source records first (quat+68,pos+84), then 44-byte collision spheres (identity rotation,pos+28). Writes source pointer and local48 affine, with count equal to both counts combined. This function does NOT write binding+52 parent; that initialization remains a separate owner until the 589A40/58A0A0 chain is closed.
char __thiscall rf_character_load_vcm_and_build_aux_bindings(int this)
{
  char *v3; // [esp+18h] [ebp-68h]
  char *Str; // [esp+1Ch] [ebp-64h] BYREF
  char Buffer; // [esp+20h] [ebp-60h] BYREF
  _BYTE v6[3]; // [esp+21h] [ebp-5Fh] BYREF
  float *aux_transform_records_with_count; // [esp+6Ch] [ebp-14h]
  int v8; // [esp+70h] [ebp-10h] BYREF
  float *collision_spheres_with_count; // [esp+74h] [ebp-Ch]
  int i; // [esp+78h] [ebp-8h]
  int v11; // [esp+7Ch] [ebp-4h] BYREF

  Str = (char *)this;
  *(_DWORD *)(this + 6588) = 0;
  for ( i = 0; i < 1; ++i )
  {
    rf_path_copy_without_last_extension(&Buffer, Str);
    if ( i )
    {
      sprintf(&v6[&v6[strlen(&Buffer)] - v6 - 1], "_%c.vcm", i + 97);
    }
    else
    {
      v3 = (char *)&Str + 3;
      while ( *++v3 )
        ;
      strcpy(v3, ".vcm");
    }
    if ( !rf_v3c_read_character_resource(&Str[148 * i + 6592], (int *)Str, &Buffer) )
      break;
    ++*((_DWORD *)Str + 1647);
  }
  if ( *((int *)Str + 1647) < 1 )
    return 0;
  aux_transform_records_with_count = (float *)rf_v3c_get_aux_transform_records_with_count(Str + 6592, &v8);
  for ( i = 0; i < v8; ++i )
  {
    *(_DWORD *)&Str[56 * i + 4796] = &aux_transform_records_with_count[25 * i];
    rf_affine3x4_set_quaternion_translation(
      (float *)&Str[56 * i + 4800],
      &aux_transform_records_with_count[25 * i + 17],
      &aux_transform_records_with_count[25 * i + 21]);
  }
  *((_DWORD *)Str + 1198) = v8;
  collision_spheres_with_count = (float *)rf_v3c_get_collision_spheres_with_count(Str + 6592, &v11);
  for ( i = 0; i < v11; ++i )
  {
    *(_DWORD *)&Str[56 * v8 + 4796 + 56 * i] = &collision_spheres_with_count[11 * i];
    rf_affine3x4_set_identity((float *)&Str[56 * v8 + 4800 + 56 * i]);
    rf_affine3x4_set_translation_return_source(
      (float *)&Str[56 * v8 + 4800 + 56 * i],
      &collision_spheres_with_count[11 * i + 7]);
  }
  *((_DWORD *)Str + 1198) += v11;
  *((_DWORD *)Str + 17) |= 4u;
  return 1;
}

