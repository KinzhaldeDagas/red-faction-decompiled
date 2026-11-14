// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D6530 rf_entity_apply_free_euler_rotation_input
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity. dt=432,k=class660 float100. Local increments D=(1800*k*dt+1832,1804*k*dt+1828,1808*k*dt). Writes angular336=D/dt via unchecked vector division;clears1828/1832,input1800 and2160/2184 vectors. Builds Euler increment matrix(pitch=D.x,bank=D.z,heading=D.y),sets current252=incrementMatrix*oldCurrent252,repairs forward basis,and copies to predicted288. Extracts Euler into2148X,2156Z,2152Y through retail extraction helper. Does NOT copy common72/visual2016 or rebuild tensor here. Constructor no-op does not zero D,but all three D components explicitly written. No dt/class/finite validation or angle clamp.
void __cdecl rf_entity_apply_free_euler_rotation_input(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float v3[9]; // [esp+Ch] [ebp-6Ch] BYREF
  float copy_result[3]; // [esp+30h] [ebp-48h] BYREF
  int v5[3]; // [esp+3Ch] [ebp-3Ch] BYREF
  float v6[9]; // [esp+48h] [ebp-30h] BYREF
  float v7; // [esp+6Ch] [ebp-Ch] BYREF
  float v8; // [esp+70h] [ebp-8h]
  float v9; // [esp+74h] [ebp-4h]

  rf_vector3_default_construct_noop(&v7);
  v7 = *(float *)(a1 + 1800) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432) + *(float *)(a1 + 1832);
  v8 = *(float *)(a1 + 1804) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432) + *(float *)(a1 + 1828);
  v9 = *(float *)(a1 + 1808) * *(float *)(*(_DWORD *)(a1 + 660) + 100) * *(float *)(a1 + 432);
  v1 = rf_vector_divide(&v7, (float *)v5, *(float *)(a1 + 432));
  rf_vector_copy((float *)(a1 + 336), copy_result, v1);
  *(float *)(a1 + 1828) = 0.0;
  *(float *)(a1 + 1832) = 0.0;
  rf_vector3_zero_return_destination((float *)(a1 + 1800));
  rf_vector3_zero_return_destination((float *)(a1 + 2160));
  rf_vector3_zero_return_destination((float *)(a1 + 2184));
  rf_matrix3_construct_from_euler_angles((int)v6, v7, v9, v8);
  v2 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 252), v3, v6);
  rf_matrix3_copy((float *)(a1 + 252), v2);
  rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 252));
  rf_matrix3_copy((float *)(a1 + 288), (const float *)(a1 + 252));
  rf_matrix3_extract_euler_angles_retail(
    (float *)(a1 + 252),
    (float *)(a1 + 2148),
    (float *)(a1 + 2156),
    (float *)(a1 + 2152));
}

