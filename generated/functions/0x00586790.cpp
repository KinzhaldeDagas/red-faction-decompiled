// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00586790 rf_character_build_skin_transforms
// UNREALRED VERIFIED [animation-mix-decode]: Builds final skinning transforms from the evaluated local hierarchy and bind-space data.
int __thiscall rf_character_build_skin_transforms(int this, int a2, int a3, int a4, int a5, int a6, char a7)
{
  int result; // eax
  float *v8; // eax
  float v10[12]; // [esp+4h] [ebp-3Ch] BYREF
  int v11; // [esp+34h] [ebp-Ch]
  int v12; // [esp+38h] [ebp-8h]
  int i; // [esp+3Ch] [ebp-4h]

  v11 = *(_DWORD *)(this + 7504) + 76;
  v12 = *(_DWORD *)(*(_DWORD *)(this + 7504) + 72);
  rf_character_instance_evaluate_pose(v12, *(_DWORD *)(this + 7504) + 3876, this);
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= v12 )
      break;
    if ( *(unsigned __int16 *)(this + 48 * i + 5014) != *(unsigned __int16 *)(this + 7416) )
    {
      *(_WORD *)(this + 48 * i + 5014) = *(_WORD *)(this + 7416);
      v8 = rf_matrix43_compose_parent_local((float *)(v11 + 76 * i + 24), v10, (float *)(this + 48 * i));
      rf_fixed_block48_copy((void *)(this + 48 * i + 2400), v8);
    }
  }
  return result;
}

