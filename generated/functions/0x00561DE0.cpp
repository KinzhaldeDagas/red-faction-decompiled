// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561DE0 rf_vmesh_type3_vfx_load
// UNREALRED VERIFIED [fpgun-vmesh-decode]: Creates a tag-3 VMesh wrapper and its optional 36-byte Spark-VFX payload.
char __thiscall rf_vmesh_type3_vfx_load(int *this, char *String2, char a3, int a4)
{
  char v4; // cl
  float *v6; // [esp+4h] [ebp-2Ch]
  _DWORD *v7; // [esp+10h] [ebp-20h]
  char *v8; // [esp+14h] [ebp-1Ch]
  float *v10; // [esp+1Ch] [ebp-14h]

  *this = 3;
  v8 = String2;
  v7 = this + 3;
  do
  {
    v4 = *v8;
    *(_BYTE *)v7 = *v8++;
    v7 = (_DWORD *)((char *)v7 + 1);
  }
  while ( v4 );
  *(this + 2) = (int)rf_scene_definition_get_or_load_cached_vsfx(String2, a4);
  if ( !*(this + 2) )
    return 0;
  if ( a3 )
  {
    v10 = (float *)operator new(0x24u);
    if ( v10 )
      v6 = rf_scene_instance_construct(v10, *(this + 2));
    else
      v6 = nullptr;
    *(this + 1) = (int)v6;
  }
  else
  {
    *(this + 1) = 0;
  }
  return 1;
}

