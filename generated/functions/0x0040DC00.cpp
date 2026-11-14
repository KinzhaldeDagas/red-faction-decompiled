// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DC00 sub_40DC00
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: Route reset arms both route+11C and route+134 with0, after clearing routecount/indices/selected-list state.4033C0 invokes this on its embedded route; constructor412EB0 prior invalid deadlines are not the final AI-birth values.
// UNREALRED VERIFIED [original-goto-reset-clock-20261112]: The two ordered calls55EF80(route+11C,0) then55EF80(route+134,0) each read the actual663E90 clock;55EF80 has no zero-duration shortcut. These stores are current raw clock values, not literal zero. Route waiting vector+138, byte348=1, byte368=0 and scalar352=0 are written AFTER both arms. Geometric path clearing alone does not reproduce this full reset.
int __cdecl sub_40DC00(int a1)
{
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 296) = 0;
  *(_DWORD *)(a1 + 24) = -1;
  *(_DWORD *)(a1 + 20) = -1;
  *(_DWORD *)(a1 + 300) = 0;
  *(_DWORD *)(a1 + 324) = -1;
  rf_replicator_arm_milliseconds((int *)(a1 + 284), 0);
  rf_replicator_arm_milliseconds((int *)(a1 + 308), 0);
  rf_vector3_zero_return_destination((float *)(a1 + 312));
  *(_BYTE *)(a1 + 348) = 1;
  *(_BYTE *)(a1 + 368) = 0;
  *(float *)(a1 + 352) = 0.0;
  return a1;
}

