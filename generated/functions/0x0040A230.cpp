// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A230 rf_ai_secondary_state_write
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Secondary setter writes AI+0x2B4, then x87-loads shared FLOAT SECONDS at6FC428 and calls truncation helper before storing int32 AI+0x2BC. This timestamp is not NativeDeadline millisecond ring time. Fresh19 confirms444D30 adds frame-delta SECONDS with float store; separate source-bound clock ownership is required.
int __cdecl rf_ai_secondary_state_write(int a1, int a2)
{
  int result; // eax

  *(_DWORD *)(a1 + 692) = a2;
  result = (int)*(float *)&dword_6FC428;
  *(_DWORD *)(a1 + 700) = result;
  return result;
}

