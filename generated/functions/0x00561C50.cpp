// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561C50 rf_vmesh_type1_v3m_load
// UNREALRED VERIFIED [fpgun-vmesh-decode]: Creates a tag-1 VMesh wrapper, copies its filename, and parses the V3M payload.
bool __thiscall rf_vmesh_type1_v3m_load(_DWORD *this, char *Str, unsigned __int8 a3, int a4, int a5)
{
  char v5; // cl
  _DWORD *v7; // [esp+8h] [ebp-Ch]
  char *v8; // [esp+Ch] [ebp-8h]

  *this = 1;
  v8 = Str;
  v7 = this + 3;
  do
  {
    v5 = *v8;
    *(_BYTE *)v7 = *v8++;
    v7 = (_DWORD *)((char *)v7 + 1);
  }
  while ( v5 );
  *(this + 1) = sub_5B7F80(Str, a3, a5);
  return *(this + 1) != 0;
}

