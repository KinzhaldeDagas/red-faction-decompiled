// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411950 sub_411950
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] This setter copies input matrix to entity physical+FC, common+48, then view+7E0 (411962/411973/411987). The view matrix can have additional runtime writers; a current host-pose mapping must be labeled as such and not asserted identical after unported native view updates.
int __cdecl sub_411950(int a1, float *a2)
{
  rf_matrix3_copy((float *)(*(_DWORD *)a1 + 252), a2);
  rf_matrix3_copy((float *)(*(_DWORD *)a1 + 72), a2);
  return rf_matrix3_copy((float *)(*(_DWORD *)a1 + 2016), a2);
}

